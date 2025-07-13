#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CMD_HELLO  0x55
#define CMD_ACK    0xAA
#define CMD_SIZE   0x10
#define CMD_BEGIN  0x01
#define CMD_DATA   0x02
#define CMD_END    0x03

HANDLE open_serial_port(const char *port_name) {
    HANDLE hSerial = CreateFileA(port_name, GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                 OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("❌ Could not open COM port %s\n", port_name);
        return NULL;
    }

    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    GetCommState(hSerial, &dcb);
    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;
    SetCommState(hSerial, &dcb);

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 100;
    timeouts.WriteTotalTimeoutConstant = 100;
    SetCommTimeouts(hSerial, &timeouts);

    return hSerial;
}

int wait_for_ack(HANDLE serial, int timeout_ms) {
    DWORD read;
    uint8_t ack;
    int waited = 0;
    while (waited < timeout_ms) {
        if (ReadFile(serial, &ack, 1, &read, NULL) && read == 1) {
            if (ack == CMD_ACK) return 1;
        }
        Sleep(10);
        waited += 10;
    }
    return 0;
}

int send_and_wait(HANDLE serial, uint8_t *data, DWORD len, const char *msg) {
    DWORD written;
    WriteFile(serial, data, len, &written, NULL);
    printf("➡️ Sent: %s (%lu bytes)\n", msg, len);
    return wait_for_ack(serial, 1000);
}

uint8_t parse_hex_byte(const char *s) {
    uint8_t hi = (s[0] >= 'A') ? (s[0] & 0xDF) - 'A' + 10 : (s[0] - '0');
    uint8_t lo = (s[1] >= 'A') ? (s[1] & 0xDF) - 'A' + 10 : (s[1] - '0');
    return (hi << 4) | lo;
}

long get_file_size(FILE *f) {
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return size;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <COMx> <firmware.hex>\n", argv[0]);
        return 1;
    }

    const char *com_port = argv[1];
    const char *hex_file = argv[2];

    FILE *f = fopen(hex_file, "r");
    if (!f) {
        printf("❌ Cannot open %s\n", hex_file);
        return 2;
    }

    HANDLE serial = open_serial_port(com_port);
    if (!serial) {
        fclose(f);
        return 3;
    }

    // Step 1: Handshake
    printf("🤝 Sending HELLO...\n");
    uint8_t hello = CMD_HELLO;
    DWORD written;
    WriteFile(serial, &hello, 1, &written, NULL);

    if (!wait_for_ack(serial, 2000)) {
        printf("❌ No ACK to HELLO\n");
        fclose(f);
        CloseHandle(serial);
        return 4;
    }
    printf("✅ ACK received from bootloader\n");

    // Step 2: Send file size
    long fsize = get_file_size(f);
    uint8_t size_packet[5] = { CMD_SIZE };
    size_packet[1] = (fsize >> 24) & 0xFF;
    size_packet[2] = (fsize >> 16) & 0xFF;
    size_packet[3] = (fsize >> 8) & 0xFF;
    size_packet[4] = fsize & 0xFF;
    if (!send_and_wait(serial, size_packet, 5, "File size")) {
        printf("❌ No ACK to file size\n");
        fclose(f);
        CloseHandle(serial);
        return 5;
    }

    // Step 3: Send CMD_BEGIN
    uint8_t begin = CMD_BEGIN;
    if (!send_and_wait(serial, &begin, 1, "CMD_BEGIN")) {
        printf("❌ No ACK to CMD_BEGIN\n");
        fclose(f);
        CloseHandle(serial);
        return 6;
    }

    // Step 4: Send HEX line by line
    char line[600];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] != ':') continue;
        uint8_t len = parse_hex_byte(&line[1]);
        uint16_t addr = (parse_hex_byte(&line[3]) << 8) | parse_hex_byte(&line[5]);
        uint8_t type = parse_hex_byte(&line[7]);

        if (type == 0x01) break; // EOF

        uint8_t packet[5 + 256] = { CMD_DATA, (addr >> 8), addr & 0xFF, len };
        for (int i = 0; i < len; i++)
            packet[4 + i] = parse_hex_byte(&line[9 + i * 2]);

        char debug_msg[64];
        sprintf(debug_msg, "Line @ 0x%04X, Len %d", addr, len);
        if (!send_and_wait(serial, packet, 4 + len, debug_msg)) {
            printf("❌ No ACK to DATA\n");
            fclose(f);
            CloseHandle(serial);
            return 7;
        }
    }

    // Step 5: Send CMD_END
    uint8_t end = CMD_END;
    if (!send_and_wait(serial, &end, 1, "CMD_END")) {
        printf("❌ No ACK to CMD_END\n");
    } else {
        printf("✅ Firmware sent successfully!\n");
    }

    fclose(f);
    CloseHandle(serial);
    return 0;
}
