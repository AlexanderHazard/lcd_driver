/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WORK_ALGORYTHM_H
#define __WORK_ALGORYTHM_H
   typedef enum {FREE , START_WORK, END_WORK} controll_state;
   extern controll_state workState;
	 void secTimCallback();
   void alWorkSystem();

#endif