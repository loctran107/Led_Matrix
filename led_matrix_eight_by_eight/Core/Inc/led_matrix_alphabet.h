/*
 * led_matrix_alphabet.h
 *
 *  Created on: Aug 21, 2023
 *      Author: donovantran
 */

#ifndef INC_LED_MATRIX_ALPHABET_H_
#define INC_LED_MATRIX_ALPHABET_H_

#include <cstdint>

constexpr unsigned STANDARD_LETTER_LENGTH { 8U };
constexpr unsigned STANDARD_LETTER_WIDTH { 8U };

std::uint8_t letter_A[STANDARD_LETTER_LENGTH] = {0x18, 0x3C, 0x66, 0x7E, 0x7E, 0x66, 0x66, 0x66};







#endif /* INC_LED_MATRIX_ALPHABET_H_ */
