/**********************************************************************************
 * [FILE NAME]:  application_functions.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: April 9, 2021
 *
 * [Description]: File to contain all functions of the application.
 ***********************************************************************************/

#include"application_functions.h"

/***************************************************************************************************
 * [Function Name]: open_motor_timer
 *
 * [Description]:  Function to hold the motor stopped for some time, indicate to the door
 *                 is open, after time has finished, it would call another function to force it
 *                 to move in opposite direction to indicate the door is closing
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void open_motor_timer(void)
{
	/*
	 * increment the value of the global variable
	 * every increase of it means that an interrupt of the occurs
	 * every increase of it mans 1 second has passed
	 */
	g_tickFlag++;

	/*
	 * As long as g_tickFlag smaller than the value of maximum seconds
	 * the MOTOR is remaining to be in stop case
	 */
	if( g_tickFlag < MAXIMUM_SECONDS_OPENING)
	{

		motor_on_90();
		/*
		 * Open the lightning system
		 */
		SET_BIT(LED_DATA_PORT,LED_PIN);

		/*
		 *   1-display a message for the user to "Your ID is 500"
		 *   2-force arrow of the LCD to go to the second line
		 *   3-display a message for the user "Door is Open now!"
		 */
		LCD_displayStringRowColumn(0,0,"Your ID is 500");
		LCD_goToRowColumn(1,0);
		LCD_displayStringRowColumn(1,0,"Door is Open now!");

	}/*End of if condition*/

	/*
	 * As long as g_tickFlag reaches the maximum value of seconds
	 * so the LCD will stop displaying the message
	 */
	else if(g_tickFlag == MAXIMUM_SECONDS_OPENING)
	{

		/*
		 * clear LCD screen after displaying the last message
		 */
		LCD_clearScreen();
		/*
		 *   1-display a message for the user to "Car passed"
		 *   2-force arrow of the LCD to go to the second line
		 *   3-display a message for the user "Door is closing now!"
		 */
		LCD_displayStringRowColumn(0,0,"Car passed");
		LCD_goToRowColumn(1,0);
		LCD_displayStringRowColumn(1,0,"Door is closing now!");
		_delay_ms(3000);


		/*
		 * call the function of motor_on_0
		 * to force the motor to return on its initial value
		 * in stopping state
		 */
		motor_on_0();

		/*
		 * Close the lightning system
		 */
		CLEAR_BIT(LED_DATA_PORT,LED_PIN);

		/*
		 *DE-initialization of all the register of the timer
		 *to be ready for another interrupts occur
		 */
		Timer_DeInit(Timer1);

		/*
		 * return the initial value of the global flag
		 * to be ready for another interrupt occur
		 */
		g_tickFlag= 0;
		/*
		 * change the value of g_holdSystem variable to
		 * log out from the polling on the time interrupt
		 * and return to the remain parts of the application
		 */
		g_holdSystem = RESUME_SYSTEM;

		/*
		 * clear LCD screen after displaying the last message
		 * "Door is closing now"
		 */
		LCD_clearScreen();

	}/*End of else if condition*/

}/*End of timerStopping function*/

/***************************************************************************************************
 * [Function Name]: displayID
 *
 * [Description]:  Function to give Car parking its ID
 *
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/

void displayID(void)
{

	/*
	 * clear LCD screen after displaying the last message
	 */
	LCD_clearScreen();
	/*
	 *   1-display a message for the user to "Your ID is 500"
	 *   2-force arrow of the LCD to go to the second line
	 *   3-display a message for the user "Door is Opening!"
	 */
	LCD_displayStringRowColumn(0,0,"Your ID is 500");
	LCD_goToRowColumn(1,0);
	LCD_displayStringRowColumn(1,0,"Door is Opening!");
	_delay_ms(2000);

	/*
	 * call the function of motor_on_CLOCKWISE to
	 * force the motor to move in clock wise direction
	 */
	motor_on_90();

	/*
	 * Open the lightning system
	 */
	SET_BIT(LED_DATA_PORT,LED_PIN);

	/*
	 * call the function Timer_setCallBack and give it
	 * the address of function timerMoving_Clockwise to force the timer ISR
	 * to call this function every interrupt occur, "every one second"
	 */
	Timer_setCallBack(open_motor_timer, Timer1);

	/*
	 * Start the timer to count
	 * give it the address of the declared structure
	 * to put its values in the initialization function
	 * in the entire registers of the timer
	 */
	Timer_init(&g_timer);

	/*
	 * clear LCD screen after displaying the last message
	 */
	LCD_clearScreen();

}/*end of the displayID function*/






