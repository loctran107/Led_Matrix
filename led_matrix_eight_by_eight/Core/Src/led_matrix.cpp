/*
 * LedMatrix.cpp
 *
 *  Created on: Aug 20, 2023
 *      Author: donovantran
 */

#include "led_matrix.h"
#include "stm32f4xx_hal.h"
namespace LEDM {

LedMatrix::LedMatrix(unsigned col, unsigned row) : m_col(col), m_row(row)
{
}

LedMatrix::~LedMatrix()
{
}

void LedMatrix::setup(void)
{
    
}

} /* namespace LEDM */
