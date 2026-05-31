/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
*
*
* File  : TaskAlarm.c
* By    : Minseok Choi
* Ver   : 1.0
* Date  : 2025-05-31
*********************************************************************************************************
*/

#include "DAM_SIM.H"
#include "task.h"
#include <string.h>

#define MAX_ALARMS 5

extern DamInfo dam;

char alarm_log[MAX_ALARMS][64]; // Circular buffer for alarm messages
int alarm_idx = 0;              // Index for alarm log buffer



/*
*********************************************************************************************************
* Function    : AddAlarmLog
* Description : Stores alarm message in internal alarm log buffer
* Parameters  : msg - string message to store
*********************************************************************************************************
*/
void AddAlarmLog(const char *msg) {
    strncpy(alarm_log[alarm_idx], msg, 63);
    alarm_log[alarm_idx][63] = '\0';
    alarm_idx = (alarm_idx + 1) % MAX_ALARMS;
}

/*
*********************************************************************************************************
* Function    : TaskAlarm
* Description : Waits for alarm messages and logs them to display and buffer
* Parameters  : pdata - unused
*********************************************************************************************************
*/
void TaskAlarm(void *pdata) {
    INT8U err;
    void *msg;

    while (1) {
        // Wait for message from the alarm queue (blocking)
        msg = OSQPend(dam.msg_q_alarm, 0, &err);
        if (msg != NULL) {
            AddAlarmLog((char *)msg);   // Save in internal log
            AddLog((char *)msg);        // Display in log panel and write to file
            PrintLogPanel();            // Refresh log panel on UI
        }
    }
}