/*
 * OS_program.c
 *
 *  Created on: Feb 1, 2023
 *      Author: speedTECH
 */

#include "../../00-LIB/STD_TYPES.h"
#include "../../00-LIB/Bit_Math.h"

#include "../../01-MCAL/03-STK/STK_interface.h"
#include "../../01-MCAL/11-USART/USART_interface.h"
#include "OS_config.h"
#include "OS_interface.h"
#include "OS_private.h"
/*Array of structures of type task */
static Task_t Global_OSTasks[NUMBER_OF_TASKS]={0};


void OS_CreateTask(u8 Copy_u8ID, u16 Copy_u16Periodicity, void (*ptr)(void),u16 Copy_u16FirstDelay)
{
	Global_OSTasks[Copy_u8ID].u16_Periodicity=Copy_u16Periodicity;
	Global_OSTasks[Copy_u8ID].Funptr=ptr;
	Global_OSTasks[Copy_u8ID].u16_FirstDelay=Copy_u16FirstDelay;
}

void OS_voidStart(void)
{
	MSTK_voidClkSrcInit();
	/*Tick =1ms*/
	/*each 1ms the interrupt will fired and enter the scheduler*/
	MSTK_u8SetCallBackFunc(OS_voidScheduler);
	MSTK_u8SetIntervalPeriodic(1000);
}

void OS_voidModifyPeriodictyTask(u8 Copy_u8ID, u16 Copy_u16MPeriodicity)
{
	Global_OSTasks[Copy_u8ID].u16_Periodicity=Copy_u16MPeriodicity;
}

void OS_voidScheduler(void)
{
	static volatile u16 Local_u16TickCounts = 0; // Tick counter

	// Increment tick count (every 1 ms interrupt)
	Local_u16TickCounts++;

	for (u8 i = 0; i < NUMBER_OF_TASKS; i++)
	{
		if (Global_OSTasks[i].u16_FirstDelay > 0)
		{
			Global_OSTasks[i].u16_FirstDelay--; // Decrement delay
		}
		else
		{
			// Execute task when its periodicity matches the tick count
			if ((Local_u16TickCounts % Global_OSTasks[i].u16_Periodicity) == 0)
			{
				if (Global_OSTasks[i].Funptr != NULL)
				{
					Global_OSTasks[i].Funptr(); // Execute task
				}
			}
		}
	}
}

