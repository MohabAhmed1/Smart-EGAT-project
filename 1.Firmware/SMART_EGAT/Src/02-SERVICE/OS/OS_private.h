/*
 * OS_private.h
 *
 *  Created on: Feb 1, 2023
 *      Author: speedTECH
 */

#ifndef OS_PRIVATE_H_
#define OS_PRIVATE_H_

typedef struct
{
	u16 u16_Periodicity;
	void (*Funptr) (void);
	u16 u16_FirstDelay;
	u8 u8_State;
}Task_t;




#endif /* OS_PRIVATE_H_ */
