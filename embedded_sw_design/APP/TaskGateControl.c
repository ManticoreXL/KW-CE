/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
*
*
* File  : TaskGateControl.c
* By    : Minseok Choi
* Ver   : 1.0
* Date  : 2025-05-31
*********************************************************************************************************
*/

#include "DAM_SIM.H"
#include "task.h"

extern DamInfo dam;

// Gate open percentage values for various water levels
#define GATE_OPEN_LOW   10
#define GATE_OPEN_MID   30
#define GATE_OPEN_HIGH  60
#define GATE_OPEN_MAX   90



/*
*********************************************************************************************************
* Function    : TaskGateControl
* Description : Controls gate opening based on water level or manual override
* Parameters  : pdata - unused
*********************************************************************************************************
*/
void TaskGateControl(void *pdata) {
    INT8U err;

    while (1) {
        // Lock shared dam data
        OSSemPend(dam.sem_data_lock, 0, &err);
        

        int prev_gate = dam.gate.open_percent;

        if (dam.user_ctrl.manual_override) {
            // todo: Manual control is enabled, gate setting remains as set by user
        } else {
            // Automatic gate control logic based on current water height
            int h = dam.water.height;

            if (h < dam.config.level_low)
                dam.gate.open_percent = GATE_OPEN_LOW;
            else if (h < dam.config.level_mid)
                dam.gate.open_percent = GATE_OPEN_MID;
            else if (h < dam.config.level_high)
                dam.gate.open_percent = GATE_OPEN_HIGH;
            else
                dam.gate.open_percent = GATE_OPEN_MAX;
        }

        // Log gate state change if modified
        if (dam.gate.open_percent != prev_gate) {
            char log_msg[64];
            snprintf(log_msg, sizeof(log_msg), "[GATE] %d%% -> %d%%", prev_gate, dam.gate.open_percent);
            AddLog(log_msg);
            PrintLogPanel();
        }

        // Update gate outflow and power output based on current setting
        UpdateGateInfo(&dam);

        // Unlock shared dam data
        OSSemPost(dam.sem_data_lock);

        // Delay 1 second
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}
