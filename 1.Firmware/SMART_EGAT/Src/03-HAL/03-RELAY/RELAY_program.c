#include "../../00-LIB/STD_TYPES.h"
#include "../../00-LIB/BIT_MATH.h"
#include "../../00-LIB/Software_Delay.h"
#include "../../01-MCAL/02-DIO/DIO_interface.h"
#include "../../01-MCAL/08-TIM/TIM_interface.h"
#include "../../01-MCAL/12-ADC/ADC_interface.h"

#include "RELAY_interface.h"
#include "RELAY_config.h"



void HRELAY_voidON(void)
{
	MDIO_u8WriteChannel(RELAY_PORT,RELAY_PIN, MDIO_PIN_HIGH);
}
void HRELAY_voidOFF(void)
{
	MDIO_u8WriteChannel(RELAY_PORT,RELAY_PIN, MDIO_PIN_LOW);
}
u8 HRELAY_u8LastStatus(void)
{
	u8 Local_u8lastStatus = 0;
	MDIO_u8ReadChannel(RELAY_PORT, RELAY_PIN, &Local_u8lastStatus);

    return (Local_u8lastStatus > 1) ? 0 : Local_u8lastStatus;
}
