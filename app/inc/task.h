/*
	Copyright 2024. 홍윤기 all right reserved.

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef TASK__H_
#define TASK__H_

#include <util/FunctionQueue.h>

class Frame;

// FunctionQueue에 의해 순차 수행되는 task의 함수 프로토타입 선언부이다.
namespace Task
{
// task.cpp

	// 테스크의 등록이나 해제 등을 처리하는데 앞서 상호배제를 하기 위해 lock을 한다.
	void lock(void);

	// lock() 함수에서 잠근 사항을 unlock하기 위해 사용한다.
	void unlock(void);

	// 현재 수행하는 주요 테스크에서 쓰레드를 활성화 시키는데 사용한다.
	// 여기서 등록된 쓰레드는 clearTask() 함수를 통해 모두 비활성화 된다.
	//
	// void (*func)(void)
	//		활성화 시킬 쓰레드의 함수 포인터를 설정한다.
	// uint32_t stackSize
	//		쓰레드의 스택 크기를 설정한다.
	void addThread(void (*func)(void), uint32_t stackSize);

	// 이전에 수행하던 주요 테스크가 생성한 자원을 제거하는데 사용한다.
	// 쓰레드와 GUI 객체등이 포함된다.
	void clearTask(void);

	// 현재 수행하는 주요 테스크에서 화면에 나타낼 GUI Frame을 설정한다.
	//
	// Frame *obj
	//		현재 출력할 Frame의 포인터를 설정한다.
	void setFrame(Frame *obj);


// task_displayLogo.cpp

	// 로고를 화면에 출력하고 5초간 정지한다.
	//
	// 반환
	//		발생한 에러를 반환한다.
	error_t displayLogo(FunctionQueue *obj);

// task_hadleMainPage.cpp
	
	// 메인 화면을 출력하고 사용자의 입력을 받아 그에 대응하는 기능을 수행한다.
	//
	// 반환
	//		발생한 에러를 반환한다.
	error_t handleMainPage(FunctionQueue *obj);

// task_handleInfoPage.cpp
	
	// 본 프로그램에 대한 소개글을 출력한다.
	//
	// 반환
	//		발생한 에러를 반환한다.
	error_t handleInfoPage(FunctionQueue *obj);

// task_handleImagePage.cpp

	// 전자 앨범 기능을 수행한다.
	//
	// 반환
	//		발생한 에러를 반환한다.
	error_t handleImagePage(FunctionQueue *obj);
}

#endif

