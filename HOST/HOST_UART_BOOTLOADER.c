#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define CMD_HELLO   0x55
#define CMD_BEGIN   0x01
#define CMD_DATA    0x02
#define CMD_END     0x03
#define CMD_ACK     0xAA
#define CMD_NACK 0xff
// Open COM port
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
    dcb.Parity = NOPARITY;
    SetCommState(h, &dcb);
    return h;
}

// Send 1 byte
void send_byte(HANDLE h, uint8_t b) {
    DWORD written;
    WriteFile(h, &b, 1, &written, NULL);
}

// Receive 1 byte
uint8_t recv_byte(HANDLE h) {
    uint8_t b;
    DWORD read;
    ReadFile(h, &b, 1, &read, NULL);
    return b;
}

// Wait for ACK with timeout
int wait_for_ack(HANDLE h, uint8_t expected, int timeout_ms) {
    uint8_t b;
    DWORD read;
    DWORD start = GetTickCount();
    while (GetTickCount() - start < (DWORD)timeout_ms) {
        if (ReadFile(h, &b, 1, &read, NULL) && read == 1) {
            return (b == expected);
        }
        Sleep(10);
    }

    printf("Timeout waiting for ACK (0x%02X)\n", expected);
    return 0;
}

// Convert 2 hex characters to byte
uint8_t hex2byte(const char *hex) {
    uint8_t val;
    sscanf(hex, "%2hhx", &val);
    return val;
}
// Calculate checksum for a data record line
uint8_t calc_checksum(const char *line, uint8_t byte_count) {
    uint32_t sum = 0;
    for (int i = 1; i < 9 + byte_count * 2; i += 2) {
        sum += hex2byte(&line[i]);
    }
    return (uint8_t)((~sum + 1) & 0xFF);
}
int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <hexfile> <COMx>\n", argv[0]);
        return 1;
    }
printf("commands ok\n");
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Hex file open failed");
        return 1;
    }
    printf("file ok\n");

    HANDLE hSerial = open_serial(argv[2]);
    printf("port ok\n");

    // Step 1: Send CMD_HELLO
    send_byte(hSerial, CMD_HELLO);
    if (!wait_for_ack(hSerial, CMD_ACK, 1000)) {
        printf("No ACK for HELLO\n");
        return 1;
    }
    printf(" ACK for HELLO\n");

    // Step 2: Send CMD_BEGIN
    send_byte(hSerial, CMD_BEGIN);
    if (!wait_for_ack(hSerial, CMD_ACK, 1000)) {
        printf("No ACK for BEGIN\n");
        return 1;
    }

       char line[600];
    uint32_t ext_addr = 0,complete_check_sum=0;

    while (fgets(line, sizeof(line), f)) {
        if (line[0] != ':') continue;

        uint8_t len = hex2byte(&line[1]);
        uint16_t offset = (hex2byte(&line[3]) << 8) | hex2byte(&line[5]);
        uint8_t type = hex2byte(&line[7]);

        if (type == 0x00) {  // Data record
            uint32_t addr = ext_addr+offset;
            printf("Sending Addr: 0x%06X, Len: %d, offset :0x%02x Data: ", addr, len,offset);

            send_byte(hSerial, CMD_DATA);
            //send_byte(hSerial, (addr>>24)& 0xFF);
           // send_byte(hSerial, (addr >> 16) & 0xFF);
            send_byte(hSerial, (addr >> 8) & 0xFF);
            send_byte(hSerial, addr & 0xFF);
            send_byte(hSerial, len);

            for (int i = 0; i < len; i++) {
                uint8_t data = hex2byte(&line[9 + i * 2]);
                send_byte(hSerial, data);
                printf("%02X ", data);
            }
            uint8_t file_checksum = hex2byte(&line[9 + len * 2]);
            complete_check_sum+=file_checksum;
           uint8_t calculated = calc_checksum(line, len);
            printf("| File Checksum: %02X | Calculated: %02X", file_checksum, calculated);
             send_byte(hSerial, file_checksum);
             printf("\n");
            if (!wait_for_ack(hSerial, CMD_ACK, 1000)) {
                printf("No ACK for DATA at addr 0x%06X\n", addr);
                return 1;
            }
        }
        else if (type == 0x01) {  // End of file
            break;
        }
        else if (type == 0x04) {  // Extended linear address
            ext_addr = ((uint32_t)hex2byte(&line[9]) << 8 | hex2byte(&line[11])) << 16;
            printf("Set Extended Address to 0x%08X\n", ext_addr);
        }
        else {
            printf("Skipping unsupported record type: 0x%02X\n", type);
        }
    }
    fclose(f);
    // Step 4: Send CMD_END
    printf("%d ",complete_check_sum);
    send_byte(hSerial, CMD_END);
    send_byte(hSerial, (complete_check_sum>>24)&0XFF);
    send_byte(hSerial, (complete_check_sum>>16)&0xff);
    send_byte(hSerial, (complete_check_sum>>8)&0xff);
    send_byte(hSerial, (complete_check_sum)&0xff);
    if (!wait_for_ack(hSerial, CMD_ACK, 1000)) {
        printf("No ACK for END\n");
        return 1;
    }

    printf("Upload complete.\n");
    return 0;
}
