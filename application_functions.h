/**********************************************************************************
 * [FILE NAME]: application_function.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: April 9, 2021
 *
 * [Description]: File of All types Declaration and Functions prototypes of application
 *                configuration.
 *
 ***********************************************************************************/
#ifndef APPLICATION_FUNCTIONS_H_
#define APPLICATION_FUNCTIONS_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#include"external_interrupts.h"
#include"timer.h"
#include"motor.h"
#include"lcd.h"
#include"i2c.h"

/**************************************************************************
 *                        Preprocessor Macros                             *
 * ************************************************************************/
/*for timer*/
#define START_VALUE             0
#define COMPARE_VALUE           1000

/*for system application*/
#define RESUME_SYSTEM                           0
#define HOLD_SYSTEM                             1

/*for timer and door*/

#define MAXIMUM_SECONDS_OPENING                 10

/*for IR sensor*/
#define IR_DIRECTION_PORT             DDRA
#define IR_OUTPUT_PIN                 PA0
#define IR_VCC_PIN
#define IR_DATA_PORT                  PORTA
#define IR_INPUT_PORT                  PINA


#define ID_SELECTION                 3
#define ID_SIZE                      3

#define LED_PIN                      PD6
#define LED_DATA_PORT                PORTD
#define LED_DIRECTION_PORT           DDRD
#define LED_INPUT_PORT               PIND
/*******************************************************************************
 *                        External variables                                   *
 *******************************************************************************/

/*
 * variable to use it in the functions call back in of the timer
 * use it as a counter for seconds
 */
extern uint8 g_tickFlag;

/*
 * variable to use it to hold the system with no work
 * while the door opening and closing
 */
extern uint8 g_holdSystem;


/*
 * variable to use to declare the structure of the timer
 */
extern Timer_ConfigType g_timer;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
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
void open_motor_timer(void);
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
void displayID(void);
/**************************************************************************************************/


#endif /* APPLICATION_FUNCTIONS_H_ */
