#ifndef CRC8_H
#define CRC8_H

#include <stdint.h>

#define GENERATOR 0x107 // x^8 + x^2 + x + 1

/**
 * @brief Encodes a 16-bit data word using an 8-bit CRC (CRC-8).
 *
 * This function appends 8 zero bits to the input 16-bit data and computes
 * the 8-bit Frame Check Sequence (FCS) using the generator polynomial 0x107.
 *
 * @param data The 16-bit input data to be encoded.
 * @return The 8-bit CRC (FCS) value.
 */
uint8_t crc8_encode(uint16_t data);

/**
 * @brief Verifies a 24-bit codeword using CRC-8.
 *
 * This function checks whether the 8-bit CRC at the lower 8 bits of the
 * codeword matches the CRC of the upper 16-bit data portion.
 *
 * @param codeword The 24-bit codeword (16-bit data + 8-bit FCS).
 * @return 0 if no error is detected; 1 if an error is detected.
 */
int crc8_decode(uint32_t codeword);

uint16_t binary_str_to_uint16(const char *bin_str);
void print_binary(uint32_t value, int bits);

#endif