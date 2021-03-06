#include "Menu.h"
#include "hd4480.h"
#include "work_values.h"
#include "out_dev.h"
#include "work_algorythm.h"

//strucure with settings for lcd initialization
void lcdMakeInitSettings();
void inputMenu(valueChange par);
void inputRepaint(uint16_t value);
void inputRepaintF(float value);
void actionRepaint(devstate acState);
void actionMenu(valueChange option);

LCD_InitTypeDef LCD_InitStr;
char* MAIN_MENU_TEXT = "������� ����";

static const menuItem  NULL_ENTRY = {(void*)0, (void*)0, (void*)0, (void*)0, SIMPLE,0, ""};
          //name   next     prev          parr        child
          //name   next     prev          parr        child
MAKE_MENU(m_Run, m_Sett, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY, SYSTEM, 0, "�����");
MAKE_MENU(m_Sett, NULL_ENTRY, m_Run, NULL_ENTRY, us_FireMode,  SIMPLE, 1, "���������");

//User settings sub menu
//us_FireMode, us_TempBoil, us_IgnTime, us_ChSCrewTime, us_CleanTime
MAKE_MENU(us_FireMode, us_TempBoil, NULL_ENTRY, m_Sett, us_FireModeChange, SIMPLE ,0, "����� �������");
   //sub menu to input
   MAKE_MENU(us_FireModeChange, NULL_ENTRY, NULL_ENTRY, us_FireMode, NULL_ENTRY, INPUT ,0, "����� �������");

MAKE_MENU(us_TempBoil, us_IgnTime, us_FireMode, m_Sett, us_TempBoilChange,  SIMPLE,1, "���-�� �����");
   //sub menu to input
   MAKE_MENU(us_TempBoilChange, NULL_ENTRY, NULL_ENTRY, us_TempBoil, NULL_ENTRY, INPUT ,0, "���-�� �����");

MAKE_MENU(us_IgnTime, us_TanTime, us_TempBoil, m_Sett, us_IgnTimeChange, SIMPLE, 2, "����� �������");
   //sub menu to input
   MAKE_MENU(us_IgnTimeChange, NULL_ENTRY, NULL_ENTRY, us_IgnTime, NULL_ENTRY, INPUT ,0, "����� �������");

MAKE_MENU(us_TanTime, us_FuelIgn, us_IgnTime, m_Sett, us_TanTimeChange, SIMPLE,3, "������ ����");
   //sub menu to input
   MAKE_MENU(us_TanTimeChange, NULL_ENTRY, NULL_ENTRY, us_TanTime, NULL_ENTRY, INPUT ,0, "������ ����");
	 
MAKE_MENU(us_FuelIgn, us_ScrewFilling, us_TanTime, m_Sett, us_FuelIgnChange, SIMPLE,4, "���-�� �������");
   //sub menu to input
   MAKE_MENU(us_FuelIgnChange, NULL_ENTRY, NULL_ENTRY, us_FuelIgn, NULL_ENTRY, INPUT ,0, "���-�� �����");
	 
MAKE_MENU(us_ScrewFilling, us_CleanPer, us_FuelIgn, m_Sett, us_ScrewFillingChange, SIMPLE,5, "�����-��� �����");
   //sub menu to input
   MAKE_MENU(us_ScrewFillingChange, NULL_ENTRY, NULL_ENTRY, us_ScrewFilling, NULL_ENTRY, INPUT ,0, "�����-��� �����");
	 
MAKE_MENU(us_CleanPer, us_CleanTime, us_ScrewFilling, m_Sett, us_CleanPerChange, SIMPLE,6, "������ ������");
   //sub menu to input
   MAKE_MENU(us_CleanPerChange, NULL_ENTRY, NULL_ENTRY, us_CleanPer, NULL_ENTRY, INPUT ,0, "������ ������");
	 
MAKE_MENU(us_CleanTime, us_FlameBright, us_CleanPer, m_Sett, us_CleanTimeChange,  SIMPLE,7, "����� ������");
   //sub menu to input
   MAKE_MENU(us_CleanTimeChange, NULL_ENTRY, NULL_ENTRY, us_CleanTime, NULL_ENTRY, INPUT ,0, "����� ������");
	 
MAKE_MENU(us_FlameBright, us_Diagnostic, us_CleanTime, m_Sett, us_FlameBrightChange, SIMPLE,8, "������� �������");
   //sub menu to input
   MAKE_MENU(us_FlameBrightChange, NULL_ENTRY, NULL_ENTRY, us_FlameBright, NULL_ENTRY, INPUT ,0, "������� �������");
   
MAKE_MENU(us_Diagnostic, NULL_ENTRY, us_FlameBright, m_Sett, d_ScrewTaker, SIMPLE,9, "�����������");

   /*Diagnostic sub menu*/
   MAKE_MENU(d_ScrewTaker, d_ScrewBurner, NULL_ENTRY, us_Diagnostic, d_ScrewTakerChange, SIMPLE,0, "���� ������");
      //sub menu to action
	   MAKE_MENU(d_ScrewTakerChange, NULL_ENTRY, NULL_ENTRY, d_ScrewTaker, NULL_ENTRY, ACTION,0, "���� ������");
		
   MAKE_MENU(d_ScrewBurner, d_Tan, d_ScrewTaker, us_Diagnostic, d_ScrewBurnerChange, SIMPLE,1, "���� �������");
         //sub menu to action
	   MAKE_MENU(d_ScrewBurnerChange, NULL_ENTRY, NULL_ENTRY, d_ScrewBurner, NULL_ENTRY, ACTION,0, "���� �������");
		
   MAKE_MENU(d_Tan, d_FireBar, d_ScrewBurner, us_Diagnostic, d_TanChange, SIMPLE,2, "���");
         //sub menu to action
	   MAKE_MENU(d_TanChange, NULL_ENTRY, NULL_ENTRY, d_Tan, NULL_ENTRY, ACTION,0, "���");
		 
   MAKE_MENU(d_FireBar, d_BoilerPump, d_Tan, us_Diagnostic, d_FireBarChange, SIMPLE,3, "��������");
         //sub menu to action
	   MAKE_MENU(d_FireBarChange, NULL_ENTRY, NULL_ENTRY, d_FireBar, NULL_ENTRY, ACTION,0, "��������");
		
   MAKE_MENU(d_BoilerPump, d_KettlePump, d_FireBar, us_Diagnostic, d_BoilerPumpChange, SIMPLE,4, "����� �������");
         //sub menu to action
	   MAKE_MENU(d_BoilerPumpChange, NULL_ENTRY, NULL_ENTRY, d_BoilerPump, NULL_ENTRY, ACTION,0, "����� �������");
		 
   MAKE_MENU(d_KettlePump, NULL_ENTRY, d_BoilerPump, us_Diagnostic, d_KettlePumpChange, SIMPLE,5, "����� �����");
	       //sub menu to action
	   MAKE_MENU(d_KettlePumpChange, NULL_ENTRY, NULL_ENTRY, d_KettlePump, NULL_ENTRY, ACTION,0, "����� �����");
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

	 if(activeItem->Select == INPUT)
		 {
			inputMenu(INC);
		 }
		 
	 else if(activeItem->Select == ACTION)
		 {
		  actionMenu(INC);
		 }
		 
	else //(activeItem->Select == SIMPLE)
	 {
		//get page number
		 int stPage = (activeItem->Index / FIELDS_NUMBER);
	  if((void*)activeItem->Previous == (void*)&NULL_ENTRY) return;
	   else activeItem = (void*)activeItem->Previous;
		
		//if we change a page we need to repaint display
		if(stPage != (activeItem->Index / FIELDS_NUMBER)) {stPage = (activeItem->Index / FIELDS_NUMBER); lcdRepaintMenu();}
		lcdMovePoint(activeItem->Index - (FIELDS_NUMBER*stPage));

	}
}
		 
 void moveDnMenu()
  {
		//get page number

	  if(activeItem->Select == INPUT)
		 {
			inputMenu(DEC);
		 }
		 
		 else if(activeItem->Select == ACTION)
		  {
			  actionMenu(DEC);
			}
			
		else //(activeItem->Select == SIMPLE)
		 {
		  volatile int stPage = (activeItem->Index / FIELDS_NUMBER);
		
 		  if((void*)activeItem->Next == (void*)&NULL_ENTRY) return;
	      else activeItem = (void*)activeItem->Next;
			
       //if we change a page we need to repaint display
		   if(stPage != (activeItem->Index / FIELDS_NUMBER)) {stPage = (activeItem->Index / FIELDS_NUMBER); lcdRepaintMenu();}
		   lcdMovePoint(activeItem->Index - (FIELDS_NUMBER*stPage));
	   }

  }
	
 void moveLfMenu()
  {
		/*save data if we are leaving input menu*/
		if(activeItem->Select == INPUT) writeToFlashMemory();
		if(activeItem->Select == ACTION) disableAll();
		
   if((void*)activeItem->Parent == (void*)&NULL_ENTRY) return;
	   else activeItem = (void*)activeItem->Parent;
		//repaitn display
		lcdRepaintMenu();
		volatile int stPage = (activeItem->Index / FIELDS_NUMBER);
		lcdMovePoint(activeItem->Index  - (FIELDS_NUMBER*stPage));
  }
	
 void moveRgMenu()
  {
		if(activeItem->Select == SYSTEM) 
		 {
       workState = START_WORK;
			 return;
		 }
		
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
		 
		 else if(activeItem->Select == ACTION) 
		 {
			 LCD_Clear();
			 actionMenu(ENTER);
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
				 if(++fire_mode.curVal > fire_mode.maxVal) fire_mode.curVal = fire_mode.minVal;
				  inputRepaint(fire_mode.curVal);
			 }
			
		 else if(activeItem == (void*)&us_TempBoilChange)
		   {
			   //change parameter of temperature of boiler
				 if(++temp_boil.curVal > temp_boil.maxVal) temp_boil.curVal = temp_boil.minVal;
				 inputRepaint(temp_boil.curVal);
				 
			 }			
		
		 else if(activeItem == (void*)&us_IgnTimeChange)
		   {
			   //change parameter of ignition time
				 if(++time_ign.curVal > time_ign.maxVal) time_ign.curVal = time_ign.minVal;
				 inputRepaint(time_ign.curVal);
			 }
		 else if(activeItem == (void*)&us_TanTimeChange)
		   {
			   //change parameter of tan time
				 if(++tan_work.curVal > tan_work.maxVal) tan_work.curVal = tan_work.minVal;
				 inputRepaint(tan_work.curVal);
			 }

		 else if(activeItem == (void*)&us_FuelIgnChange)
		   {
			   //change parameter of quantity ignition fuel
				 if(++fuel_ign.curVal > fuel_ign.maxVal) fuel_ign.curVal = fuel_ign.minVal;
				 inputRepaint(fuel_ign.curVal);
			 }
			
		 else if(activeItem == (void*)&us_ScrewFillingChange)
		   {
			   //change parameter of quantity ignition fuel
				 if(++screw_fill.curVal > screw_fill.maxVal) screw_fill.curVal = screw_fill.minVal;
				 inputRepaint(screw_fill.curVal);
			 }
			
		else if(activeItem == (void*)&us_CleanPerChange)
		  {
			  //change parameter of quantity ignition fuel
				if(++clean_per.curVal > clean_per.maxVal) clean_per.curVal = clean_per.minVal;
				inputRepaint(clean_per.curVal);
			}		

		else if(activeItem == (void*)&us_CleanTimeChange)
		  {
			  //change parameter of quantity ignition fuel
				clean_time += 0.01f;
				if(clean_time > clean_time_max) clean_time = clean_time_min;
				inputRepaintF(clean_time);
			}					
			
		else if(activeItem == (void*)&us_FlameBrightChange)
		  {
			  //change parameter of quantity ignition fuel
				if(++flame_bright.curVal > flame_bright.maxVal) flame_bright.curVal = flame_bright.minVal;
					inputRepaint(flame_bright.curVal);
			}
		}		
	 else if(par == DEC)
		{			
	   if(activeItem == (void*)&us_FireModeChange)
		   {
			  	//change parameter of fire mode
				 if(--fire_mode.curVal < fire_mode.minVal) fire_mode.curVal = fire_mode.maxVal;
				  inputRepaint(fire_mode.curVal);
			 }
			
		 else if(activeItem == (void*)&us_TempBoilChange)
		   {
			   //change parameter of temperature of boiler
				 if(--temp_boil.curVal < temp_boil.minVal) temp_boil.curVal = temp_boil.maxVal;
				 inputRepaint(temp_boil.curVal);
				 
			 }			
		
		 else if(activeItem == (void*)&us_IgnTimeChange)
		   {
			   //change parameter of ignition time
				 if(--time_ign.curVal < time_ign.minVal) time_ign.curVal = time_ign.maxVal;
				 inputRepaint(time_ign.curVal);
			 }
		 else if(activeItem == (void*)&us_TanTimeChange)
		   {
			   //change parameter of tan time
				 if(--tan_work.curVal < tan_work.maxVal) tan_work.curVal = tan_work.maxVal;
				 inputRepaint(tan_work.curVal);
			 }

		 else if(activeItem == (void*)&us_FuelIgnChange)
		   {
			   //change parameter of quantity ignition fuel
				 if(--fuel_ign.curVal < fuel_ign.minVal) fuel_ign.curVal = fuel_ign.maxVal;
				 inputRepaint(fuel_ign.curVal);
			 }
			
		 else if(activeItem == (void*)&us_ScrewFillingChange)
		   {
			   //change parameter of quantity ignition fuel
				 if(--screw_fill.curVal < screw_fill.minVal) screw_fill.curVal = screw_fill.maxVal;
				 inputRepaint(screw_fill.curVal);
			 }
			
		else if(activeItem == (void*)&us_CleanPerChange)
		  {
			  //change parameter of quantity ignition fuel
				if(--clean_per.curVal < clean_per.minVal) clean_per.curVal = clean_per.maxVal;
				inputRepaint(clean_per.curVal);
			}		

		else if(activeItem == (void*)&us_CleanTimeChange)
		  {
			  //change parameter of quantity ignition fuel
				clean_time -= 0.01f;
				if(clean_time < clean_time_min) clean_time = clean_time_max;
				inputRepaintF(clean_time);
			}					
			
		else if(activeItem == (void*)&us_FlameBrightChange)
		  {
			  //change parameter of quantity ignition fuel
				if(--flame_bright.curVal < flame_bright.minVal) flame_bright.curVal = flame_bright.maxVal;
					inputRepaint(flame_bright.curVal);
			}
		}			

	 else if(par == ENTER)
		{			
	   if(activeItem == (void*)&us_FireModeChange)
		   {
			  	//change parameter of fire mode
				 inputRepaint(fire_mode.curVal);
			 }
			
		 else if(activeItem == (void*)&us_TempBoilChange)
		   {
			   //change parameter of temperature of boiler
				 inputRepaint(temp_boil.curVal);
			 }			
		
		 else if(activeItem == (void*)&us_IgnTimeChange)
		   {
			   //change parameter of ignition time
				 inputRepaint(time_ign.curVal);
			 }
		 else if(activeItem == (void*)&us_TanTimeChange)
		   {
			   //change parameter of tan time
				 inputRepaint(tan_work.curVal);
			 }

		 else if(activeItem == (void*)&us_FuelIgnChange)
		   {
			   //change parameter of quantity ignition fuel
				 inputRepaint(fuel_ign.curVal);
			 }
			
		 else if(activeItem == (void*)&us_ScrewFillingChange)
		   {
			   //change parameter of quantity ignition fuel
				 inputRepaint(screw_fill.curVal);
			 }
			
		else if(activeItem == (void*)&us_CleanPerChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaint(clean_per.curVal);
			}		

		else if(activeItem == (void*)&us_CleanTimeChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaintF(clean_time);
			}					
			
		else if(activeItem == (void*)&us_FlameBrightChange)
		  {
			  //change parameter of quantity ignition fuel
				inputRepaint(flame_bright.curVal);
			}
		}				
	}
	
	inline void inputRepaint(uint16_t value)
	{
		//if need, we clear display
		LCD_Goto(1, 0);//print title
		LCD_Puts(activeItem->Text);
		LCD_Goto(2, 1);
		LCD_Puts("��������:");
		LCD_Putc(' ');
		LCD_PutUnsignedInt(value);//print value
	}
	
	inline void inputRepaintF(float value)
	{
		//if need, we clear display
		LCD_Goto(1, 0);//print title
		LCD_Puts(activeItem->Text);
		LCD_Goto(2, 1);
		LCD_Puts("��������:");
		LCD_Putc(' ');
		LCD_PutFloat(value);//print value
	}
	
	void actionMenu(valueChange option)
	{
	if(option != ENTER)
	{		
		/*change value and repaint on display*/
		if(activeItem == (void*)&d_ScrewTakerChange)
		 {
		   changeDevState(&screwTake);
			 actionRepaint(screwTake.CurrentState);
		 }
		 
		else if(activeItem == (void*)&d_ScrewBurnerChange)
		 {
		   changeDevState(&screwIgn);
			 actionRepaint(screwIgn.CurrentState);
		 }
		 
		else if(activeItem == (void*)&d_TanChange)
		 {
		   changeDevState(&outTan);
			 actionRepaint(outTan.CurrentState);
		 }
		 
		else if(activeItem == (void*)&d_FireBarChange)
		 {
		   changeDevState(&outFireBar);
			 actionRepaint(outFireBar.CurrentState);
		 }
		 
		 else if(activeItem == (void*)&d_BoilerPumpChange)
		 {
		   changeDevState(&outPumpBoil);
			 actionRepaint(outPumpBoil.CurrentState);
		 }
		 
		 else if(activeItem == (void*)&d_KettlePumpChange)
		 {
		   changeDevState(&outPumpCatl);
			 actionRepaint(outPumpCatl.CurrentState);
		 }
	 }
	else
	 {
	   /*when enter to action menu, show current state*/
		 if(activeItem == (void*)&d_ScrewTakerChange)
		 {
			 actionRepaint(screwTake.CurrentState);
		 }
		 
		else if(activeItem == (void*)&d_ScrewBurnerChange)
		 {
			 actionRepaint(screwIgn.CurrentState);
		 }
		 
		else if(activeItem == (void*)&d_TanChange)
		 {
       actionRepaint(outTan.CurrentState);
		 }
		 
		else if(activeItem == (void*)&d_FireBarChange)
		 {
       actionRepaint(outFireBar.CurrentState);
		 }
		 
		 else if(activeItem == (void*)&d_BoilerPumpChange)
		 {
       actionRepaint(outPumpBoil.CurrentState);
		 }
		 
		 else if(activeItem == (void*)&d_KettlePumpChange)
		 {
       actionRepaint(outPumpCatl.CurrentState);
		 }
	 }
	}
	
	inline void actionRepaint(devstate acState)
	 {
	   		//if need, we clear display
		LCD_Goto(1, 0);//print title
		LCD_Puts(activeItem->Text);
		LCD_Goto(2, 2);
		LCD_Puts("���������:");
		LCD_Puts("   ");
		LCD_Goto(12, 2);
		if(acState == ENABLE_STATE) LCD_Puts("���.");//print value
		else if(acState == DISABLE_STATE) LCD_Puts("����.");//print value
	 }