#include "00-LIB/STD_TYPES.h"
#include "00-LIB/BIT_MATH.h"

#include "01-MCAL/00-RCC/RCC_interface.h"
#include "01-MCAL/01-PORT/PORT_interface.h"
#include "01-MCAL/02-DIO/DIO_interface.h"
#include "01-MCAL/03-STK/STK_interface.h"
#include "01-MCAL/05-EXTI/EXTI_interface.h"
#include "01-MCAL/06-AFIO/AFIO_interface.h"
#include "01-MCAL/08-TIM/TIM_interface.h"
#include "01-MCAL/10-PWM/PWM_interface.h"
#include "01-MCAL/04-NVIC/NVIC_interface.h"
#include "01-MCAL/11-USART/USART_interface.h"
#include "01-MCAL/12-ADC/ADC_interface.h"
#include "01-MCAL/01-PORT/PORT_private.h"
#include "02-SERVICE/OS/OS_interface.h"

#include "03-HAL/01-TEMP_SENSOR/TEMP_interface.h"
#include "03-HAL/02-LIGHT_SENSOR/LIGHT_interface.h"
#include "03-HAL/03-RELAY/RELAY_interface.h"

#include "CJSON/cJSON.h"
#include "string.h"

char *node_Type[]={"NS","NA"};
char *node_ID[]={"0x80","0x81","0x50"};

#define NS 		node_Type[0]
#define NA 		node_Type[1]
#define TEMP 	node_ID[0]
#define LIGHT 	node_ID[1]
#define RELAY 	node_ID[2]
u8 TEMP_ENA	= 0;
u8 LIGHT_ENA= 0;
#define TEMP_ID		1
#define LIGHT_ID	2


void ReadTemp(void);
void ReadLight(void);

void reply_json_data(char *copy_nodeType,char *copy_nodeID, char *copy_data);
void send_and_parse_json();
void process_json(char *json_string);
char* IntToStr(u8 data) ;
unsigned int string_to_unsigned_int(char *str) ;


int main(void)
{
	RCC_voidInitSysClock();
	MSTK_voidClkSrcInit();
	RCC_voidEnableClock(RCC_GPIOA,RCC_APB2);
	RCC_voidEnableClock(RCC_GPIOB,RCC_APB2);
	RCC_voidEnableClock(RCC_GPIOC,RCC_APB2);
	RCC_voidEnableClock(RCC_ADC1, RCC_APB2);
	RCC_voidEnableClock(RCC_TIM2, RCC_APB1);
	RCC_voidEnableClock(RCC_TIM3, RCC_APB1);
	RCC_voidEnableClock(RCC_AFIO, RCC_APB2);
	RCC_voidEnableClock(RCC_USART1, RCC_APB2);

	PORT_voidInit();
	MTIM2_voidInit();
	MTIM3_voidInit();


	USART_config_t usart={
			.USART_Number= USART1,
			.USART_BaudRate = USART_BaudRate_9600 ,
			.USART_DataLength=USART_Data8Bits,
			.USART_StopBits= USART_1StopBits,
			.USART_Parity=USART_EvenParity,
			.USART_ParityCheck = USART_ParityCheckDisabled};

	USART_voidInit(&usart);

	ADC1_voidSingleChannelInit(0);

	OS_CreateTask(0, 500, send_and_parse_json, 0);
	OS_CreateTask(1,5000,ReadTemp,500);
	OS_CreateTask(2,2000,ReadLight,1000);
	OS_voidStart();
	while(1)
	{

	}
}



void ReadTemp(void)
{
	if(TEMP_ENA)
		reply_json_data(NS, TEMP, IntToStr(HTEMP_f32GetTemp()));
}
void ReadLight(void)
{
	if(LIGHT_ENA)
		reply_json_data(NS, LIGHT, IntToStr(HLDR_f32GetReading()));
}
void reply_json_data(char *copy_nodeType,char *copy_nodeID, char *copy_data)
{
	cJSON *json = cJSON_CreateObject();
	if (!json) {
		USART_voidSendString("Error: Failed to create JSON object!\n", USART1);
		return;
	}


	cJSON_AddStringToObject(json, "nodeType", copy_nodeType);
	cJSON_AddStringToObject(json, "nodeID", copy_nodeID);
	cJSON_AddStringToObject(json, "data", copy_data);

	char *json_string = cJSON_PrintUnformatted(json); // Smaller JSON string
	if (json_string) {
		USART_voidSendString(json_string, USART1);
		USART_voidTransmitByteSynch('\r', USART1);
		USART_voidTransmitByteSynch('\n', USART1);
	} else {
		USART_voidSendString("Error: Failed to create JSON string!\n", USART1);
	}

	cJSON_Delete(json);
}

void send_and_parse_json() {
	char received_json[100];  // Buffer to hold received JSON string
	char ch;
	int i = 0;

	// Receive JSON string
	while (1) {
		ch = USART_voidReceiveByteSynch(USART1);
		USART_voidTransmitByteSynch(ch, USART1);  // display
		if (ch == '\n' || ch == '\r') {          // Stop at newline or carriage return
			received_json[i] = '\0';             // Null-terminate
			break;
		}
		received_json[i++] = ch;
		if (i >= sizeof(received_json) - 1) {    // Prevent buffer overflow
			USART_voidSendString("Error: JSON too long!\n", USART1);
			return;
		}
	}


	// Parse JSON
	cJSON *json = cJSON_Parse(received_json);
	if (json == NULL) {
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL) {
			USART_voidSendString("Parse error before: ", USART1);
			USART_voidSendString(error_ptr, USART1);
			USART_voidTransmitByteSynch('\r', USART1);
		} else {
			USART_voidSendString("JSON Parse failed!\n", USART1);
		}
		return;
	}

	// Extract and print JSON values
	cJSON *command = cJSON_GetObjectItem(json, "command");
	cJSON *nodeID = cJSON_GetObjectItem(json, "nodeID");
	cJSON *data = cJSON_GetObjectItem(json, "data");

	/*RELAY*/
	if((strcmp(command->valuestring ,"ENA")==0)&&(strcmp(nodeID->valuestring ,RELAY)==0)&&(strcmp(data->valuestring ,"NULL")==0))
	{
		reply_json_data(NS, RELAY, "DONE");
	}
	if((strcmp(command->valuestring ,"ACT")==0)&&(strcmp(nodeID->valuestring ,RELAY)==0)&&(strcmp(data->valuestring ,"1")==0))
	{
		HRELAY_voidON();
	}
	if((strcmp(command->valuestring ,"ACT")==0)&&(strcmp(nodeID->valuestring ,RELAY)==0)&&(strcmp(data->valuestring ,"0")==0))
	{
		HRELAY_voidOFF();
	}
	if((strcmp(command->valuestring ,"STA")==0)&&(strcmp(nodeID->valuestring ,RELAY)==0)&&(strcmp(data->valuestring ,"NULL")==0))
	{
		reply_json_data(NA, RELAY, IntToStr(HRELAY_u8LastStatus()));
	}

	/*Temp*/
	if((strcmp(command->valuestring ,"ENA")==0)&&(strcmp(nodeID->valuestring ,TEMP)==0)&&(strcmp(data->valuestring ,"NULL")==0))
	{
		TEMP_ENA = 1 ;
		reply_json_data(NS, TEMP, "DONE");
	}
	if((strcmp(command->valuestring ,"DUR")==0)&&(strcmp(nodeID->valuestring ,TEMP)==0))
	{
		OS_voidModifyPeriodictyTask(TEMP_ID, string_to_unsigned_int(data->valuestring)*1000);
	}


	/*Light*/
	if((strcmp(command->valuestring ,"ENA")==0)&&(strcmp(nodeID->valuestring ,LIGHT)==0)&&(strcmp(data->valuestring ,"NULL")==0))
	{
		LIGHT_ENA = 1 ;
		reply_json_data(NS, LIGHT, "DONE");
	}
	if((strcmp(command->valuestring ,"DUR")==0)&&(strcmp(nodeID->valuestring ,LIGHT)==0))
	{
		OS_voidModifyPeriodictyTask(LIGHT_ID, string_to_unsigned_int(data->valuestring)*1000);
	}


	cJSON_Delete(json);
}




char* IntToStr(u8 data)
{
	static char intString[12]; // Static buffer for the string
	sprintf(intString, "%u", data);
	return intString;
}


unsigned int string_to_unsigned_int(char *str) {
	unsigned int result = 0;
	int i = 0;

	// Loop through each character of the string
	for (; str[i] != '\0'; i++) {
		if (str[i] < '0' || str[i] > '9') {
			// Handle invalid characters (you could return an error or handle differently)
			return 0;
		}
		result = result * 10 + (str[i] - '0');  // Convert character to integer and add to result
	}

	return result;
}
