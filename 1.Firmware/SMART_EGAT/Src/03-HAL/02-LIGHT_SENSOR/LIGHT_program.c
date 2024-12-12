/*************************** Layer:HAL      ************************************/
/**************************  Driver:LIGHT   *************************************/
/*************************  Version: 1.0    ************************************/
/******************************************************************************/


#include "../../00-LIB/STD_TYPES.h"
#include "../../00-LIB/BIT_MATH.h"
#include "../../00-LIB/Software_Delay.h"
#include "../../01-MCAL/02-DIO/DIO_interface.h"
#include "../../01-MCAL/08-TIM/TIM_interface.h"
#include "../../01-MCAL/12-ADC/ADC_interface.h"

#include "LIGHT_interface.h"
#include "LIGHT_config.h"

f32 HLDR_f32GetReading(void)
{
	static u16 Local_u16ADCValue = 0; // Variable to store ADC value
	f32 Local_f32LightIntensity = 0.0; // Variable to store light intensity

	// Check if the sensor is enabled

		// Check if the ADC conversion is complete
		if (ADC1_u8SingleChannelCheck())  // Check End of Conversion (EOC) flag
		{
			ADC1_voidSingleChannelRX(&Local_u16ADCValue);  // Read ADC value

			// Convert ADC value to light intensity (for example, using the formula for LDR)
			// You may need to adjust this formula based on your circuit
			// For simplicity, assume the voltage across the LDR is linearly related to the light intensity
			Local_f32LightIntensity = (Local_u16ADCValue * 3.3f) / 4095.0f * 100.0f; // Example conversion

			// Return the calculated light intensity
			return Local_f32LightIntensity;
		}
		else
		{
			return -1;  // ADC data not ready
		}


}

