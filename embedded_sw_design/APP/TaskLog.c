/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
*
*
* File  : TaskLog.c
* By    : Minseok Choi
* Ver   : 1.0
* Date  : 2025-05-31
*********************************************************************************************************
*/

#include "DAM_SIM.H"
#include "task.h"
#include <direct.h>
#include <io.h>
#include <string.h>

extern DamInfo dam;
extern OS_EVENT *sem_log_file;



/*
*********************************************************************************************************
* Function    : TaskLog
* Description : Periodically logs the current dam status to a file
* Parameters  : pdata - unused
*********************************************************************************************************
*/
void TaskLog(void *pdata) {
    INT8U err;

    // Open status log file in append mode
    FILE *fp = fopen("log/status.txt", "a");
    if (!fp) {
        printf("[ERROR] Failed to open log file.\n");
        return;
    }

    while (1) {
        // Acquire both semaphores to safely access dam data and log file
        OSSemPend(dam.sem_data_lock, 0, &err);
        OSSemPend(sem_log_file, 0, &err);

        // Write the dam's current status to log file
        LogDamInfo(&dam, fp);

        // Release semaphores after logging
        OSSemPost(sem_log_file);
        OSSemPost(dam.sem_data_lock);

        // Delay 10 seconds before next log
        OSTimeDlyHMSM(0, 0, 10, 0); 
    }

    fclose(fp); // This will never be reached due to infinite loop
}