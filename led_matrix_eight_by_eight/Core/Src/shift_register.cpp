/*
 * shift_register.cpp
 *
 *  Created on: Aug 20, 2023
 *      Author: donovantran
 */
#include "shift_register.h"

#include <cstdint>

SN74HC595N_Shift_Reg::SN74HC595N_Shift_Reg(GPIO_TypeDef* GPIOx, std::uint16_t GPIO_Pin)
    : m_GPIOx(GPIOx), m_GPIO_Pin(GPIO_Pin)
{
}

SN74HC595N_Shift_Reg::~SN74HC595N_Shift_Reg()
{
}
