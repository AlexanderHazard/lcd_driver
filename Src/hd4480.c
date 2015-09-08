#include "hd4480.h"
#include <stdio.h>
#include <math.h>

void LCD_LowLevel_Init();
void LCD_WriteCommand(uint8_t n);
void LCD_WriteData(uint8_t n);


const unsigned char kirilTable[64]= {
0x41, 0xA0, 0x42, 0xA1, 0xE0, 0x45, 0xA3, 0xA4, 0xA5, 0xA6, 0x4B, 0xA7, 0x4D, 0x48, 0x4F, 0xA8,
0x50, 0x43, 0x54, 0xA9, 0xAA, 0x58, 0xE1, 0xAB, 0xAC, 0xE2, 0xAD, 0xAE, 0xAD, 0xAF, 0xB0, 0xB1,
0x61, 0xB2, 0xB3, 0xB4, 0xE3, 0x65, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x6F, 0xBE,
0x70, 0x63, 0xBF, 0x79, 0xE4, 0x78, 0xE5, 0xC0, 0xC1, 0xE6, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7};

void LCD_Init(LCD_InitTypeDef *LCD_InitStruct)
{
	uint8_t ctrl, i;

	ctrl = LCD_PFX_FunctionSet |
		   LCD_InitStruct->DataLength |
		   LCD_InitStruct->LineNumber |
		   LCD_InitStruct->CharacterFont;

	LCD_LowLevel_Init();

	LCD_EN_LOW();
	LCD_RS_LOW();

	HAL_Delay(15);

	for (i = 0; i < 3; i++)
	{
		LCD_SendNibble(3);
		HAL_Delay(5);
	}

	LCD_SendNibble(2);
	HAL_Delay(5);


	LCD_SendByte(0, ctrl);

	ctrl = LCD_PFX_DisplayOnOff |
		   LCD_DisplayState_On |
		   LCD_CursorState_Off |
		   LCD_BlinkCursor_Off;

	LCD_SendByte(0, ctrl);

	ctrl = LCD_CMD_ClearDisplay;

	LCD_SendByte(0, ctrl);

	ctrl = LCD_PFX_EntryModeSet |
		   LCD_CursorDirection_Increment |
		   LCD_DisplayShift_NoShift;

	LCD_SendByte(0, ctrl);

}

void LCD_Clear(void)
{
	LCD_SendByte(0, LCD_CMD_ClearDisplay);
	LCD_SendByte(0, LCD_CMD_CursorHome);
}

void LCD_SendNibble(uint8_t n)
{
	HAL_GPIO_WritePin(LCD_PORT, LCD_D4, GET_BIT(n,0));
	HAL_GPIO_WritePin(LCD_PORT, LCD_D5, GET_BIT(n,1));
	HAL_GPIO_WritePin(LCD_PORT, LCD_D6, GET_BIT(n,2));
	HAL_GPIO_WritePin(LCD_PORT, LCD_D7, GET_BIT(n,3));

	HAL_Delay(1);
	LCD_EN_HIGH();
	HAL_Delay(1);
	LCD_EN_LOW();
}

/*send bytes through the lines D4 - D7*/
void LCD_SendByte(uint8_t address, uint8_t n)
{
	if (address == 0) LCD_RS_LOW();
	else if(address == 1) LCD_RS_HIGH();
	HAL_Delay(1);
	LCD_SendNibble(n >> 4);
	LCD_SendNibble(n & 0xf);
}

//LCD- send dram data
void LCD_SetDdramAddress(uint8_t address)
{
	LCD_SendByte(0, address | LCD_PFX_DdramSetAddress);
}

void LCD_SetCgramAddress(uint8_t address)
{
	LCD_SendByte(0, address | LCD_PFX_CgramSetAddress);
}

void LCD_Goto(uint8_t cx, uint8_t cy)
{
	uint8_t address;
	if (cy == 1)
		address = LCD_LINE_TWO_ADDR;

	else if (cy == 3)
		address = LCD_LINE_FOUR_ADDR;

	else if (cy == 0)
		address = LCD_LINE_ONE_ADDR;

	else if (cy == 2)
		 address = LCD_LINE_THREE_ADDR;

	address += cx - 1;

	LCD_SetDdramAddress(address);
}

void LCD_WriteCustomCharacter(uint8_t num, const uint8_t c[])
{
	uint8_t i;
	if(num < 7)
	{
		LCD_SendByte(0, 0x40 | (num << 3));
		for(i = 0; i < 8; i++)
			LCD_SendByte(1, c[i]);
		LCD_SetDdramAddress(0);
	}
}

void LCD_Putc(char c)
{
	
	//printf("Test");
	switch (c) {
		case '\a':
			LCD_Goto(1, 1);
			break;
		case '\f':
			LCD_SendByte(0, LCD_CMD_ClearDisplay);
			HAL_Delay(2);
			break;
		case '\n':
			LCD_Goto(1, 2);
			break;
		case '\b':
			LCD_SendByte(0, 0x10);
			break;
		default:
			if (c > 0x7F) {c = kirilTable[c - 0xC0];}
			LCD_SendByte(1, c);
			break;
	}
}

void LCD_Puts(const char *s)
{
	const char *p = s;
	while(*p != 0)
	{
		LCD_Putc(*p);
		p++;
	}
}

void LCD_PutSignedInt(int32_t n)
{
	char c1[32];

	if(n == 0)
	{
		LCD_Putc('0');
		return;
	}

	signed int value = n;
	unsigned int absolute;

	int i = 0;

	if(value < 0) {
		absolute = -value;
	} else {
		absolute = value;
	}

	while (absolute > 0) {
		c1[i] = '0' + absolute % 10;
		absolute /= 10;
		i++;
	}

	LCD_Putc((value < 0) ? '-' : '+');

	i--;

	while(i >= 0){
		LCD_Putc(c1[i--]);
	}
}

void LCD_PutUnsignedInt(uint32_t n)
{
	char c1[32];
	uint32_t value = n;
	uint32_t i = 0;

	if(n == 0)
	{
		LCD_Putc('0');
		LCD_Putc('0');
		return;
	}

	while (value > 0) {
		c1[i] = '0' + value % 10;
		value /= 10;
		i++;
	}

	if (n < 10) LCD_Putc('0');

	while(i-- > 0){
		LCD_Putc(c1[i]);
	}
}

void LCD_PutFloat(float val)
{
  double fract, intpart;
	fract = modf(val, &intpart);
	
	if(val < 0) LCD_Putc('-');
	LCD_PutUnsignedInt(intpart);
	LCD_Putc('.');
	fract *= 100;
	LCD_PutUnsignedInt(fract);
}

void LCD_EntryModeCommand(LCD_EntryModeCmdTypeDef *LCD_EntryModeCmdStruct)
{
	uint8_t ctrl;
	ctrl = LCD_PFX_EntryModeSet |
		   LCD_EntryModeCmdStruct->CursorDirection |
		   LCD_EntryModeCmdStruct->DisplayShift;
	LCD_SendByte(0, ctrl);
}

void LCD_DisplayOnOffCommand(LCD_DisplayOnOffCmdTypedef *LCD_DisplayOnOffStruct)
{
	uint8_t ctrl;
	ctrl = LCD_PFX_DisplayOnOff |
		   LCD_DisplayOnOffStruct->BlinkCursor |
		   LCD_DisplayOnOffStruct->CursorState |
		   LCD_DisplayOnOffStruct->DisplayState;
	LCD_SendByte(0, ctrl);
}

void LCD_CursorDisplayShiftCommand(
		LCD_CursorDisplayShiftCmdTypeDef *LCD_CursorDisplayShiftStruct)
{
	uint8_t ctrl;
	ctrl = LCD_PFX_CursorDisplayShift |
		   LCD_CursorDisplayShiftStruct->MoveOrShift |
		   LCD_CursorDisplayShiftStruct->ShiftDirection;
	LCD_SendByte(0, ctrl);
}

void LCD_LowLevel_Init()
{
   GPIO_InitTypeDef GPIO_InitStruct;
	
	 LCD_RCC();
	
	//speed and mode are common for all pins
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pin = LCD_RS | LCD_EN | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
	HAL_GPIO_Init(LCD_PORT, &GPIO_InitStruct);
}