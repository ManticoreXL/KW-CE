/*
*********************************************************************************************************
*                                         DAM SIMULATOR
*
*
* 
* File  : DAM_SIM.C
* By    : Minseok Choi
* Ver   : 1.0
* Date  : 2025-05-31
*********************************************************************************************************
*/

#include <DAM_SIM.H>

// Constants for linear model (outflow and power output)
#define MIN_OUTFLOW         0      // m^3/s
#define MAX_OUTFLOW         11000   // m^3/s
#define MIN_POWER_OUTPUT    0       // kWh
#define MAX_POWER_OUTPUT    500     // kWh

extern TimeTicker timer;

OS_EVENT *sem_log_file; // Semaphore for logging file access

char log_buffer[MAX_LOG_LINES][64];
int log_line_index = 0;



/*
*********************************************************************************************************
* Function    : UpdateWaterInfo
* Description : Updates the water level in the reservoir based on inflow and outflow
* Parameters  : dam - pointer to dam structure
*               dt_sec - time step in seconds
*********************************************************************************************************
*/
void UpdateWaterInfo(DamInfo *dam, int dt_sec) {
    float inflow = dam->water.inflow_fixed + dam->water.inflow_variable;  // total inflow rate
    float outflow = dam->gate.outflow;                                    // outflow rate
    float net_flow_volume = (inflow - outflow) * dt_sec;                  // net water volume change

    float delta_height = net_flow_volume / dam->reservoir_area;           // height change
    dam->water.height += delta_height;

    if (dam->water.height < 0)
        dam->water.height = 0; // prevent negative water height
}



/*
*********************************************************************************************************
* Function    : UpdateGateInfo
* Description : Calculates gate outflow and power output based on gate opening
* Parameters  : dam - pointer to dam structure
*********************************************************************************************************
*/
void UpdateGateInfo(DamInfo *dam) {
    int percent = dam->gate.open_percent;

    // Calculate outflow (linear interpolation)
    dam->gate.outflow = MIN_OUTFLOW + (MAX_OUTFLOW - MIN_OUTFLOW) * percent / 100;

    // Calculate power output per second (convert from kWh per hour to kWh per second)
    float hourly_power = MIN_POWER_OUTPUT + (MAX_POWER_OUTPUT - MIN_POWER_OUTPUT) * percent / 100.0f;
    dam->gate.power_output = hourly_power / 3600.0f;  // kWh per second

    // Update cumulative status
    dam->stats.total_outflow += dam->gate.outflow;
    dam->stats.total_power += dam->gate.power_output;
}



/*
*********************************************************************************************************
* Function    : CheckWaterLevel
* Description : Checks if current water level exceeds a threshold
* Parameters  : dam - pointer to dam structure
*               threshold - threshold level to check
*********************************************************************************************************
*/
int CheckWaterLevel(DamInfo *dam, int threshold) {
    return (dam->water.height > threshold);
}



/*
*********************************************************************************************************
* Function    : PrintDamInfo
* Description : Prints current dam status to the console
* Parameters  : dam - pointer to dam structure
*               dt_sec - time step in seconds
*********************************************************************************************************
*/
void PrintDamInfo(DamInfo *dam, int dt_sec) {
    static int seconds = 0;
    seconds += dt_sec; 

    SetCursorPosition(0, 2);

    printf("======== DAM STATUS MONITOR ========\n");
    printf("Elapsed Time       : %d sec\n", seconds);
    printf("Water Height       : %.2f m\n", dam->water.height);
    printf("Fixed Inflow       : %.2f m^3/s\n", dam->water.inflow_fixed);
    printf("Variable Inflow    : %.2f m^3/s\n", dam->water.inflow_variable);
    printf("Gate Open Rate     : %d %%\n", dam->gate.open_percent);
    printf("Outflow Rate       : %.2f m^3/s\n", dam->gate.outflow);
    printf("Power Output       : %.2f kWh\n", dam->gate.power_output);
    printf("Total Power        : %.2f kWh\n", dam->stats.total_power);
    printf("Total Outflow      : %.2f m^3\n", dam->stats.total_outflow);
    printf("Alarm Count        : %d\n", dam->stats.alarm_count);
    printf("Manual Override    : %s\n", dam->user_ctrl.manual_override ? "YES" : "NO");
    printf("====================================\n");
}



/*
*********************************************************************************************************
* Function    : LogDamInfo
* Description : Logs current dam status to a file
* Parameters  : dam - pointer to dam structure
*               fp - file pointer to the log file
*********************************************************************************************************
*/
void LogDamInfo(DamInfo *dam, FILE *fp) {
    fprintf(fp, "[DAM STATUS]\n");
    fprintf(fp, "Time: %02d:%02d:%02d\n", timer.hours, timer.minutes, timer.seconds);
    fprintf(fp, "WaterHeight: %.2f m\n", dam->water.height);
    fprintf(fp, "InflowFixed: %.2f m^3/s\n", dam->water.inflow_fixed);
    fprintf(fp, "InflowVariable: %.2f m^3/s\n", dam->water.inflow_variable);
    fprintf(fp, "GateOpenRate: %d %%\n", dam->gate.open_percent);
    fprintf(fp, "OutflowRate: %.2f m^3/s\n", dam->gate.outflow);
    fprintf(fp, "PowerOutput: %.2f kWh/s\n", dam->gate.power_output);
    fprintf(fp, "TotalPower: %.2f kWh\n", dam->stats.total_power);
    fprintf(fp, "TotalOutflow: %.2f m^3\n", dam->stats.total_outflow);
    fprintf(fp, "AlarmCount: %d\n", dam->stats.alarm_count);
    fprintf(fp, "ManualOverride: %s\n", dam->user_ctrl.manual_override ? "YES" : "NO");
    fprintf(fp, "------------------------------\n");
    fflush(fp);
}



/*
*********************************************************************************************************
* Function    : LogMessageToFile
* Description : Appends a log message to the message log file with timestamp
* Parameters  : msg - log message string
*********************************************************************************************************
*/
void LogMessageToFile(const char *msg) {
    INT8U err;
    OSSemPend(sem_log_file, 0, &err);

    FILE *fp = fopen("log/messages.txt", "a");
    if (fp) {
        fprintf(fp, "[%02d:%02d:%02d] %s\n", timer.hours, timer.minutes, timer.seconds, msg);
        fflush(fp);
        fclose(fp);
    }

    OSSemPost(sem_log_file);
}



/*
*********************************************************************************************************
* Function    : ApplyManualControl
* Description : Placeholder for processing manual control commands
* Parameters  : dam - pointer to dam structure
*               user_input - string input from user
*********************************************************************************************************
*/
void ApplyManualControl(DamInfo *dam, char *user_input) {
    // todo
}




/*
*********************************************************************************************************
* Function    : DamInfoInit
* Description : Initializes the dam structure from config file and sets default states
* Parameters  : dam - pointer to dam structure
*               config_path - path to the configuration file
*********************************************************************************************************
*/
void DamInfoInit(DamInfo *dam, const char *config_path) {
    FILE *fp = fopen(config_path, "r");
    if (!fp) {
        printf("[ERROR] Could not open config file: %s\n", config_path);
        exit(1);
    }

    char line[128];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "RESERVOIR_AREA=", 15) == 0) {
            dam->reservoir_area = atoi(&line[15]);
        } else if (strncmp(line, "WATER_HEIGHT=", 13) == 0) {
            dam->water.height = atoi(&line[13]);
        } else if (strncmp(line, "INFLOW_FIXED=", 13) == 0) {
            dam->water.inflow_fixed = atoi(&line[13]);
        } else if (strncmp(line, "INFLOW_VARIABLE=", 16) == 0) {
            dam->water.inflow_variable = atoi(&line[16]);
        } else if (strncmp(line, "GATE_OPEN_PERCENT=", 18) == 0) {
            dam->gate.open_percent = atoi(&line[18]);
        } else if (strncmp(line, "LEVEL_LOW=", 10) == 0) {
            dam->config.level_low = atoi(&line[10]);
        } else if (strncmp(line, "LEVEL_MID=", 10) == 0) {
            dam->config.level_mid = atoi(&line[10]);
        } else if (strncmp(line, "LEVEL_HIGH=", 11) == 0) {
            dam->config.level_high = atoi(&line[11]);
        } else if (strncmp(line, "THRESHOLD_HEIGHT=", 17) == 0) {
            dam->config.alarm_threshold = atoi(&line[17]);
        } else if (strncmp(line, "RAIN_MIN=", 9) == 0) {
            dam->climate_config.rain_min = atoi(&line[9]);
        } else if (strncmp(line, "RAIN_MAX=", 9) == 0) {
            dam->climate_config.rain_max = atoi(&line[9]);
        } else if (strncmp(line, "STORM_MIN=", 10) == 0) {
            dam->climate_config.storm_min = atoi(&line[10]);
        } else if (strncmp(line, "STORM_MAX=", 10) == 0) {
            dam->climate_config.storm_max = atoi(&line[10]);
        }
    }

    fclose(fp);

    // initialize
    dam->gate.outflow = 0;
    dam->gate.power_output = 0;
    dam->stats.total_outflow = 0;
    dam->stats.total_power = 0;
    dam->stats.alarm_count = 0;
    dam->user_ctrl.manual_override = false;
    dam->climate_state = CLEAR;

    if (_access("log", 0) == -1) {
        _mkdir("log");
    }

    sem_log_file = OSSemCreate(1);
}



/*
*********************************************************************************************************
* Function    : SetCursorPosition
* Description : Moves console cursor to specified (x, y) position
* Parameters  : x - horizontal position
*               y - vertical position
*********************************************************************************************************
*/
void SetCursorPosition(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



/*
*********************************************************************************************************
* Function    : PrintTime
* Description : Displays the current simulation time on the console
* Parameters  : None
*********************************************************************************************************
*/
void PrintTime() {
    SetCursorPosition(0, 1);

    printf("Time: %02d:%02d:%02d:%03d", 
        timer.hours,
        timer.minutes,
        timer.seconds,
        timer.millis
    );

    fflush(stdout);
}



/*
*********************************************************************************************************
* Function    : ClearConsole
* Description : Clears the console screen
* Parameters  : None
*********************************************************************************************************
*/
void ClearConsole() {
    system("cls"); 
}



/*
*********************************************************************************************************
* Function    : AddLog
* Description : Adds a log message to the circular buffer and file
* Parameters  : msg - log message string
*********************************************************************************************************
*/
void AddLog(const char *msg) {
    strncpy(log_buffer[log_line_index], msg, 63);
    log_buffer[log_line_index][63] = '\0';
    log_line_index = (log_line_index + 1) % MAX_LOG_LINES;
    LogMessageToFile(msg);
}



/*
*********************************************************************************************************
* Function    : PrintLogPanel
* Description : Displays recent log messages in right-side panel
* Parameters  : None
*********************************************************************************************************
*/
void PrintLogPanel() {
    SetCursorPosition(40, 1);
    printf("[LOG MESSAGES]                             ");

    int index = log_line_index;
    for (int i = 0; i < MAX_LOG_LINES; i++) {
        index = (index - 1 + MAX_LOG_LINES) % MAX_LOG_LINES;
        SetCursorPosition(40, 2 + i);
        printf("%-38s\n", log_buffer[index]);
    }
}