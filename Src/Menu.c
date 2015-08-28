#include "Menu.h"
#include "hd4480.h"
#include "work_values.h"

//strucure with settings for lcd initialization
void lcdMakeInitSettings();
void inputMenu(valueChange par);
void inputRepaint(uint16_t value);
LCD_InitTypeDef LCD_InitStr;
char* MAIN_MENU_TEXT = "Главное меню";

static const menuItem  NULL_ENTRY = {(void*)0, (void*)0, (void*)0, (void*)0, SIMPLE,0, ""};
          //name   next     prev          parr        child
          //name   next     prev          parr        child
MAKE_MENU(m_Run, m_Sett, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY, SIMPLE, 0, "Старт");
MAKE_MENU(m_Sett, NULL_ENTRY, m_Run, NULL_ENTRY, us_FireMode,  SIMPLE, 1, "Настройки");

//User settings sub menu
//us_FireMode, us_TempBoil, us_IgnTime, us_ChSCrewTime, us_CleanTime
MAKE_MENU(us_FireMode, us_TempBoil, NULL_ENTRY, m_Sett, us_FireModeChange, SIMPLE ,0, "Режим горения");
   //sub menu to input
   MAKE_MENU(us_FireModeChange, NULL_ENTRY, NULL_ENTRY, us_FireMode, NULL_ENTRY, INPUT ,0, "Режим горения");

MAKE_MENU(us_TempBoil, us_IgnTime, us_FireMode, m_Sett, us_TempBoilChange,  SIMPLE,1, "Тем-ра котла");
   //sub menu to input
   MAKE_MENU(us_TempBoilChange, NULL_ENTRY, NULL_ENTRY, us_TempBoil, NULL_ENTRY, INPUT ,0, "Тем-ра котла");

MAKE_MENU(us_IgnTime, us_TanTime, us_TempBoil, m_Sett, us_IgnTimeChange, SIMPLE, 2, "Время розжига");
   //sub menu to input
   MAKE_MENU(us_IgnTimeChange, NULL_ENTRY, NULL_ENTRY, us_IgnTime, NULL_ENTRY, INPUT ,0, "Время розжига");

MAKE_MENU(us_TanTime, us_FuelIgn, us_IgnTime, m_Sett, us_TanTimeChange, SIMPLE,3, "Работа тэна");
   //sub menu to input
   MAKE_MENU(us_TanTimeChange, NULL_ENTRY, NULL_ENTRY, us_TanTime, NULL_ENTRY, INPUT ,0, "Работа тэна");
	 
MAKE_MENU(us_FuelIgn, us_ScrewFilling, us_TanTime, m_Sett, us_FuelIgnChange, SIMPLE,4, "Топ-во розжига");
   //sub menu to input
   MAKE_MENU(us_FuelIgnChange, NULL_ENTRY, NULL_ENTRY, us_FuelIgn, NULL_ENTRY, INPUT ,0, "Тем-ра котла");
	 
MAKE_MENU(us_ScrewFilling, us_CleanPer, us_FuelIgn, m_Sett, us_ScrewFillingChange, SIMPLE,5, "Запол-ние шнэка");
   //sub menu to input
   MAKE_MENU(us_ScrewFillingChange, NULL_ENTRY, NULL_ENTRY, us_ScrewFilling, NULL_ENTRY, INPUT ,0, "Запол-ние шнэка");
	 
MAKE_MENU(us_CleanPer, us_CleanTime, us_ScrewFilling, m_Sett, us_CleanPerChange, SIMPLE,6, "Период чистки");
   //sub menu to input
   MAKE_MENU(us_CleanPerChange, NULL_ENTRY, NULL_ENTRY, us_CleanPer, NULL_ENTRY, INPUT ,0, "Период чистки");
	 
MAKE_MENU(us_CleanTime, us_FlameBright, us_CleanPer, m_Sett, us_CleanTimeChange,  SIMPLE,7, "Время читски");
   //sub menu to input
   MAKE_MENU(us_CleanTimeChange, NULL_ENTRY, NULL_ENTRY, us_CleanTime, NULL_ENTRY, INPUT ,0, "Время чистки");
	 
MAKE_MENU(us_FlameBright, us_Diagnostic, us_CleanTime, m_Sett, us_FlameBrightChange, SIMPLE,8, "Яркость пламени");
   //sub menu to input
   MAKE_MENU(us_FlameBrightChange, NULL_ENTRY, NULL_ENTRY, us_FlameBright, NULL_ENTRY, INPUT ,0, "Яркость пламени");
   
MAKE_MENU(us_Diagnostic, NULL_ENTRY, us_FlameBright, m_Sett, d_ScrewTaker, SIMPLE,9, "Диагностика");

   /*Diagnostic sub menu*/
   MAKE_MENU(d_ScrewTaker, d_ScrewBurner, NULL_ENTRY, us_Diagnostic, NULL_ENTRY, SIMPLE,0, "Шнек подачи");
      //sub menu to action
	   MAKE_MENU(d_ScrewTakerChange, NULL_ENTRY, NULL_ENTRY, d_ScrewTaker, NULL_ENTRY, ACTION,0, "Шнек подачи");
		
   MAKE_MENU(d_ScrewBurner, d_Tan, d_ScrewTaker, us_Diagnostic, NULL_ENTRY, SIMPLE,1, "Шнек горелки");
         //sub menu to action
	   MAKE_MENU(d_ScrewBurnerChange, NULL_ENTRY, NULL_ENTRY, d_ScrewBurner, NULL_ENTRY, ACTION,0, "Шнек горелки");
		
   MAKE_MENU(d_Tan, d_FireBar, d_ScrewBurner, us_Diagnostic, NULL_ENTRY, SIMPLE,2, "Тэн");
         //sub menu to action
	   MAKE_MENU(d_TanChange, NULL_ENTRY, NULL_ENTRY, d_Tan, NULL_ENTRY, ACTION,0, "Тэн");
		 
   MAKE_MENU(d_FireBar, d_BoilerPump, d_Tan, us_Diagnostic, NULL_ENTRY, SIMPLE,3, "Колосник");
         //sub menu to action
	   MAKE_MENU(d_FireBarChange, NULL_ENTRY, NULL_ENTRY, d_FireBar, NULL_ENTRY, ACTION,0, "Колосник");
		
   MAKE_MENU(d_BoilerPump, d_KettlePump, d_FireBar, us_Diagnostic, NULL_ENTRY, SIMPLE,4, "Насос бойлера");
         //sub menu to action
	   MAKE_MENU(d_BoilerPumpChange, NULL_ENTRY, NULL_ENTRY, d_BoilerPump, NULL_ENTRY, ACTION,0, "Насос бойлера");
		 
   MAKE_MENU(d_KettlePump, NULL_ENTRY, d_BoilerPump, us_Diagnostic, NULL_ENTRY, SIMPLE,5, "Насос котла");
	       //sub menu to action
	   MAKE_MENU(d_KettlePumpChange, NULL_ENTRY, NULL_ENTRY, d_KettlePump, NULL_ENTRY, ACTION,0, "Насос котла");
//currentMenuItem
menuItem *activeItem, *prevItem ;

void lcdMakeInitSettings()
{
  LCD_InitStr.LineNumber = LCD_LineNumber_2Lines;
	LCD_InitStr.CharacterFont = LCD_CharacterFont_5x10Dots;
  LCD_InitStr.DataLength = LCD_DataLength_4Bit;
}

void lcdStartWorking()
{
	lcdMakeInitSettings();
	
	LCD_Init(&LCD_InitStr);
  LCD_Clear();
	
	activeItem = (void*)&m_Run;
}

void lcdRepaintMenu()
{
	LCD_Clear();
	/*
	 For first we print the name of parent menu
	*/
	if(activeItem->Parent == (void*)&NULL_ENTRY){
		 LCD_Goto(1, 0);
     LCD_Puts(MAIN_MENU_TEXT);
	 }
	else
	 {
		 menuItem *parItem = (void*)activeItem->Parent;
		 
	   LCD_Goto(1, 0);
     LCD_Puts(parItem->Text);
	 }
	
	 /*After that we print current item 
	  and two others besides it
	 */
			 menuItem *parItem = (void*)activeItem;
			 //come back to first item in current page
		   int i;
	     if(activeItem->Index <= FIELDS_NUMBER-1) i = activeItem->Index;//if we situated in 1-st page
	      else i = activeItem->Index % FIELDS_NUMBER;//if we situated in the one of others pages
	 
        for(; i > 0; i--)
          parItem = (void*)parItem->Previous;			 
			 //and print points items on display
       for(i = 0; i < FIELDS_NUMBER; i++)
			   {
			     LCD_Goto(2, i+1);
           LCD_Puts(parItem->Text);
					 if((void*)parItem->Next != (void*)&NULL_ENTRY) parItem = (void*)parItem->Next;
					 else break;
			   }
}

/*Moving through the menu*/
void moveUpMenu()
{
	if(activeItem->Select == SIMPLE)
	 {
		//get page number
		 int stPage = (activeItem->Index / FIELDS_NUMBER);
	  if((void*)activeItem->Previous == (void*)&NULL_ENTRY) return;
	   else activeItem = (void*)activeItem->Previous;
		
		//if we change a page we need to repaint display
		if(stPage != (activeItem->Index / FIELDS_NUMBER)) {stPage = (activeItem->Index / FIELDS_NUMBER); lcdRepaintMenu();}
		lcdMovePoint(activeItem->Index - (FIELDS_NUMBER*stPage));

	}
	 else if(activeItem->Select == INPUT)
		 {
			inputMenu(INC);
		 }
}
		 
 void moveDnMenu()
  {
		//get page number
	if(activeItem->Select == SIMPLE)
		{
		 volatile int stPage = (activeItem->Index / FIELDS_NUMBER);
		
 		 if((void*)activeItem->Next == (void*)&NULL_ENTRY) return;
	     else activeItem = (void*)activeItem->Next;
			
       //if we change a page we need to repaint display
		   if(stPage != (activeItem->Index / FIELDS_NUMBER)) {stPage = (activeItem->Index / FIELDS_NUMBER); lcdRepaintMenu();}
		   lcdMovePoint(activeItem->Index - (FIELDS_NUMBER*stPage));
	   }
	  else if(activeItem->Select == INPUT)
		 {
			inputMenu(DEC);
		 }

  }
	
 void moveLfMenu()
  {
   if((void*)activeItem->Parent == (void*)&NULL_ENTRY) return;
	   else activeItem = (void*)activeItem->Parent;
		//repaitn display
		lcdRepaintMenu();
		lcdMovePoint(activeItem->Index);
  }
	
 void moveRgMenu()
  {
	  if((void*)activeItem->Child == (void*)&NULL_ENTRY) return;
	   else activeItem = (void*)activeItem->Child;
		
		if(activeItem->Select == SIMPLE) 
		  {
				lcdRepaintMenu();
				lcdMovePoint(activeItem->Index);
			}
		 else if(activeItem->Select == INPUT) 
		 {
			 LCD_Clear();
			 inputMenu(ENTER);
		 }
 	}
	
	//Point moving
	void lcdMovePoint(uint8_t pos)
	{
		//clear points
		int i;
		for(i = 1; i <= 3; i++)
		{
		 LCD_Goto(1, i);
		 LCD_Putc(' ');
		}
		
		LCD_Goto(1, pos + 1);
		LCD_Putc('>');
	}
	
	void inputMenu(valueChange par)
	{
	 if(par == INC)
		{			
	   if(activeItem == (void*)&us_FireModeChange)
		   {
			  	//change parameter of fire mode
				  inputRepaint(++fire_mode);
			 }
			
		 else if(activeItem == (void*)&us_TempBoilChange)
		   {
			   //change parameter of temperature of boiler
				 inputRepaint(++temp_boil);
				 
			 }			
		
		 else if(activeItem == (void*)&us_IgnTimeChange)
		   {
			   //change parameter of ignition time
				 inputRepaint(++time_ign);
			 }
		 else if(activeItem == (void*)&us_TanTimeChange)
		   {
			   //change parameter of tan time
				 inputRepaint(++tan_work);
			 }

		 else if(activeItem == (void*)&us_FuelIgnChange)
		   {
			   //change parameter of quantity ignition fuel
				 inputRepaint(++fuel_ign);
			 }
			
		 else if(activeItem == (void*)&us_ScrewFillingChange)
		   {
			   //change parameter of quantity ignition fuel
				 inputRepaint(++screw_fill);
			 }
			
		else if(activeItem == (void*)&us_CleanPerChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaint(++clean_per);
			}		

		else if(activeItem == (void*)&us_CleanTimeChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaint(++clean_time);
			}					
			
		else if(activeItem == (void*)&us_FlameBrightChange)
		  {
			  //change parameter of quantity ignition fuel
					inputRepaint(++flame_bright);
			}
		}		
	 else if(par == DEC)
		{			
	   if(activeItem == (void*)&us_FireModeChange)
		   {
			  	//change parameter of fire mode
				 inputRepaint(--fire_mode);
			 }
			
		 else if(activeItem == (void*)&us_TempBoilChange)
		   {
			   //change parameter of temperature of boiler
				 inputRepaint(--temp_boil);
			 }			
		
		 else if(activeItem == (void*)&us_IgnTimeChange)
		   {
			   //change parameter of ignition time
				 inputRepaint(--time_ign);
			 }
		 else if(activeItem == (void*)&us_TanTimeChange)
		   {
			   //change parameter of tan time
				 inputRepaint(--tan_work);
			 }

		 else if(activeItem == (void*)&us_FuelIgnChange)
		   {
			   //change parameter of quantity ignition fuel
				 inputRepaint(--fuel_ign);
			 }
			
		 else if(activeItem == (void*)&us_ScrewFillingChange)
		   {
			   //change parameter of quantity ignition fuel
				 inputRepaint(--screw_fill);
			 }
			
		else if(activeItem == (void*)&us_CleanPerChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaint(--clean_per);
			}		

		else if(activeItem == (void*)&us_CleanTimeChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaint(--clean_time);
			}					
			
		else if(activeItem == (void*)&us_FlameBrightChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaint(--flame_bright);
			}
		}			

	 else if(par == ENTER)
		{			
	   if(activeItem == (void*)&us_FireModeChange)
		   {
			  	//change parameter of fire mode
				 inputRepaint(fire_mode);
			 }
			
		 else if(activeItem == (void*)&us_TempBoilChange)
		   {
			   //change parameter of temperature of boiler
				 inputRepaint(temp_boil);
			 }			
		
		 else if(activeItem == (void*)&us_IgnTimeChange)
		   {
			   //change parameter of ignition time
				 inputRepaint(time_ign);
			 }
		 else if(activeItem == (void*)&us_TanTimeChange)
		   {
			   //change parameter of tan time
				 inputRepaint(tan_work);
			 }

		 else if(activeItem == (void*)&us_FuelIgnChange)
		   {
			   //change parameter of quantity ignition fuel
				 inputRepaint(fuel_ign);
			 }
			
		 else if(activeItem == (void*)&us_ScrewFillingChange)
		   {
			   //change parameter of quantity ignition fuel
				 inputRepaint(screw_fill);
			 }
			
		else if(activeItem == (void*)&us_CleanPerChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaint(clean_per);
			}		

		else if(activeItem == (void*)&us_CleanTimeChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaint(clean_time);
			}					
			
		else if(activeItem == (void*)&us_FlameBrightChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaint(flame_bright);
			}
		}				
	}
	
	inline void inputRepaint(uint16_t value)
	{
		//if need, we clear display
		LCD_Goto(1, 0);//print title
		LCD_Puts(activeItem->Text);
		LCD_Goto(3, 1);
		LCD_Puts("Параметр:");
		LCD_Putc(' ');
		LCD_PutUnsignedInt(value);//print value
	}
	
	void actionMenu()
	{
		
	}