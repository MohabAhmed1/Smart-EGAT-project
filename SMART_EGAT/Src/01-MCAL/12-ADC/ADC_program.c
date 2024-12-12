

#include "../../00-LIB/STD_TYPES.h"
#include "../../00-LIB/BIT_MATH.h"

#include "../03-STK/STK_interface.h"
#include "../11-USART/USART_interface.h"
#include "../01-PORT/PORT_private.h"
#include "../00-RCC/RCC_interface.h"
#include "../00-RCC/RCC_private.h"
#include "../00-RCC/RCC_register.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"




void ADC1_voidSingleChannelInit(u8 Copy_u8Channel)
{

	// Step 1: Configure ADC clock
	RCC->CFGR |= (2 << 14);     // Set ADC prescaler to divide by 2 (4 MHz ADC clock)
	RCC->APB2ENR |= (1 << 9);   // Enable ADC1 clock

	// Step 2: Configure GPIO for ADC
	RCC->APB2ENR |= (1 << 2);   // Enable GPIOA clock
	GPIOA->CRL &= ~(0xF << (0 * 4)); // Configure PA0 as analog mode
	ADC1->CR2 = 0;               // Reset CR2
	ADC1->SQR3 = Copy_u8Channel; // Select channel

	ADC1->SMPR2 |= (7 << (Copy_u8Channel * 3)); // Set sampling time to 239.5 cycles

	ADC1->CR2 |= 1;              // Enable ADC
	MSTK_voidSetBusyWait(100);   // Wait for stabilization

	ADC1->CR2 |= (1 << 3);       // Start calibration
	while (ADC1->CR2 & (1 << 3)); // Wait for calibration

	ADC1->CR2 |= 1;              // Re-enable ADC
	// Choose one mode:
	// Manual trigger mode: Do not enable continuous mode
	// ADC1->CR2 |= 0;            // Ensure continuous mode is off
	// Continuous mode:
	ADC1->CR2 |= 2;              // Enable continuous conversion mode

}


u8 ADC1_u8SingleChannelCheck(void)
{
	u8 Local_u8Check = 0;


	/* Check Flag of EOC */
	if(ADC1->SR & 2)
	{
		Local_u8Check = 1;
	}
	return Local_u8Check;
}



void ADC1_voidSingleChannelRX(u16 * Copy_pu16Data)
{
	u16 Local_u16Data = 0;

	// Check if continuous mode is disabled
	if (ADC1->SR & (1 << 4)) // Check for Overrun (OVR)
	{
		volatile u16 dummy = ADC1->DR; // Read DR to clear OVR
		ADC1->SR &= ~(1 << 4); // Clear the OVR flag
	}


	// Wait for the End of Conversion (EOC) flag
	while (!(ADC1->SR & (1 << 1)));

	// Clear Overrun (OVR) flag if it is set
	if (ADC1->SR & (1 << 4))
	{
		ADC1->SR &= ~(1 << 4); // Clear the OVR flag
	}

	// Read ADC data from the DR register
	Local_u16Data = ADC1->DR;

	// Scale ADC result to millivolts
	*Copy_pu16Data = (Local_u16Data * 1000) / 0xFFF;

//	// Debug output for status and data
//	USART_voidTransmitByteSynch('S', USART1);
//	USART_voidSendNumber(ADC1->SR, USART1);  // Send status register
//	USART_voidTransmitByteSynch('\r', USART1);
//
//	USART_voidTransmitByteSynch('C', USART1);
//	USART_voidSendNumber(ADC1->CR2, USART1);
//	USART_voidTransmitByteSynch('\r', USART1);
//
//	USART_voidTransmitByteSynch('M', USART1);
//	USART_voidSendNumber(ADC1->SMPR2, USART1);
//	USART_voidTransmitByteSynch('\r', USART1);
//
//	USART_voidTransmitByteSynch('D', USART1);
//	USART_voidSendNumber(Local_u16Data, USART1); // Send raw ADC value
//	USART_voidTransmitByteSynch('\r', USART1);
}

void ADC1_voidMultiChannelInit(u8 Copy_u8FirstChannel)
{
	/* Clear All CR2 */
	ADC1->CR2  = 0;

	/* ADC ON */
	ADC1->CR2 |= 1;

	/* wait for stability */
	MSTK_voidSetBusyWait(100);

	/* Set Number of first Channel of ADC */
	ADC1->SQR3 = Copy_u8FirstChannel;

	/* Set Continuous conversion */
	ADC1->CR2 |= 2;

	/* ADC ON again */
	ADC1->CR2 |= 1;
}


void ADC1_voidSetNextChannel(u8 Copy_u8NextChannel)
{
	/* Set Number of Next Channel of ADC */
	ADC1->SQR3 = Copy_u8NextChannel;
}

void ADC1_voidMultiChannel_RX(u8 Copy_u8Channels , u8 * Copy_pu8AdcChannels , u16 * Copy_pu16AnalogRX)
{
	u16 Local_u16TempRX = 0;
	u8 Local_u8Counter  = 0;
	while (1)
	{
		/* Check Flag of EOC */
		if(ADC1_u8SingleChannelCheck())
		{
			/* Read Data of ADC from Dr Register */
			ADC1_voidSingleChannelRX(&Local_u16TempRX);

			/* Assign this data in array */
			Copy_pu16AnalogRX[Local_u8Counter] = Local_u16TempRX;
			Local_u8Counter++;

			/* Check if all channel has a value or not */
			if(Local_u8Counter == Copy_u8Channels)
			{
				Local_u8Counter = 0;
				ADC1_voidSetNextChannel(Copy_pu8AdcChannels[Local_u8Counter]);
				break;
			}
			else
			{
				ADC1_voidSetNextChannel(Copy_pu8AdcChannels[Local_u8Counter]);
			}
		}
	}
}
