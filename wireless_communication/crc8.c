#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "crc8.h"
#include "utils.h"

uint8_t crc8_encode(uint16_t data) {
    // Append 8 zero bits to the data (equivalent to multiplying by x^8)
    uint32_t shifted_data = ((uint32_t)data) << 8;
    uint32_t mask = 1 << 23;

    // Perform modulo-2 division (bitwise XOR) using the generator polynomial
    for (int i = 0; i < 16; i++) {
        if (shifted_data & (1 << (23 - i))) {
            shifted_data ^= (GENERATOR << (15 - i));
        }
    }

    // Extract the last 8 bits (remainder is the CRC)
    uint8_t crc = shifted_data & 0xFF;

    return crc;
}

int crc8_decode(uint32_t codeword) {
    uint32_t temp = codeword;

    // Perform modulo-2 division to compute remainder
    for (int i = 0; i < 16; i++) {
        if (temp & (1 << (23 - i))) {
            temp ^= (GENERATOR << (15 - i));
        }
    }

    // If remainder is zero, the codeword is valid
    return (temp & 0xFF) != 0;
}

#ifdef TEST_CRC8_ENC
int main() {
    char input_str[17]; // 16-bit input + null terminator

    printf("Enter 16-bit binary data: ");
    if (scanf("%16s", input_str) != 1 || strlen(input_str) != 16) {
        printf("Invalid input! Please enter exactly 16 bits.\n");
        return -1;
    }

    // Convert binary string to 16-bit integer
    uint16_t data = binary_str_to_uint16(input_str);
    uint8_t fcs = crc8_encode(data);

    // Print 24-bit codeword
    printf("Encoded 24-bit codeword : ");
    print_binary((uint32_t)data, 16);
    printf(" ");
    print_binary((uint32_t)fcs, 8);
    printf("\n");

    printf("Press Enter to exit...");
    getchar(); // consume leftover '\n'
    getchar(); // wait for real input

    return 0;
}
#endif

#ifdef TEST_CRC8_DEC
int main() {
    char input_str[25]; // 24-bit input + null terminator

    printf("Enter 24-bit binary codeword: ");
    if (scanf("%24s", input_str) != 1 || strlen(input_str) != 24) {
        printf("Invalid input! Please enter exactly 24 bits.\n");
        return -1;
    }

    // Convert 24-bit binary string to integer
    uint32_t codeword = 0;

    for (int i = 0; i < 24; i++) {
        codeword <<= 1;

        if (input_str[i] == '1') {
            codeword |= 1;
        } 
        else if (input_str[i] != '0') {
            printf("Invalid character in binary input.\n");
            return -1;
        }
    }

    // Perform CRC-8 check
    int result = crc8_decode(codeword);
    printf("Decoded result: %s\n", result ? "ERROR!" : "No error");

    printf("Press Enter to exit...");
    getchar(); // consume leftover '\n'
    getchar(); // wait for real input

    return 0;
}
#endif