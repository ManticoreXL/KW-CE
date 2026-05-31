#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

/**
 * @brief Print a binary representation of an integer value.
 * 
 * @param value The integer value to print.
 * @param bits Number of bits to display.
 */
void print_binary(uint32_t value, int bits);

/**
 * @brief Convert a 16-character binary string to a 16-bit unsigned integer.
 * 
 * @param bin_str Null-terminated string containing exactly 16 characters of '0' or '1'.
 * @return uint16_t The converted value.
 */
uint16_t binary_str_to_uint16(const char *bin_str);

#endif