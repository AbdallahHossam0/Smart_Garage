/**********************************************************************************
 * [FILE NAME]:  enterance.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: April 9, 2021
 *
 * [Description]:
 ***********************************************************************************/

#include"application_functions.h"


	/*
	 * variable to use it in the functions call back in of the timer
	 * use it as a counter for seconds
	 */
	uint8 g_tickFlag=0;

	/*
	 * variable to use it to hold the system with no work
	 * while the door opening and closing
	 */
	uint8 g_holdSystem = HOLD_SYSTEM;

	/*
	 * initialize the configure structure of the timer
	 * choosing value in order to form the structure
	 */
	Timer_ConfigType g_timer={START_VALUE, COMPARE_VALUE, Timer1, F_CPU_1024, Compare};

int main(void)
{

	/******************************************************************************************
	 *                                      INITIALIZATION
	 *****************************************************************************************/
	/*
	 * initialize the configure structure of i2c
	 * choosing value in order to form the structure
	 */

	TWI_ConfigType init_i2c = {0X02, 0X01, TWPS_0};

	/*
	 * initialize the driver of LCD to begin
	 */
	LCD_init();

	/*
	 * enable the interrupt bit in the SREG register
	 * to be ready for any interrupt occur
	 */
	SREG |= (1<<7);

	/*
	 *configure Motor pin as output pin
	 */
	SET_BIT(MOTOR_DIRECTION_PORT, MOTOR_PIN);

	/*
	 * set motor in equilibrium state in the first
	 * of the program
	 */
	motor_on_0();

	/*
	 * Configure LED pin as output pin
	 */
	SET_BIT(LED_DIRECTION_PORT, LED_PIN);


	/*
	 * initialize the configure structure of external
	 * interrup0 choosing value in order to
	 * form the structure.
	 */
	External_Interrupt_ConfigType Get_ID = {INTERRUPT1, Falling};



	/*
	 * call the function Interrupt_setCallBack and give it
	 * the address of function Reset_stopWatch to force the Interrupt ISR
	 * to call this function every interrupt occur
	 */
	Interrupt_setCallBack(displayID, INTERRUPT1);


	/*
	 * configure IR_VCC pin as output pin in the MCU
	 */
	 //SET_BIT(IR_DIRECTION_PORT, IR_VCC_PIN );

	/*
	 * Configure IR Output as input pin in the MCU
	 */
	CLEAR_BIT(IR_DIRECTION_PORT , IR_OUTPUT_PIN );


	/******************************************************************************************
	 *                                      Application
	 *****************************************************************************************/
	while(1)
	{

		if( BIT_IS_SET(IR_INPUT_PORT, IR_OUTPUT_PIN ) )
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Car Found");
			LCD_goToRowColumn(1,0);
			LCD_displayStringRowColumn(1,0,"Welcome User!");
			_delay_ms(10000);
			LCD_clearScreen();

			LCD_displayStringRowColumn(0,0,"New Guest?! if,yes");
			LCD_goToRowColumn(1,0);
			LCD_displayStringRowColumn(1,0,"Use button to get ID");

			/*
			 * Start the interrupt to detect edges
			 * give it the address of the declared structure
			 * to put its values in the initialization function
			 * in the entire registers of interrupt1
			 */
			External_Interrupt_init(&Get_ID);

			/*
			 *pooling to hold the whole program until the door opening
			 * to make all peripherals are pooled with no work
			 */

			while( (g_holdSystem != RESUME_SYSTEM) || (BIT_IS_SET(IR_INPUT_PORT, IR_OUTPUT_PIN)) ){}

			/*
			 * return the state of the g_holdSystem to be hold again
			 * after being RESUME to be ready for any required
			 * action to hold the system again
			 */
			g_holdSystem = HOLD_SYSTEM;

			/*
			 * clear LCD screen after displaying the last message
			 */
			LCD_clearScreen();

		}


		while ( BIT_IS_CLEAR(IR_INPUT_PORT , IR_OUTPUT_PIN) )
		{
			External_Interrupt_Deinit(INTERRUPT1);
			LCD_displayStringRowColumn(0,0,"   SMART PARKING");
		}



	}/*End of Super loop*/


}/*End of main function*/
