/*************************** Layer:HAL      ************************************/
/**************************  Driver:TEMP    ************************************/
/*************************  Version: 1.0    ************************************/
/******************************************************************************/


#include "../../00-LIB/STD_TYPES.h"
#include "../../00-LIB/BIT_MATH.h"
#include "../../00-LIB/Software_Delay.h"
#include "../../01-MCAL/02-DIO/DIO_interface.h"
#include "../../01-MCAL/08-TIM/TIM_interface.h"
#include "../../01-MCAL/12-ADC/ADC_interface.h"
#include "TEMP_interface.h"
#include "TEMP_config.h"
#include "TEMP_private.h"




f32 HTEMP_f32GetTemp(void)
{
	static u16 Local_u16ADCValue = 0;
	f32 Local_f32Temperature = 0.0;

	// Check if the sensor is enabled

		// Check if the ADC conversion is complete
		if (ADC1_u8SingleChannelCheck())  // Check EOC (End of Conversion) flag
		{
			ADC1_voidSingleChannelRX(&Local_u16ADCValue);  // Read ADC data

			// Convert ADC value to temperature in Celsius (LM35: 1 degree = 10mV)
			// Formula: Temperature = (ADC Value * 5.0V / 4095) / 0.01V
			Local_f32Temperature = (Local_u16ADCValue * 5.0f) / 4095.0f * 100.0f;

			// Return the temperature in C
			return Local_f32Temperature;
		}
		else
		{
			return -1;  // ADC data not ready
		}


}
