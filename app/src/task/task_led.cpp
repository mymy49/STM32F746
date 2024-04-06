/*
	Copyright 2023. 홍윤기 all right reserved.

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

#include <task.h>
#include <yss.h>
#include <bsp.h>

namespace Task
{
	error_t blinkLedOneTime(FunctionQueue *fq)
	{
		(void)fq;

		// LED의 지정된 횟수만큼 동작
		for(int32_t i = 0;i < 1;i++)
		{
			Led::on(true);
			thread::delay(500);

			Led::on(false);
			thread::delay(500);
		}

		// 현재 동작이 완료 됐음을 알리는 빠른 깜빡임	
		for(int32_t i = 0;i < 3;i++)
		{
			Led::on(true);
			thread::delay(50);

			Led::on(false);
			thread::delay(50);
		}

		return error_t::ERROR_NONE;
	}

	error_t blinkLedTwoTime(FunctionQueue *fq)
	{
		(void)fq;

		// LED의 지정된 횟수만큼 동작
		for(int32_t i = 0;i < 2;i++)
		{
			Led::on(true);
			thread::delay(500);

			Led::on(false);
			thread::delay(500);
		}

		// 현재 동작이 완료 됐음을 알리는 빠른 깜빡임	
		for(int32_t i = 0;i < 3;i++)
		{
			Led::on(true);
			thread::delay(50);

			Led::on(false);
			thread::delay(50);
		}

		return error_t::ERROR_NONE;
	}

	error_t blinkLedThreeTime(FunctionQueue *fq)
	{
		(void)fq;

		// LED의 지정된 횟수만큼 동작
		for(int32_t i = 0;i < 3;i++)
		{
			Led::on(true);
			thread::delay(500);

			Led::on(false);
			thread::delay(500);
		}

		// 현재 동작이 완료 됐음을 알리는 빠른 깜빡임	
		for(int32_t i = 0;i < 3;i++)
		{
			Led::on(true);
			thread::delay(50);

			Led::on(false);
			thread::delay(50);
		}

		return error_t::ERROR_NONE;
	}

	error_t blinkLedFourTime(FunctionQueue *fq)
	{
		(void)fq;

		// LED의 지정된 횟수만큼 동작
		for(int32_t i = 0;i < 4;i++)
		{
			Led::on(true);
			thread::delay(500);

			Led::on(false);
			thread::delay(500);
		}

		// 현재 동작이 완료 됐음을 알리는 빠른 깜빡임	
		for(int32_t i = 0;i < 3;i++)
		{
			Led::on(true);
			thread::delay(50);

			Led::on(false);
			thread::delay(50);
		}

		return error_t::ERROR_NONE;
	}
}

