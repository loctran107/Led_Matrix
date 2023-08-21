/*
 * shift_register.cpp
 *
 *  Created on: Aug 20, 2023
 *      Author: donovantran
 */
#include "shift_register.h"

#include <cstdint>

namespace LEDM
{
SN74HC595N_Shift_Reg::SN74HC595N_Shift_Reg(SN74HC595N_Pin const data_pin, 
                                           SN74HC595N_Pin const clock_pin,
                                           SN74HC595N_Pin const shift_pin)
    : m_data_pin(data_pin)
    , m_clock_pin(clock_pin)
    , m_shift_pin(shift_pin)
{
}

SN74HC595N_Shift_Reg::~SN74HC595N_Shift_Reg()
{
}

} /* namespace LEDM */
