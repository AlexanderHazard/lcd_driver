/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HD4480_H
#define __HD4480_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

//redefenition ports for LCD pins using
#define LCD_PORT GPIOC
#define LCD_RCC()  __GPIOC_CLK_ENABLE()

#define LCD_RS GPIO_PIN_0 //RS
#define LCD_EN GPIO_PIN_1 //Enable pin
#define LCD_D4 GPIO_PIN_5
#define LCD_D5 GPIO_PIN_6
#define LCD_D6 GPIO_PIN_8
#define LCD_D7 GPIO_PIN_9

#define LCD_LINE_LENGTH					  (uint8_t)16
#define LCD_LINE_ONE_ADDR				  (uint8_t)0
#define LCD_LINE_TWO_ADDR				  (uint8_t)64
#define LCD_LINE_THREE_ADDR				(uint8_t)16
#define LCD_LINE_FOUR_ADDR				(uint8_t)80

#define LCD_EN_LOW()					HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_RESET)
#define LCD_EN_HIGH()					HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_SET)

#define LCD_RS_LOW()					HAL_GPIO_WritePin(LCD_PORT, LCD_RS, GPIO_PIN_RESET)
#define LCD_RS_HIGH()					HAL_GPIO_WritePin(LCD_PORT, LCD_RS, GPIO_PIN_SET)


/*  LCD_Constants  */
#define LCD_DataLength_4Bit				(uint8_t)0

#define LCD_LineNumber_1Line			(uint8_t)0
#define LCD_LineNumber_2Lines			(uint8_t)8

#define LCD_CharacterFont_5x8Dots		(uint8_t)0
#define LCD_CharacterFont_5x10Dots		(uint8_t)4

#define LCD_CursorDirection_Decrement	(uint8_t)0
#define LCD_CursorDirection_Increment	(uint8_t)2

#define LCD_DisplayShift_NoShift		(uint8_t)0
#define LCD_DisplayShift_Shift			(uint8_t)1

#define LCD_DisplayState_On				(uint8_t)4
#define LCD_DisplayState_Off			(uint8_t)0

#define LCD_CursorState_On				(uint8_t)2
#define LCD_CursorState_Off				(uint8_t)0

#define LCD_BlinkCursor_On				(uint8_t)1
#define LCD_BlinkCursor_Off				(uint8_t)0

#define LCD_MoveOrShift_MoveCursor		(uint8_t)0
#define LCD_MoveOrShift_ShiftDisplay	(uint8_t)8

#define LCD_ShiftDirection_Left			(uint8_t)0
#define LCD_ShiftDirection_Right		(uint8_t)4

/*  LCD Commands  */
#define LCD_CMD_ClearDisplay			(uint8_t)1
#define LCD_CMD_CursorHome				(uint8_t)2

/*  LCD Command prefixes  */
#define LCD_PFX_EntryModeSet			(uint8_t)4
#define LCD_PFX_DisplayOnOff			(uint8_t)8
#define LCD_PFX_CursorDisplayShift		(uint8_t)16
#define LCD_PFX_FunctionSet				(uint8_t)32
#define LCD_PFX_CgramSetAddress			(uint8_t)64
#define LCD_PFX_DdramSetAddress			(uint8_t)128

#define GET_BIT(a, b)					((a >> b) & 1)

/*  Structures  */
typedef struct
{
	uint8_t DataLength;			/*  LCD communication bus length. Only 4-bit supported yet  */
	uint8_t LineNumber;			/*  Number of lines displayed on LCD.  */
	uint8_t CharacterFont;		/*  Displayed character font  */
}LCD_InitTypeDef;

typedef struct
{
	uint8_t CursorDirection;	/*  Cursor move direction during data read/write  */
	uint8_t DisplayShift;		/*  Specifies display shift during data read/write  */
}LCD_EntryModeCmdTypeDef;

typedef struct
{
	uint8_t DisplayState;		/*  Display on/off control  */
	uint8_t CursorState;		/*  Cursor on/off control  */
	uint8_t BlinkCursor;		/*  Blinking at cursor position character on/off control  */
}LCD_DisplayOnOffCmdTypedef;

typedef struct
{
	uint8_t MoveOrShift;		/*  Specifies preferred printing mode  */
	uint8_t ShiftDirection;		/*  Specifies display shifting direcion if shifting on  */
}LCD_CursorDisplayShiftCmdTypeDef;

//Functions
void LCD_Init(LCD_InitTypeDef *LCD_InitStruct);
void LCD_Clear(void);
void LCD_SendNibble(uint8_t n);
void LCD_SendByte(uint8_t address, uint8_t n);
void LCD_SetDdramAddress(uint8_t address);
void LCD_SetCgramAddress(uint8_t address);
void LCD_Goto(uint8_t cx, uint8_t cy);
void LCD_WriteCustomCharacter(uint8_t num, const uint8_t *c);
void LCD_Putc(char c);
void LCD_Puts(const char *s);
void LCD_PutSignedInt(int32_t value);
void LCD_PutUnsignedInt(uint32_t value);
void LCD_PutFloat(float val);
void LCD_EntryModeCommand(LCD_EntryModeCmdTypeDef *LCD_EntryModeCmdStruct);
void LCD_DisplayOnOffCommand(LCD_DisplayOnOffCmdTypedef *LCD_DisplayOnOffStruct);
void LCD_CursorDisplayShiftCommand(LCD_CursorDisplayShiftCmdTypeDef *LCD_CursorDisplayShiftStruct);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/