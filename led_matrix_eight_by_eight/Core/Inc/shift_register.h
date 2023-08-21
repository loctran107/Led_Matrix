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

class SN74HC595N_Shift_Reg
{
public:
	SN74HC595N_Shift_Reg(GPIO_TypeDef* GPIOx, std::uint16_t GPIO_Pin);
	~SN74HC595N_Shift_Reg();

private:
	GPIO_TypeDef* m_GPIOx;
	std::uint16_t m_GPIO_Pin;
};

#endif /* INC_SHIFT_REGISTER_H_ */
