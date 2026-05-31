#include "INCLUDES.H"
#include <DAM_SIM.H>
#include <APP/task.h>
#include <windows.h>

#define TASK_STK_SIZE   512
#define TASK_NUM        7
#define Q_SIZE          11

OS_STK TaskStk[TASK_NUM][TASK_STK_SIZE];
void *alarm_msg_buf[Q_SIZE];

DamInfo dam;
TimeTicker timer;

void SystemInit();

int main(void)
{
    OSInit(); // Initialize OS

    SystemInit(); // Set up dam info and synchronization primitives
    ClearConsole(); // Clear console screen for clean UI

    // Create tasks with appropriate priorities
    OSTaskCreate(TaskReservoir,     (void *)0, &TaskStk[0][TASK_STACK_SIZE - 1], TASK_RESERVOIR_PRIO);
    OSTaskCreate(TaskWaterSensor,   (void *)0, &TaskStk[1][TASK_STACK_SIZE - 1], TASK_WATER_SENSOR_PRIO);
    OSTaskCreate(TaskGateControl,   (void *)0, &TaskStk[2][TASK_STACK_SIZE - 1], TASK_GATE_CONTROL_PRIO);
    OSTaskCreate(TaskAlarm,         (void *)0, &TaskStk[3][TASK_STACK_SIZE - 1], TASK_ALARM_PRIO);
    OSTaskCreate(TaskPrintStatus,   (void *)0, &TaskStk[4][TASK_STACK_SIZE - 1], TASK_PRINT_STATUS_PRIO);
    OSTaskCreate(TaskLog,           (void *)0, &TaskStk[5][TASK_STACK_SIZE - 1], TASK_LOG_PRIO);
    // OSTaskCreate(TaskUserInput,     (void *)0, &TaskStk[][TASK_STACK_SIZE - 1], TASK_USER_INPUT_PRIO);
    OSTaskCreate(TaskTimeTicker,    (void *)0, &TaskStk[6][TASK_STACK_SIZE - 1], TASK_TIME_TICKER_PRIO);

    OSStart(); // Start OS

    return 0;
}

// Initialize system data
void SystemInit(void) {
    INT8U err;
    DamInfoInit(&dam, "config.txt");
    dam.sem_data_lock = OSSemCreate(1);
    dam.msg_q_alarm = OSQCreate(&alarm_msg_buf[0], Q_SIZE);
}