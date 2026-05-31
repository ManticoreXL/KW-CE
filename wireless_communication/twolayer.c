#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "twolayer.h"
#include "crc8.h"
#include "hamming74.h"
#include "utils.h"

void twolayer_encode(uint16_t data, uint8_t output[6]) {
    // Step 1: Generate 8-bit CRC and append to data to form 24-bit codeword
    uint8_t crc = crc8_encode(data);
    uint32_t codeword24 = ((uint32_t)data << 8) | crc;

    // Step 2: Split into six 4-bit nibbles and encode each using Hamming(7,4)
    for (int i = 0; i < 6; i++) {
        uint8_t nibble = (codeword24 >> (20 - 4 * i)) & 0xF;
        output[i] = hamming74_encode(nibble);
    }
}

int twolayer_decode(const uint8_t input[6], uint16_t *decoded_data) {
    uint32_t reconstructed = 0;

    // Step 1: Decode each 7-bit Hamming codeword back to 4-bit block
    for (int i = 0; i < 6; i++) {
        int corrected = 0;
        uint8_t syndrome = 0;
        uint8_t decoded = hamming74_decode(input[i], &corrected, &syndrome);
        reconstructed = (reconstructed << 4) | (decoded & 0xF);
    }

    // Step 2: Check CRC on the 24-bit reconstructed codeword
    if (crc8_decode(reconstructed)) {
        return 1;
    }

    // Step 3: Extract original 16-bit data (upper 16 bits)
    *decoded_data = (reconstructed >> 8) & 0xFFFF;
    return 0;
}

#ifdef TEST_TWOLAYER_ENC
int main() {
    char input_str[17]; // 16-bit input string

    printf("Enter 16-bit binary data: ");
    if (scanf("%16s", input_str) != 1 || strlen(input_str) != 16) {
        printf("Invalid input! Please enter exactly 16 bits.\n");
        return -1;
    }

    // Convert string to 16-bit number
    uint16_t data = binary_str_to_uint16(input_str);
    uint8_t encoded[6];

    // Perform 2-layer encoding
    twolayer_encode(data, encoded);

    // Print the 42-bit encoded codeword (6 blocks of 7 bits)
    printf("Encoded 42-bit codeword: ");
    for (int i = 0; i < 6; i++) {
        print_binary(encoded[i], 7);
        printf(" ");
    }
    printf("\n");

    printf("Press Enter to exit...");
    getchar(); // consume leftover '\n'
    getchar(); // wait for real input

    return 0;
}
#endif

#ifdef TEST_TWOLAYER_DEC
int main() {
    char input_str[43]; // 42 bits + null terminator

    printf("Enter 42-bit binary codeword: ");
    if (scanf("%42s", input_str) != 1 || strlen(input_str) != 42) {
        printf("Invalid input! Please enter exactly 42 bits.\n");
        return -1;
    }

    // Convert 42-bit string into six 7-bit integers
    uint8_t input[6] = {0};

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            char bit = input_str[i * 7 + j];
            if (bit == '1') {
                input[i] = (input[i] << 1) | 1;
            } 
            else if (bit == '0') {
                input[i] <<= 1;
            } 
            else {
                printf("Invalid character in binary input.\n");
                return -1;
            }
        }
    }

    // Decode the 2-layer codeword
    uint16_t decoded;
    int result = twolayer_decode(input, &decoded);

    // Output result
    if (result == 0) {
        printf("Decoded 16-bit data: ");
        print_binary(decoded, 16);
        printf("\n");
    } else {
        printf("ERROR!\n");
    }

    printf("Press Enter to exit...");
    getchar(); // consume leftover '\n'
    getchar(); // wait for real input

    return 0;
}
#endif
