/*
 * sct.c
 *
 *  Created on: Oct 11, 2023
 *      Author: xknobm00
 */

#include "main.h"
#include "sct.h"

void sct_init(void)
{
	sct_led(0);
}

void sct_led(uint32_t value)
{
	for(uint8_t i = 0; i < 32; i++){
		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin,(value & 1));
		value >>= 1;
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
	}
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);
}


static const uint32_t reg_values[3][10] = {
	{
		//PCDE--------GFAB @ DIS1
		0b0010000000000000 << 16,
		0b0001000000000000 << 16,
		0b0000000000000100 << 16,
		0b0000000000000010 << 16,
		0b0000000000000000 << 16,
		0b0000000000000000 << 16,
		0b0000000000000000 << 16,
		0b0000000000000000 << 16,
		0b0000000000000000 << 16,
		0b0000000000000000 << 16,
	},
	{
		//----PCDEGFAB---- @ DIS2
		0b0000000000000000 << 0,
		0b0000000000000000 << 0,
		0b0000000000000000 << 0,
		0b0000000000000000 << 0,
		0b0000000000100000 << 0,
		0b0000000000000000 << 0,
		0b0000000000000000 << 0,
		0b0000000000000000 << 0,
		0b0000000000000000 << 0,
		0b0000001000000000 << 0,
	},
	{
		//PCDE--------GFAB @ DIS3
		0b0000000000000000 << 0,
		0b0000000000000000 << 0,
		0b0000000000000000 << 0,
		0b0000000000000000 << 0,
		0b0000000000000000 << 0,
		0b0000000000000010 << 0,
		0b0000000000000001 << 0,
		0b0100000000000000 << 0,
		0b0010000000000000 << 0,
		0b0000000000000000 << 0,
	},
};

void sct_value(uint16_t value)
{
	uint32_t reg=0;
	reg |= reg_values[0][value / 100 % 10];
	reg |= reg_values[1][value / 10 % 10];
	reg |= reg_values[2][value % 10];

	sct_led(reg);

}
