#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t hex2byte(const char *hex) {
    uint8_t val;
    sscanf(hex, "%2hhx", &val);
    return val;
}

int main() {
    FILE *f = fopen("APPLICATION.hex", "r");
    if (!f) {
        perror("Error opening file");
        return 1;
    }

    char line[1024];
    int line_number = 0;

    while (fgets(line, sizeof(line), f)) {
        line_number++;
        line[strcspn(line, "\r\n")] = 0; // Remove \r or \n

        if (line[0] != ':') continue;

        uint8_t len = hex2byte(&line[1]);
        uint16_t offset = (hex2byte(&line[3]) << 8) | hex2byte(&line[5]);
        uint8_t type = hex2byte(&line[7]);
        printf("Record Type: %02X | Length: %d | Offset: 0x%04X | Data: ", type, len, offset);

        uint8_t data[256];
        for (int i = 0; i < len; i++) {
            data[i] = hex2byte(&line[9 + i * 2]);
            printf("%002x ",data[i]);
        }

        uint32_t checksum_from_file = hex2byte(&line[9 + len * 2]);

        // ✅ Calculate checksum manually
        uint32_t sum = len + (offset >> 8) + (offset & 0xFF) + type;
        for (int i = 0; i < len; i++) {
            sum += data[i];
        }
        uint8_t calculated_checksum = (~sum + 1) & 0xFF;

        // ✅ Print info
        printf("Line %02d: %s\n", line_number, line);
        printf("Length: %u, Offset: 0x%04X, Type: %u\n", len, offset, type);
        printf("Checksum in file:    0x%02X\n", checksum_from_file);
        printf("Calculated checksum: 0x%02X\n", calculated_checksum);
            int cnt=0;

        if (checksum_from_file == calculated_checksum) {
            printf("✅ Checksum OK\n");
            cnt++;

        } else {
            printf("❌ Checksum MISMATCH\n");
            cnt++;
            if(cnt==5){
                break;
            }
        }
            if(cnt==5){
                break;
            }
        printf("-----------------------------------\n");
        
    }

    fclose(f);
    return 0;
}
