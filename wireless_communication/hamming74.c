#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hamming74.h"
#include "utils.h"

// Generator matrix G (4x7):
// t = G * s
static const uint8_t G[4] = {
    0b1000101, // s1
    0b0100110, // s2
    0b0010111, // s3
    0b0001011  // s4
};

// Parity check matrix H (3x7)
// z = H * r
static const uint8_t H[3] = {
    0b1110100,
    0b0111010,
    0b1011001
};

// Syndrome-to-error-position mapping
static const uint8_t syndrome_to_bit[8] = {
    0, // 000 - no error
    7, // 001 - r7
    6, // 010 - r6
    4, // 011 - r4
    5, // 100 - r5
    1, // 101 - r1
    2, // 110 - r2
    3  // 111 - r3
};

uint8_t hamming74_encode(uint8_t data) {
    uint8_t codeword = 0;

    // Multiply input bits by generator matrix rows using XOR (GF(2))
    for (int i = 0; i < 4; i++) {
        if (data & (1 << (3 - i))) {
            codeword ^= G[i];
        }
    }

    // Mask to ensure only 7 bits are used
    return codeword & 0x7F;
}

uint8_t hamming74_decode(uint8_t codeword, int *corrected, uint8_t *syndrome) {
    *syndrome = 0;

    // Compute syndrome z = H * r
    for (int i = 0; i < 3; i++) {
        uint8_t h_row = H[i];
        uint8_t dot = codeword & h_row;

        // Compute parity of dot product (mod 2)
        int parity = 0;

        for (int j = 0; j < 7; j++) {
            if (dot & (1 << j)) parity ^= 1;
        }

        *syndrome |= (parity << (2 - i));
    }

    // If syndrome is not zero, there is a single-bit error
    if (*syndrome != 0) {
        int bit_pos = syndrome_to_bit[*syndrome];
        if (bit_pos >= 1 && bit_pos <= 7) {
            // Correct the error by flipping the corresponding bit
            codeword ^= (1 << (7 - bit_pos)); 
            *corrected = 1;
        } else {
            // Invalid syndrome (should not occur)
            *corrected = 0;
        }
    } else {
        *corrected = 0;
    }

    // Extract original 4-bit data from corrected codeword
    uint8_t data = 0;
    data |= ((codeword >> 6) & 0x1) << 3; // r1 -> s1
    data |= ((codeword >> 5) & 0x1) << 2; // r2 -> s2
    data |= ((codeword >> 4) & 0x1) << 1; // r3 -> s3
    data |= ((codeword >> 3) & 0x1) << 0; // r4 -> s4

    return data;
}


#ifdef TEST_HAMMING74_ENC
int main() {
    char input_str[5]; // 4 bits + null terminator

    printf("Enter 4-bit binary data: ");
    if (scanf("%4s", input_str) != 1 || strlen(input_str) != 4) {
        printf("Invalid input! Please enter exactly 4 bits.\n");
        return -1;
    }

    // Convert binary string to 4-bit integer
    uint8_t data = 0;

    for (int i = 0; i < 4; i++) {
        if (input_str[i] == '1') data = (data << 1) | 1;
        else if (input_str[i] == '0') data <<= 1;
        else {
            printf("Invalid character in binary input.\n");
            return -1;
        }
    }

    // Encode and print codeword
    uint8_t codeword = hamming74_encode(data);

    printf("Encoded 7-bit codeword: ");
    print_binary(codeword, 7);
    printf("\n");

    printf("Press Enter to exit...");
    getchar(); // consume leftover '\n'
    getchar(); // wait for real input

    return 0;
}
#endif

#ifdef TEST_HAMMING74_DEC
int main() {
    char input_str[8]; // 7 bits + null terminator

    printf("Enter 7-bit binary codeword: ");
    if (scanf("%7s", input_str) != 1 || strlen(input_str) != 7) {
        printf("Invalid input! Please enter exactly 7 bits.\n");
        return -1;
    }

    // Convert binary string to 7-bit integer
    uint8_t codeword = 0;

    for (int i = 0; i < 7; i++) {
        if (input_str[i] == '1') 
            codeword = (codeword << 1) | 1;
        else if (input_str[i] == '0') 
            codeword <<= 1;
        else {
            printf("Invalid character in binary input.\n");
            return -1;
        }
    }

    // Decode and correct
    int corrected;
    uint8_t syndrome;
    uint8_t data = hamming74_decode(codeword, &corrected, &syndrome);

    // Print result
    printf("Decoded 4-bit data: ");
    print_binary(data, 4);
    printf("\n");

    printf("Syndrome: z=");
    print_binary(syndrome, 3);

    if (corrected == 1) {
        int r_bit = syndrome_to_bit[syndrome];
        printf(" (r%d corrected)\n", r_bit);
    }
    else  if (corrected == 0) 
        printf(" (no error detected)\n");

    printf("Press Enter to exit...");
    getchar(); // consume leftover '\n'
    getchar(); // wait for real input

    return 0;
}
#endif
