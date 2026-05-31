/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
* File  : TaskTimeTicker.c
* By    : Minseok Choi
* Ver   : 1.0
* Date  : 2025-05-31
*********************************************************************************************************
*/

#include <windows.h>
#include "DAM_SIM.H"

extern TimeTicker timer;



/*
*********************************************************************************************************
* Function    : TaskTimeTicker
* Description : Increments the simulation clock every 100ms and updates the display
* Parameters  : pdata - unused
*********************************************************************************************************
*/
void TaskTimeTicker(void *pdata) {
    while (1) {
        // Increase time by 100 milliseconds
        timer.millis += 100;

        // Carry over to seconds, minutes, hours as needed
        if (timer.millis >= 1000) {
            timer.millis = 0;
            timer.seconds++;
        }
        if (timer.seconds >= 60) {
            timer.seconds = 0;
            timer.minutes++;
        }
        if (timer.minutes >= 60) {
            timer.minutes = 0;
            timer.hours++;
        }

        // Print updated time to the console
        PrintTime();

        // Wait for 100 milliseconds
        Sleep(100);
    }
}