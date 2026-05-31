/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
* File  : TaskUserInput.c
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
#include <conio.h>

extern DamInfo dam;

static char buffer[64] = {0};   // Input buffer
static char cmd[64] = {0};      // Parsed command (not used here)

/*
*********************************************************************************************************
* Function    : TaskUserInput
* Description : Handles user input from keyboard for manual control and settings
* Parameters  : pdata - unused
*********************************************************************************************************
*/
void TaskUserInput(void *pdata) {
    int pos = 0;

    while (1) {
        // Display current input buffer in command line UI
        SetCursorPosition(0, 15);
        printf("Command > %-60s", buffer);
        fflush(stdout);

        // Check for user input
        if (_kbhit()) {
            char ch = _getch();

            // If Enter key pressed
            if (ch == '\r') {
                buffer[pos] = '\0';

                if (strlen(buffer) > 0) {
                    float value = 0.0f;
                    INT8U err;

                    // Try to acquire semaphore for data access
                    OSSemPend(dam.sem_data_lock, 0, &err);
                    if (err == OS_NO_ERR) {
                        // Parse known commands and apply changes
                        if (sscanf(buffer, "set height %f", &value) == 1) {
                            dam.water.height = value;
                            AddLog("[USER] Set height");
                        } else if (sscanf(buffer, "set inflow_fixed %f", &value) == 1) {
                            dam.water.inflow_fixed = value;
                            AddLog("[USER] Set inflow_fixed");
                        } else if (sscanf(buffer, "set inflow_var %f", &value) == 1) {
                            dam.water.inflow_variable = value;
                            AddLog("[USER] Set inflow_var");
                        } else if (sscanf(buffer, "set gate %f", &value) == 1) {
                            if (value >= 0 && value <= 100) {
                                dam.user_ctrl.manual_override = 1;
                                dam.gate.open_percent = (int)value;
                                AddLog("[USER] Manual gate override");
                            } else {
                                AddLog("[ERROR] Gate percent must be 0-100");
                            }
                        } else if (strcmp(buffer, "manual off") == 0) {
                            dam.user_ctrl.manual_override = 0;
                            AddLog("[USER] Manual control disabled");
                        } else {
                            AddLog("[USER] Unknown command");
                        }

                        OSSemPost(dam.sem_data_lock);
                    } else {
                        AddLog("[ERROR] Semaphore lock failed");
                    }

                    PrintLogPanel();
                    SetCursorPosition(10, 15); // Reset cursor after entry
                }

                // Reset buffer
                pos = 0;
                memset(buffer, 0, sizeof(buffer));

            } else if (ch == '\b' && pos > 0) {
                // Handle backspace
                pos--;
                buffer[pos] = '\0';
            } else if (pos < sizeof(buffer) - 1) {
                // Append character to buffer
                buffer[pos++] = ch;
            }
        }

        // Update cursor position
        SetCursorPosition(10 + pos, 15);
        OSTimeDlyHMSM(0, 0, 0, 100); // Check for input every 100ms
    }
}