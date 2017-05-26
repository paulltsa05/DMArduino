/*
 * string_command.h
 *
 *  Created on: 12-Apr-2016
 *      Author: kpit
 */

#ifndef STRING_COMMAND_H_
#define STRING_COMMAND_H_

#include <stdbool.h>
#include <stdint.h>

struct string_letter {
	uint8_t XH;
	uint8_t XL;
	uint8_t YH;
	uint8_t YL;
	uint8_t Letter;
}__attribute__ ((packed));

struct string_str {
	uint8_t XH;
	uint8_t XL;
	uint8_t YH;
	uint8_t YL;
	uint8_t strLenth;
}__attribute__ ((packed));

struct string_color {
	uint8_t Color_R;
	uint8_t Color_G;
	uint8_t Color_B;
}__attribute__ ((packed));

struct set_font{
	
	uint8_t TextSize;
}__attribute__ ((packed));

struct draw_box {
	uint8_t X;
	uint8_t Y;
	uint8_t Width;
	uint8_t Height;
}__attribute__ ((packed));


#endif /* STRING_COMMAND_H_ */
