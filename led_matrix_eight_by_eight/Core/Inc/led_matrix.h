/*
 * LedMatrix.h
 *
 *  Created on: Aug 20, 2023
 *      Author: donovantran
 */

#ifndef INC_LED_MATRIX_H_
#define INC_LED_MATRIX_H_

#include <memory>
#include "shift_register.h"

namespace LEDM
{

class LedMatrix
{
public:
	// Constructor
	LedMatrix(unsigned col, unsigned row);

	// Destructor
	~LedMatrix();

	void run(void);

private:

	// Delete copy constructor, move constructor, and assignment operators.
	LedMatrix(const LedMatrix &other) = delete;
	LedMatrix(LedMatrix &&other) = delete;
	LedMatrix& operator=(const LedMatrix &other) = delete;
	LedMatrix& operator=(LedMatrix &&other) = delete;

	void setup_col_shift_reg(void);
	void setup_row_shift_reg(void);

	std::unique_ptr<SN74HC595N_Shift_Reg> m_col_shift_reg {nullptr};
	std::unique_ptr<SN74HC595N_Shift_Reg> m_row_shift_reg {nullptr};
	unsigned m_col; // number of column the LED matrix supports
	unsigned m_row; // number of row the LED matrix supports
};

} /* namespace LEDM */

#endif /* INC_LED_MATRIX_H_ */
