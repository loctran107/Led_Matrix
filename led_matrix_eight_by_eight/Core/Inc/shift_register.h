/*
 * shift_register.h
 *
 *  Created on: Aug 20, 2023
 *      Author: donovantran
 */

#ifndef INC_SHIFT_REGISTER_H_
#define INC_SHIFT_REGISTER_H_

#include <cstdint>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

namespace LEDM
{

class SN74HC595N_Shift_Reg
{
public:
	
	struct SN74HC595N_Pin
	{
		GPIO_TypeDef* GPIOx;
		std::uint16_t GPIO_Pin;
	};

	SN74HC595N_Shift_Reg(SN74HC595N_Pin const data_pin,
						 SN74HC595N_Pin const clock_pin,
						 SN74HC595N_Pin const shift_pin);
	~SN74HC595N_Shift_Reg();

private:
	SN74HC595N_Pin m_data_pin;
	SN74HC595N_Pin m_clock_pin;
	SN74HC595N_Pin m_shift_pin;
};

} /* namespace LEDM */

#endif /* INC_SHIFT_REGISTER_H_ */
