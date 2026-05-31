/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
* File  : TaskReservoir.c
* By    : Minseok Choi
* Ver   : 1.0
* Date  : 2025-05-31
*********************************************************************************************************
*/

#include <DAM_SIM.H>
#include "task.h"
#include <stdlib.h>
#include <time.h>

extern DamInfo dam;

const char *CLIMATE_NAME[] = {"Clear", "Rain", "Storm"};

/*
*********************************************************************************************************
* Function    : TaskReservoir
* Description : Periodically updates water inflow and climate condition
* Parameters  : pdata - unused
*********************************************************************************************************
*/
void TaskReservoir(void *pdata) {
    INT8U err;
    int tick = 0;
    srand(time(NULL)); // Seed random number generator

    while (1) {
        // Lock shared data
        OSSemPend(dam.sem_data_lock, 0, &err);

        // Update water level based on inflow/outflow
        UpdateWaterInfo(&dam, 1);

        // Every 10 ticks, change the climate randomly
        if (tick % 10 == 0) {
            Climate prev = dam.climate_state;
            Climate next = rand() % 3;  // Random climate: 0 = Clear, 1 = Rain, 2 = Storm
            dam.climate_state = next;

            // Update variable inflow based on climate
            if (next == CLEAR) {
                dam.water.inflow_variable = 0;
            } else if (next == RAIN) {
                dam.water.inflow_variable = dam.climate_config.rain_min +
                    rand() % (dam.climate_config.rain_max - dam.climate_config.rain_min + 1);
            } else if (next == STORM) {
                dam.water.inflow_variable = dam.climate_config.storm_min +
                    rand() % (dam.climate_config.storm_max - dam.climate_config.storm_min + 1);
            }

            // Log climate change if changed
            if (prev != next) {
                char log_msg[64];
                snprintf(log_msg, sizeof(log_msg), "[CLIMATE] %s -> %s", CLIMATE_NAME[prev], CLIMATE_NAME[next]);
                AddLog(log_msg);
                PrintLogPanel();
            }
        }

        // Release lock on shared data
        OSSemPost(dam.sem_data_lock);

        tick++;

        // Delay 1 second
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}