/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
* File  : TaskPrintStatus.c
* By    : Minseok Choi
* Ver   : 1.0
* Date  : 2025-05-31
*********************************************************************************************************
*/

#include "DAM_SIM.H"
#include "task.h"

extern DamInfo dam;



/*
*********************************************************************************************************
* Function    : TaskPrintStatus
* Description : Prints the current dam status and log messages to the console periodically
* Parameters  : pdata - unused
*********************************************************************************************************
*/
void TaskPrintStatus(void *pdata) {
    INT8U err;

    while (1) {
        // Lock shared dam data for safe reading
        OSSemPend(dam.sem_data_lock, 0, &err);

        // Print current dam status to the screen
        PrintDamInfo(&dam, 1);

        // Display the most recent log messages
        PrintLogPanel();

        // Release shared data semaphore
        OSSemPost(dam.sem_data_lock);

        // Delay 1 second
        OSTimeDlyHMSM(0, 0, 1, 0); 
    }
}