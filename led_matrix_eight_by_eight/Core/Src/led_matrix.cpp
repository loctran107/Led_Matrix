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

void LedMatrix::blink_all_leds(void)
{
    static unsigned toggle = 0;
    unsigned toggle_val = (toggle) ? 0xFF : 0x00;
    
    m_col_shift_reg->disable_latch();
    m_row_shift_reg->disable_latch();
    
    // unsigned val = (1 << col);
    m_col_shift_reg->shift_out(SN74HC595N_Shift_Reg::SHIFT_BIT_ORDER::MSBFIRST, 0xFF);
    m_row_shift_reg->shift_out(SN74HC595N_Shift_Reg::SHIFT_BIT_ORDER::MSBFIRST, toggle_val);
    
    m_col_shift_reg->enable_latch();
    m_row_shift_reg->enable_latch();

    HAL_Delay(500);
    
    toggle ^= 1;
}

void LedMatrix::run(void)
{
    static unsigned scroll = 0;
    scroll = (scroll >= 8) ? 0 : scroll;
    
    // This is the loop that added some delay per LED frame
    for (unsigned speed = 0; speed < 15; speed++)
    {
        for (unsigned col = 0; col < m_col; ++col)
        {   
            m_row_shift_reg->disable_latch();
            m_row_shift_reg->shift_out(SN74HC595N_Shift_Reg::SHIFT_BIT_ORDER::LSBFIRST, (1U << col));

            m_col_shift_reg->disable_latch();
            m_col_shift_reg->shift_out(SN74HC595N_Shift_Reg::SHIFT_BIT_ORDER::LSBFIRST, letter_A[col] << scroll);

            m_col_shift_reg->enable_latch();
            m_row_shift_reg->enable_latch();

            HAL_Delay(1); // 1ms delay to smooth out the pattern
        }
    }
    scroll++;
}

} /* namespace LEDM */
