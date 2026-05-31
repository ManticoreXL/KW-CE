/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
* File  : TaskWaterSensor.c
* By    : Minseok Choi
* Ver   : 1.0
* Date  : 2025-05-31
*********************************************************************************************************
*/

#include <DAM_SIM.H>
#include "task.h"

extern DamInfo dam;



/*
*********************************************************************************************************
* Function    : TaskWaterSensor
* Description : Monitors water level and posts an alarm if it exceeds the threshold
* Parameters  : pdata - unused
*********************************************************************************************************
*/
void TaskWaterSensor(void *pdata) {
    INT8U err;

    while (1) {
        // Lock access to dam data
        OSSemPend(dam.sem_data_lock, 0, &err);

        // Check if water level exceeds alarm threshold
        if(CheckWaterLevel(&dam, dam.config.alarm_threshold)) {
            dam.stats.alarm_count++; // Increment alarm counter
            OSQPost(dam.msg_q_alarm, (void *)"Water Level Exceeded!"); // Post message to alarm queue
        }

        // Release semaphore
        OSSemPost(dam.sem_data_lock);

        // Delay 1 second before next check
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}