/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
*                                      Task Header Definitions
*
* File  : task.h
* By    : Minseok Choi
* Ver   : 1.0
* Date  : 2025-05-31
*********************************************************************************************************
*/

#ifndef __TASK_H__
#define __TASK_H__

#include <includes.h>
#include "DAM_SIM.H" 



/*
*********************************************************************************************************
*                                      TASK PRIORITIES
* Description : Defines unique priority levels for each task.
*               Lower value means higher priority in uC/OS-II.
*********************************************************************************************************
*/
#define TASK_RESERVOIR_PRIO      6   // Climate and inflow updater
#define TASK_WATER_SENSOR_PRIO   7   // Water level monitor and alarm trigger
#define TASK_GATE_CONTROL_PRIO   8   // Automatic gate control logic
#define TASK_ALARM_PRIO          9   // Alarm message handler
#define TASK_PRINT_STATUS_PRIO  10   // Console status output
#define TASK_LOG_PRIO           11   // Periodic logging to file
#define TASK_USER_INPUT_PRIO    12   // Manual input interface
#define TASK_TIME_TICKER_PRIO   13   // Time counter and display



/*
*********************************************************************************************************
*                                      TASK STACK SIZE
* Description : Common stack size for all tasks (in words).
*********************************************************************************************************
*/
#define TASK_STACK_SIZE  512



/*
*********************************************************************************************************
*                                      TASK FUNCTION PROTOTYPES
* Description : Declarations of task entry functions for OS scheduler.
*********************************************************************************************************
*/
void TaskReservoir(void *pdata);      // Controls climate simulation and inflow
void TaskWaterSensor(void *pdata);    // Monitors water level and posts alarms
void TaskGateControl(void *pdata);    // Manages gate control logic
void TaskAlarm(void *pdata);          // Receives and logs alarms
void TaskPrintStatus(void *pdata);    // Displays dam info and logs on console
void TaskLog(void *pdata);            // Saves dam state to log file
void TaskUserInput(void *pdata);      // Handles manual user commands (keyboard)
void TaskTimeTicker(void *pdata);     // Advances simulation time every 100ms

#endif  // __TASK_H__
