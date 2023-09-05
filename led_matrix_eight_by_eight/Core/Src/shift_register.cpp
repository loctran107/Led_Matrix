/*
 * shift_register.cpp
 *
 *  Created on: Aug 20, 2023
 *      Author: donovantran
 */
#include "shift_register.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#include <cstdint>

namespace LEDM
{
SN74HC595N_Shift_Reg::SN74HC595N_Shift_Reg(SN74HC595N_Pin const data_pin,
                                           SN74HC595N_Pin const shift_pin,
                                           SN74HC595N_Pin const clock_pin)
    : m_data_pin(data_pin)
    , m_shift_pin(shift_pin)
    , m_clock_pin(clock_pin)
{
}

SN74HC595N_Shift_Reg::~SN74HC595N_Shift_Reg()
{
}

SN74HC595N_Shift_Reg& SN74HC595N_Shift_Reg::operator=(SN74HC595N_Shift_Reg const& other)
{
    m_data_pin  = other.m_data_pin;
    m_shift_pin = other.m_shift_pin;
    m_clock_pin = other.m_clock_pin;
    return *this;
}

void SN74HC595N_Shift_Reg::shift_out(std::uint8_t bit_order, std::uint8_t val)
{
    // Shift out 8 bits to the shift register
    for (unsigned bit = 0; bit < 8; ++bit)
    {
        bool bit_set = false;
        if (bit_order == SHIFT_BIT_ORDER::LSBFIRST)
        {
            bit_set = !!(val & (1U << bit));
        }
        else if (bit_order == SHIFT_BIT_ORDER::MSBFIRST)
        {
            bit_set = !!(val & (1U << (7 - bit)));
        }
        else
        {
            // Should assert here
        }

        GPIO_PinState pin_state = (bit_set) ? GPIO_PIN_SET : GPIO_PIN_RESET;
        HAL_GPIO_WritePin(m_data_pin.GPIOx, m_data_pin.GPIO_Pin, pin_state);

        // Create a clock pulse
        HAL_GPIO_WritePin(m_clock_pin.GPIOx, m_clock_pin.GPIO_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(m_clock_pin.GPIOx, m_clock_pin.GPIO_Pin, GPIO_PIN_RESET);
    }
}

void SN74HC595N_Shift_Reg::disable_latch(void)
{
    HAL_GPIO_WritePin(m_shift_pin.GPIOx, m_shift_pin.GPIO_Pin, GPIO_PIN_RESET);
}

void SN74HC595N_Shift_Reg::enable_latch(void)
{
    HAL_GPIO_WritePin(m_shift_pin.GPIOx, m_shift_pin.GPIO_Pin, GPIO_PIN_SET);
}

} /* namespace LEDM */
