/*
 * LedMatrix.cpp
 *
 *  Created on: Aug 20, 2023
 *      Author: donovantran
 */

#include "led_matrix.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include <memory>

#include "shift_register.h"
#include "led_matrix_alphabet.h"
namespace LEDM
{

LedMatrix::LedMatrix(unsigned col, unsigned row) : m_col(col), m_row(row)
{
    setup_col_shift_reg();
    setup_row_shift_reg();
}

LedMatrix::~LedMatrix()
{
}

void LedMatrix::setup_col_shift_reg(void)
{
    // Instantiate a shift register object that controls the LED matrix column
	SN74HC595N_Shift_Reg::SN74HC595N_Pin data_pin  { GPIOE, GPIO_PIN_7 };
	SN74HC595N_Shift_Reg::SN74HC595N_Pin storage_pin { GPIOE, GPIO_PIN_9 };
    SN74HC595N_Shift_Reg::SN74HC595N_Pin clock_pin { GPIOE, GPIO_PIN_11 };
    m_col_shift_reg = std::make_unique<SN74HC595N_Shift_Reg>(data_pin, storage_pin, clock_pin);
}

void LedMatrix::setup_row_shift_reg(void)
{
    // Instantiate a shift register object that controls the LED matrix row
    SN74HC595N_Shift_Reg::SN74HC595N_Pin data_pin  { GPIOE, GPIO_PIN_8 };
    SN74HC595N_Shift_Reg::SN74HC595N_Pin storage_pin { GPIOE, GPIO_PIN_10 };
	SN74HC595N_Shift_Reg::SN74HC595N_Pin clock_pin { GPIOE, GPIO_PIN_12 };
    m_row_shift_reg = std::make_unique<SN74HC595N_Shift_Reg>(data_pin, storage_pin, clock_pin);
}

void LedMatrix::run(void)
{
    static unsigned toggle = 0;
    unsigned toggle_val = (toggle) ? 0xFF : 0x00;
    // for (unsigned row = 0, unsigned col = 8; row < 8; ++row)
    // {
        m_col_shift_reg->disable_latch();
        m_row_shift_reg->disable_latch();
        
        // unsigned val = (1 << col);
        m_col_shift_reg->shift_out(SN74HC595N_Shift_Reg::SHIFT_BIT_ORDER::MSBFIRST, 0xFF);
        m_row_shift_reg->shift_out(SN74HC595N_Shift_Reg::SHIFT_BIT_ORDER::MSBFIRST, toggle_val);
        
        m_col_shift_reg->enable_latch();
        m_row_shift_reg->enable_latch();

        HAL_Delay(500);
    // }
    toggle ^= 1;
    

    // for (unsigned val = 0; val < 256; ++val)
    // {
    //     m_row_shift_reg->disable_latch();
        
    //     m_row_shift_reg->shift_out(SN74HC595N_Shift_Reg::SHIFT_BIT_ORDER::MSBFIRST, val);
        
    //     m_row_shift_reg->enable_latch();

    //     HAL_Delay(500);
    // }
}

} /* namespace LEDM */
