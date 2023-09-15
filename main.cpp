/*!****************************************************************************
 * @file main.cpp
 * @brief Activate the alarm when gas or overTemperature is detected
 * This program was built and tested on the NUCLEO F429ZI ARMC6,
 * connected to a Dip Switch and it takes care of turning on and off
 * the LED1 based on the selected state of the dip switch. Additionally,
 * it prints in the terminal the states of the pins
 * The pins is set into a PullDown mode so the dip switch should be connected 
 * to 3.3V pin
 * There is an OFF button to set the alarm state to OFF and so its pin LED
 * @author Quattrone Martin
 * @author Vazquez Rodrigo
 *******************************************************************************/

#include "mbed.h"
#include "arm_book_lib.h"

int main()
{
    // DigitalIn gasDetector(D2);
    gpio_t gasDetector;
    gpio_init_in(&gasDetector, D2);

    // DigitalIn overTempDetector(D3);
    gpio_t overTempDetector;
    gpio_init_in(&overTempDetector, D3);

    // DigitalIn alarmOffButton(BUTTON1);
    gpio_t alarmOffButton;
    gpio_init_in(&alarmOffButton, BUTTON1);

    // DigitalOut alarmLed(LED1);
    gpio_t alarmLed;
    gpio_init_out(&alarmLed, LED1);

    // gasDetector.mode(PullDown);
    gpio_mode(&gasDetector, PullDown);

    // overTempDetector.mode(PullDown);
    gpio_mode(&overTempDetector, PullDown);

    // alarmLed = OFF;
    gpio_write(&alarmLed, OFF);

    bool alarmState = OFF;

    while (true) 
    {
        if ( gpio_read(&gasDetector) || gpio_read(&overTempDetector) ) 
        {
            printf("if ( gasDetector || overTempDetector ) \n");                    //!< The state of the pins are printed
            printf("gasDetector = %d\n", gpio_read(&gasDetector));
            printf("overTempDetector = %d\n", gpio_read(&overTempDetector));
            printf("alarmState = %d\n", alarmState);

            alarmState = ON;
        }

        // alarmLed = alarmState;
        gpio_write(&alarmLed, alarmState);

        // if ( alarmOffButton ) 
        if ( gpio_read(&alarmOffButton) ) 
        {
            printf("if ( alarmOffButton ) \n");                                     //!< The state of the pins are  printed
            printf("gasDetector = %d\n", gpio_read(&gasDetector));
            printf("overTempDetector = %d\n", gpio_read(&overTempDetector));
            printf("alarmState = %d\n", alarmState);

            alarmState = OFF;
        }
    }
}