#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

uint16_t binary_str_to_uint16(const char *bin_str) {
    uint16_t result = 0;

    for (int i = 0; i < 16; i++) {
        result <<= 1; // Shift left to make space for the next bit

        if (bin_str[i] == '1') {
            // Set the least significant bit if current char is '1'
            result |= 1; 
        } 
        else if (bin_str[i] != '0') {
            // Invalid character in input string
            printf("Invalid character in binary input.\n");
            exit(1);
        }
        // If '0', no action needed (LSB already 0)
    }
    return result;
}

void print_binary(uint32_t value, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        // Check if the i-th bit is set and print '1' or '0' accordingly
        printf("%c", (value & (1 << i)) ? '1' : '0');
    }
}