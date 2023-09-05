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

		SN74HC595N_Pin& operator=(SN74HC595N_Pin const& other)
		{
			GPIOx = other.GPIOx;
			GPIO_Pin = other.GPIO_Pin;
			return *this;
		}
	};

	enum SHIFT_BIT_ORDER
	{
		MSBFIRST,
		LSBFIRST
	};

	SN74HC595N_Shift_Reg(SN74HC595N_Pin const data_pin,
					     SN74HC595N_Pin const shift_pin,
						 SN74HC595N_Pin const clock_pin);
	~SN74HC595N_Shift_Reg();

	// Make an assignment operator
	SN74HC595N_Shift_Reg& operator=(SN74HC595N_Shift_Reg const& other);

	void disable_latch(void);
	void enable_latch(void);

	void shift_out(std::uint8_t bit_order, std::uint8_t val);

private:
	SN74HC595N_Pin m_data_pin;
	SN74HC595N_Pin m_shift_pin;
	SN74HC595N_Pin m_clock_pin;
};

} /* namespace LEDM */

#endif /* INC_SHIFT_REGISTER_H_ */
