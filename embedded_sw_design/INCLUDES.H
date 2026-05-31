/*
*********************************************************************************************************
*                                                uC/OS-II
*                                The Real-Time Kernel (by Jean J. Labrosse)
*
*					WIN32 PORT & LINUX PORT
*
*                          (c) Copyright 2004-... Werner.Zimmermann@fht-esslingen.de
*                                           All Rights Reserved
*
* File : INCLUDES.H
* By   : Werner Zimmermann
*********************************************************************************************************
*/

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef __GNUC__
#include <conio.h>
#endif

#ifdef __WIN32__
#include <windows.h>
#endif

#ifdef __GNUC__
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
#endif

#include "os_cfg.h"
#include "os_cpu.h"
#include "pc.h"
#include "ucos_ii.h"

#include <string.h>
