/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <yss.h>
#include <bsp.h>
#include <bsp.h>
#include <task.h>
#include <memory.h>

int main(void)
{
	// 운영체체 초기화
	initializeYss();
	
	// 보드 초기화
	initializeBoard();

	// 설정 저장용 메모리 초기화
	memory::initilize();
	
	// fq1 동작 시작
	fq1.start();
	
	fq1.add(Task::blinkLedOneTime);
	fq1.add(Task::blinkLedTwoTime);
	fq1.add(Task::blinkLedThreeTime);
	fq1.add(Task::blinkLedFourTime);

	// fq2. 동작 시작
	fq2.start();

	fq2.add(Task::sendUartHelloWorld);
	fq2.add(Task::sendUartYssOs);
	fq2.add(Task::sendUartEnjoyProgramming);
	
	thread::delay(2000);
	fq1.stop();
	fq2.stop();

	while(1)
	{
		thread::yield();
	}
}


