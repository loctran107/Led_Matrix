/*
 * LedMatrix.h
 *
 *  Created on: Aug 20, 2023
 *      Author: donovantran
 */

#ifndef INC_LED_MATRIX_H_
#define INC_LED_MATRIX_H_

#include <memory>
#include <string>
#include "shift_register.h"
#include <vector>

namespace LEDM
{

class LedMatrix
{
public:
	// Constructor
	LedMatrix(unsigned col, unsigned row);

	// Destructor
	~LedMatrix();

	void display(std::string const message, unsigned const scrolling_speed);

private:

	// Delete copy constructor, move constructor, and assignment operators.
	LedMatrix(const LedMatrix &other) = delete;
	LedMatrix(LedMatrix &&other) = delete;
	LedMatrix& operator=(const LedMatrix &other) = delete;
	LedMatrix& operator=(LedMatrix &&other) = delete;

	void setup_col_shift_reg(void);
	void setup_row_shift_reg(void);

	void blink_all_leds(void);
	void init_led_animation(void);

	void produce_frame(bool is_bit_on, unsigned const row);
	void display_frame(void);
	void shift_frame_left(void);

	std::unique_ptr<SN74HC595N_Shift_Reg> m_col_shift_reg {nullptr};
	std::unique_ptr<SN74HC595N_Shift_Reg> m_row_shift_reg {nullptr};
	// TODO: maybe animation is not a good generic name for all of the effects
	// 		 Consider changing this name later
	std::uint8_t m_led_frame[8] { 0}; // m_led_animation[frame][row]
	unsigned m_col; // number of column the LED matrix supports
	unsigned m_row; // number of row the LED matrix supports
};

} /* namespace LEDM */

#endif /* INC_LED_MATRIX_H_ */
