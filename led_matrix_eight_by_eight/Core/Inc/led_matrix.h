/*
 * LedMatrix.h
 *
 *  Created on: Aug 20, 2023
 *      Author: donovantran
 */

#ifndef INC_LED_MATRIX_H_
#define INC_LED_MATRIX_H_

#ifdef __cplusplus
namespace LEDM
{

class LedMatrix
{
public:
	// Constructor
	LedMatrix(unsigned col, unsigned row);

	// Destructor
	~LedMatrix();
	
	void setup();

private:

	// Delete copy constructor, move constructor, and assignment operators.
	LedMatrix(const LedMatrix &other) = delete;
	LedMatrix(LedMatrix &&other) = delete;
	LedMatrix& operator=(const LedMatrix &other) = delete;
	LedMatrix& operator=(LedMatrix &&other) = delete;

	unsigned m_col; // number of column the LED matrix supports
	unsigned m_row; // number of row the LED matrix supports
};

} /* namespace LEDM */

#endif // __cplusplus

#endif /* INC_LED_MATRIX_H_ */
