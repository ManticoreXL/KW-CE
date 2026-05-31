/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
*
* 
* File  : DAM_SIM.H
* By    : Minseok Choi
* Ver   : 1.0
* Date  : 2025-05-31
*********************************************************************************************************
*/

#ifndef __DAM_SIM_H__
#define __DAM_SIM_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <INCLUDES.H>
#include <windows.h>
#include <direct.h>     // _mkdir
#include <io.h>         // _access

#define MAX_LOG_LINES 10
extern char log_buffer[MAX_LOG_LINES][64];
extern int log_line_index;

/*
*********************************************************************************************************
* Enum        : Climate
* Description : Represents possible climate conditions
*********************************************************************************************************
*/
typedef enum {
    CLEAR = 0,
    RAIN,
    STORM
} Climate;



/*
*********************************************************************************************************
* Structure   : WaterInfo
* Description : Holds information about water level and inflow
* Members     : height - current water height in reservoir (m)
*               inflow_fixed - fixed inflow rate (m^3/s)
*               inflow_variable - inflow rate due to climate effects (m^3/s)
*********************************************************************************************************
*/
typedef struct {
    float height;
    float inflow_fixed;
    float inflow_variable;
} WaterInfo;



/*
*********************************************************************************************************
* Structure   : GateInfo
* Description : Describes gate operation and power generation
* Members     : open_percent - gate opening percentage (0~100%)
*               outflow - outflow rate through the gate (m^3/s)
*               power_output - power output generated (kWh)
*********************************************************************************************************
*/
typedef struct {
    int     open_percent;
    float   outflow;
    float   power_output;
} GateInfo;



/*
*********************************************************************************************************
* Structure   : StatInfo
* Description : Tracks cumulative statistics of dam operation
* Members     : total_power - total power generated (kWh)
*               total_outflow - total released water volume (m^3)
*               alarm_count - number of alarms triggered
*********************************************************************************************************
*/
typedef struct {
    float   total_power;
    float   total_outflow;
    int     alarm_count;
} StatInfo;



/*
*********************************************************************************************************
* Structure   : UserCtrlInfo
* Description : Stores user override state and gate setting
* Members     : manual_override - flag to enable manual control
*               manual_gate_percent - user-set gate opening percent
*********************************************************************************************************
*/
typedef struct {
    int manual_override;     
    int manual_gate_percent; 
} UserCtrlInfo;



/*
*********************************************************************************************************
* Structure   : ControlConfig
* Description : Holds water level thresholds for gate control logic
* Members     : level_low - low water threshold
*               level_mid - mid water threshold
*               level_high - high water threshold
*               alarm_threshold - level triggering alarm
*********************************************************************************************************
*/
typedef struct {
    int level_low;
    int level_mid;
    int level_high;
    int alarm_threshold;
} ControlConfig;



/*
*********************************************************************************************************
* Structure   : ClimateConfig
* Description : Configuration for inflow rates based on climate
* Members     : rain_min - minimum rain inflow
*               rain_max - maximum rain inflow
*               storm_min - minimum storm inflow
*               storm_max - maximum storm inflow
*********************************************************************************************************
*/
typedef struct {
    int rain_min;
    int rain_max;
    int storm_min;
    int storm_max;
} ClimateConfig;



/*
*********************************************************************************************************
* Structure   : DamInfo
* Description : Central structure holding all dam state and configuration
* Members     : reservoir_area - surface area of reservoir
*               water - water-related info
*               gate - gate and power output info
*               stats - statistical data
*               user_ctrl - user override state
*               config - control thresholds
*               climate_config - climate-based inflow settings
*               climate_state - current climate condition
*               sem_data_lock - semaphore for data access
*               msg_q_alarm - message queue for alarms
*********************************************************************************************************
*/
typedef struct {
    int             reservoir_area; 

    WaterInfo       water; 
    GateInfo        gate;
    StatInfo        stats;
    UserCtrlInfo    user_ctrl;
    ControlConfig   config;
    ClimateConfig   climate_config;
    Climate         climate_state;

    OS_EVENT        *sem_data_lock;
    OS_EVENT        *msg_q_alarm;
} DamInfo;



/*
*********************************************************************************************************
* Structure   : TimeTicker
* Description : Timekeeping structure for the simulator
* Members     : hours, minutes, seconds, millis - current time snapshot
*********************************************************************************************************
*/
typedef struct {
    int         hours;
    int         minutes;
    int         seconds;
    int         millis;
} TimeTicker;

/*
*********************************************************************************************************
*                                   FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void UpdateWaterInfo(DamInfo *dam, int dt_sec);
void UpdateGateInfo(DamInfo *dam);
int  CheckWaterLevel(DamInfo *dam, int threshold);
void PrintDamInfo(DamInfo *dam, int dt_sec);
void LogDamInfo(DamInfo *dam, FILE *fp);
void ApplyManualControl(DamInfo *dam, char *user_input);

void DamInfoInit(DamInfo *dam, const char *config_path);

void SetCursorPosition(int x, int y);
void PrintTime();
void ClearConsole();

void AddLog(const char *msg);
void PrintLogPanel();

#endif  // __DAM_SIM_H__