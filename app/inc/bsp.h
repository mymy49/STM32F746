/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#ifndef BSP__H_
#define BSP__H_

// 타겟 보드 설정 (MB1191_B_03)
#define MB1191_B_03

#include <util/FunctionQueue.h>
#include <dev/led.h>

#if defined(MB1191_B_03)
#include <mod/qsflash/N25Q128A1.h>

extern N25Q128A1 qflashMem;
#endif

void initializeBoard(void);

extern FunctionQueue fq1, fq2;

#endif

