#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Convert 2-character hex string to byte
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
    if (argc < 2) {
        printf("Usage: %s <hexfile>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Failed to open file");
        return 1;
    }

    char line[600];

    while (fgets(line, sizeof(line), f)) {
        if (line[0] != ':') continue;

        uint8_t byte_count = hex2byte(&line[1]);
        uint8_t record_type = hex2byte(&line[7]);

        if (record_type == 0x00) {  // Data record
            printf("Data: ");
            for (int i = 0; i < byte_count; i++) {
                uint8_t data = hex2byte(&line[9 + i * 2]);
                printf("%02X ", data);
            }

            uint8_t file_checksum = hex2byte(&line[9 + byte_count * 2]);
            uint8_t calculated = calc_checksum(line, byte_count);

            printf("| File Checksum: %02X | Calculated: %02X", file_checksum, calculated);
            if (file_checksum == calculated) {
                printf(" ✅\n");
            } else {
                printf(" ❌\n");
            }
        }
    }

    fclose(f);
    return 0;
}
