/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MENU_H
#define __MENU_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

typedef enum {SIMPLE, ACTION, INPUT, ADMIN} itemOption;
typedef enum {INC, DEC} valueChange;

typedef struct PROGMEM{
	struct menuItem  *Next;
	struct menuItem  *Previous;
	struct menuItem  *Parent;
	struct menuItem  *Child;
	const  itemOption Select;
	const  uint8_t    Index;
	const char*  Text;
} menuItem;



#define MAKE_MENU(Name, Next, Previous, Parent, Child, Options, Index, Text) \
   extern const menuItem Next;     \
   extern const menuItem Previous; \
   extern const menuItem Parent;   \
   extern const menuItem Child;    \
   const menuItem  Name = {(void*)&Next, (void*)&Previous, (void*)&Parent, (void*)&Child, Options, Index,  Text }
	 

	 
	 //gui output
	 void lcdStartWorking();
	 void lcdRepaintMenu();
	 
	 //moving through menu
	 void moveUpMenu();
	 void moveDnMenu();
	 void moveLfMenu();
	 void moveRgMenu();
	 
	 void lcdMovePoint(uint8_t pos);
	 
	 //fields count on display for Items
	 #define FIELDS_NUMBER 3
	 

#endif