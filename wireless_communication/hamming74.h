#ifndef HAMMING74_H
#define HAMMING74_H

#include <stdint.h>

/**
 * @brief Encodes a 4-bit data word using (7,4) Hamming code.
 *
 * This function takes a 4-bit input and produces a 7-bit Hamming codeword
 * that can correct single-bit errors.
 *
 * @param data 4-bit input data (only lower 4 bits are used).
 * @return 7-bit Hamming codeword (stored in lower 7 bits of uint8_t).
 */
uint8_t hamming74_encode(uint8_t data);

/**
 * @brief Decodes a 7-bit Hamming codeword and corrects single-bit errors.
 *
 * This version also outputs the 3-bit syndrome value used for error detection.
 *
 * @param codeword 7-bit input codeword (lower 7 bits used)
 * @param corrected Output pointer: 1 if error corrected, 0 if no error
 * @param syndrome Output pointer: 3-bit syndrome (z = Hr)
 * @return Corrected 4-bit original data
 */
uint8_t hamming74_decode(uint8_t codeword, int *corrected, uint8_t *syndrome);

#endif
