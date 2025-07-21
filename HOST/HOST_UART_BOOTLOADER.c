#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define CMD_HELLO       0x01
#define CMD_BEGIN       0x02
#define CMD_DATA        0x03
#define CMD_END         0x04
#define CMD_FINAL_CHKSUM 0x05
#define CMD_ACK   0x79

HANDLE open_serial(const char *port) {
    HANDLE h = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
    if (h == INVALID_HANDLE_VALUE) {
        perror("Open serial failed");
        exit(1);
    }
    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    GetCommState(h, &dcb);
    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;
    SetCommState(h, &dcb);
    return h;
}

void send_byte(HANDLE h, uint8_t b) {
    DWORD written;
    WriteFile(h, &b, 1, &written, NULL);
}

uint8_t recv_byte(HANDLE h) {
    uint8_t b;
    DWORD read;
    ReadFile(h, &b, 1, &read, NULL);
    return b;
}

uint8_t hex2byte(const char *hex) {
    uint8_t val;
    sscanf(hex, "%2hhx", &val);
    return val;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <hexfile> <COMx>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Hex file open failed");
        return 1;
    }

    HANDLE hSerial = open_serial(argv[2]);

    // Handshake
    send_byte(hSerial, CMD_HELLO);
    if (recv_byte(hSerial) != CMD_ACK) {
        printf("No ACK for HELLO\n");
        return 1;
    }

    // Erase app region
    send_byte(hSerial, CMD_BEGIN);
    if (recv_byte(hSerial) != CMD_ACK) {
        printf("No ACK for BEGIN\n");
        return 1;
    }

    char line[600];
    uint32_t ext_addr = 0;
    uint32_t full_checksum = 0;

    while (fgets(line, sizeof(line), f)) {
        if (line[0] != ':') continue;

        uint8_t len = hex2byte(&line[1]);
        uint16_t offset = (hex2byte(&line[3]) << 8) | hex2byte(&line[5]);
        uint8_t type = hex2byte(&line[7]);

        if (type == 0x00) {  // Data
            uint32_t addr = ext_addr + offset;
            send_byte(hSerial, CMD_DATA);
            send_byte(hSerial, (addr >> 16) & 0xFF);
            send_byte(hSerial, (addr >> 8) & 0xFF);
            send_byte(hSerial, addr & 0xFF);
            send_byte(hSerial, len);

            for (int i = 0; i < len; i++) {
                uint8_t data = hex2byte(&line[9 + i * 2]);
                send_byte(hSerial, data);
                full_checksum += data;  // accumulate final checksum
            }

            uint8_t line_checksum = hex2byte(&line[9 + len * 2]);
            send_byte(hSerial, line_checksum);  // ✅ Send line checksum

            if (recv_byte(hSerial) != CMD_ACK) {
                printf("No ACK for DATA at addr 0x%06X\n", addr);
                return 1;
            }
        }
        else if (type == 0x04) {  // Extended linear address
            ext_addr = ((uint32_t)hex2byte(&line[9]) << 8 | hex2byte(&line[11])) << 16;
        }
        else if (type == 0x01) {  // End of file
            break;
        }
    }

    fclose(f);

    // END command
    send_byte(hSerial, CMD_END);
    if (recv_byte(hSerial) != CMD_ACK) {
        printf("No ACK for END\n");
        return 1;
    }

    // ✅ Send final checksum
    send_byte(hSerial, CMD_FINAL_CHKSUM);
    send_byte(hSerial, (full_checksum >> 24) & 0xFF);
    send_byte(hSerial, (full_checksum >> 16) & 0xFF);
    send_byte(hSerial, (full_checksum >> 8) & 0xFF);
    send_byte(hSerial, full_checksum & 0xFF);
    if (recv_byte(hSerial) != CMD_ACK) {
        printf("No ACK for FINAL_CHKSUM\n");
        return 1;
    }

    printf("Upload complete. Final checksum: 0x%08X\n", full_checksum);
    return 0;
}
