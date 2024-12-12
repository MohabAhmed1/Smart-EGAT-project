

#ifndef OS_INTERFACE_H_
#define OS_INTERFACE_H_


void OS_CreateTask(u8 Copy_u8ID, u16 Copy_u16Periodicity, void (*ptr)(void),u16 Copy_u16FirstDelay);
void OS_voidStart(void);
void OS_voidModifyPeriodictyTask(u8 Copy_u8ID, u16 Copy_u16MPeriodicity);
void OS_voidScheduler(void);


#endif /* OS_INTERFACE_H_ */
