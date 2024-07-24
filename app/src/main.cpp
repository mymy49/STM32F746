/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <yss.h>
#include <bsp.h>
#include "memory.h"
#include "task.h"

int main(void)
{
	bool mLastDetectFlag = false, flag;

	// 운영체체 초기화
	initializeYss();
	
	// 보드 초기화
	initializeBoard();

	// 설정 저장용 메모리 초기화
	memory::initialize();

	// Function Queue 처리 시작
	fq.start();

	fq.add(Task::displayLogo);		// 로고 출력
	fq.add(Task::handleMainPage);	// 메인 페이지 처리

	while(1)
	{
		flag = sdmmc.isDetected();

		if(mLastDetectFlag != flag)
		{
			mLastDetectFlag = flag;

			if(flag && !sdmmc.isConnected())
				sdmmc.connect();
			else if(!flag && sdmmc.isConnected())
				sdmmc.disconnect();
		}
		thread::yield();
	}
}

