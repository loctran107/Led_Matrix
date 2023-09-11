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
#include <string>
#include <iterator>
#include <algorithm>

#include "shift_register.h"
#include "led_matrix_alphabet.h"
namespace LEDM
{

LedMatrix::LedMatrix(unsigned col, unsigned row) : m_col(col), m_row(row)
{
    // init_led_animation();

    setup_col_shift_reg();
    setup_row_shift_reg();
}

LedMatrix::~LedMatrix()
{
}

void LedMatrix::rotate_matrix_90_degree_counterclockwise(std::uint8_t const * letter_bitmap)
{
    // Transform the matrix by 90 degree
    for (unsigned col = 0; col < m_col; ++col)
    {
        std::uint8_t val { 0x0U };
        for (unsigned row = 0; row < m_row; ++row)
        {
            bool is_bit_on = (letter_bitmap[row] & (1U << col));
            if (is_bit_on)
            {
                val |= (1U << (m_row - 1 - row));
            }
            else
            {
                val &= ~(1U << (m_row - 1 - row));
            }
        }

        m_rotated_90_degree_counterclockwise_bitmap[col] = val;
    }
}

void LedMatrix::rotate_matrix_90_degree_clockwise(std::uint8_t const * letter_bitmap)
{
    for (unsigned col = 0; col < m_col; ++col)
    {
        std::uint8_t val { 0x0U};
        for (unsigned row = 0; row < m_row; ++row)
        {
            bool is_bit_on = (letter_bitmap[row] & (1U << (m_col - 1 - col)));
            if (is_bit_on)
            {
                val |= (1U << row);
            }
            else
            {
                val &= ~(1U << row);
            }
        }

        m_led_frame_non_transformed[col] = val;
    }
}

void LedMatrix::init_led_animation(void)
{
    // The number of frame suppported is set to be equal to
    // the number of col because this specific setup aims for the
    // scrolling LED effects
    // for (unsigned row = 0; row < m_row; ++row)
    // {
    //     m_led_frame_non_transformed.push_back(0x0U);
    //     m_led_frame_transformed.push_back(0x0U);
    // }
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

void LedMatrix::produce_frame(unsigned const row, unsigned const col)
{
    // Traversing each column of the letter bitmap to extract
    // the bit of each row and plot them into a frame. Starting
    // from the MSB.
    bool is_bit_on = (m_rotated_90_degree_counterclockwise_bitmap[row] & (1U << (STANDARD_LETTER_LENGTH - 1 - col)));
    
    // Always map the first bit of each row with the corresponding value
    if (is_bit_on)
    {
        m_led_frame_transformed[row] |= 1U; // Turn on the rightmost bit of that row
    }
    else
    {
        m_led_frame_transformed[row] &= ~(1U); // Turn off the rightmost bit of that row
    }
}

void LedMatrix::display_frame(void)
{
    // Display all of the rows in each frame
    for (unsigned row = 0; row < m_row; ++row)
    {   
        m_row_shift_reg->disable_latch();
        m_row_shift_reg->shift_out(SN74HC595N_Shift_Reg::SHIFT_BIT_ORDER::MSBFIRST, (1U << row));

        m_col_shift_reg->disable_latch();
        m_col_shift_reg->shift_out(SN74HC595N_Shift_Reg::SHIFT_BIT_ORDER::MSBFIRST, m_led_frame_non_transformed[row]);

        m_col_shift_reg->enable_latch();
        m_row_shift_reg->enable_latch();

        HAL_Delay(1); // 1ms delay to smooth out the pattern
    }
}

void LedMatrix::shift_frame_left(void)
{
    for (unsigned row = 0; row < m_row; ++row)
    {
        m_led_frame_transformed[row] = (m_led_frame_transformed[row] << 1);
    }
}

void LedMatrix::display(std::string const message, unsigned const scrolling_speed)
{
    for (unsigned char_indx = 0; char_indx < message.length(); ++char_indx)
    {
        unsigned alphabet_indx = message[char_indx] - ' ';
        std::uint8_t * letter_bitmap = Led_matrix_alphabet[alphabet_indx];
        rotate_matrix_90_degree_counterclockwise(letter_bitmap);
    
        // Plot the Letter to display on the LED Frame
        // Plot each row of the bitmap to the frame, starting
        // from the MSB bit
        for (unsigned col = 0; col < m_col; ++col)
        {
            for (unsigned row = 0; row < m_row; ++row)
            {
                produce_frame(row, col);
            }

            rotate_matrix_90_degree_clockwise(m_led_frame_transformed);
            unsigned current_speed = scrolling_speed;
            while ((current_speed--) > 0)
            {
                display_frame();
            }

            shift_frame_left();
        }
    }
}

void LedMatrix::display_letter_A(std::string const message, unsigned const scrolling_speed)
{
    // std::uint8_t Letter_A[STANDARD_LETTER_LENGTH] = {0x18, 0x3C, 0x66, 0x7E, 0x7E, 0x66, 0x66, 0x66}; // A

    // // Plot the Letter to display on the LED Frame
    // // Plot each row of the bitmap to the frame, starting
    // // from the MSB bit
    // for (unsigned col = 0; col < m_col; ++col)
    // {
    //     for (unsigned row = 0; row < m_row; ++row)
    //     {
    //         // Traversing each column of the letter bitmap to extract
    //         // the bit of each row and plot them into a frame. Starting
    //         // from the MSB.
    //         bool is_bit_on = (Letter_A[row] & (1U << (m_col - 1 - col)));
    //         produce_frame(is_bit_on, row);
    //     }

    //     unsigned current_speed = scrolling_speed;
    //     while ((current_speed--) > 0)
    //     {
    //         display_frame();
    //     }

    //     shift_frame_left();
    // }
}

} /* namespace LEDM */
