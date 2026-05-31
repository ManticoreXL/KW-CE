#ifndef TWOLAYER_H
#define TWOLAYER_H

#include <stdint.h>

/**
 * @brief Encode 16-bit input using 2-layer encoding (CRC-8 + Hamming(7,4)).
 *
 * This function first computes a CRC-8 on the 16-bit input and then splits the resulting
 * 24-bit codeword into six 4-bit blocks, each of which is encoded using the (7,4) Hamming code.
 *
 * @param data 16-bit input data.
 * @param output 6-byte array to store the resulting 42-bit encoded output.
 */
void twolayer_encode(uint16_t data, uint8_t output[6]);

/**
 * @brief Decode a 42-bit input using 2-layer decoding (Hamming(7,4) + CRC-8).
 *
 * Each 7-bit segment is decoded using Hamming(7,4), reconstructing the original 24-bit
 * CRC codeword. CRC-8 is then used to validate the 16-bit original data.
 *
 * @param input 6-byte array containing the 42-bit received codeword.
 * @param decoded_data Pointer to store the resulting 16-bit output if valid.
 * @return 0 if no error or all errors corrected, 1 if an uncorrectable error is detected.
 */
int twolayer_decode(const uint8_t input[6], uint16_t *decoded_data);

#endif
