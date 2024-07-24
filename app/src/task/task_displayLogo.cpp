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

#include <stdio.h>
#include <task.h>
#include <yss.h>
#include <bsp.h>
#include <memory.h>
#include <yss/gui.h>
#include <../bmp/logo.h>
#include <../font/Noto_Sans_CJK_HK_14.h>
#include <yss/debug.h>
#include <gui/FrameBufferRgb888.h>

class Logo : public Object
{
public :
	Logo(void)
	{
		setSize(logo.width, logo.height + 20);
	}

private :
	virtual void paint(void)
	{
		char str[32];
		Position_t pos = {0, 0};
				
		mFrameBuffer->setBackgroundColor(0xFF, 0xFF, 0xFF);
		mFrameBuffer->clear();
		mFrameBuffer->drawBitmap({0, 19}, logo);
		mFrameBuffer->setFont(Font_Noto_Sans_CJK_HK_14);
		mFrameBuffer->setFontColor(0x00, 0x00, 0x00);
		
		sprintf(str, "Version %d.%d.%d builld %05d", VER_MAJOR, VER_MINOR, VER_PATCH, VER_BUILD);
		pos.x = 479 - Font_Noto_Sans_CJK_HK_14.getStringWidth(str) - 10;
		if(pos.x < 0)
			pos.x = 0;

		mFrameBuffer->drawString(pos, str);
	}	
};

namespace Task
{
	error_t displayLogo(FunctionQueue *obj)
	{
		(void)obj;
		
		lock();	// unlock()을 만날 때까지 외부에서 이 함수를 강제 종료 시키지 못한다.
		clearTask();	// 이전에 등록된 쓰레드 등을 전부 제거한다.

		Logo *logo = new Logo;
		Frame *frame = new Frame;
		Size_t size = frame->getSize();

		logo->setPosition({0, (int16_t)((size.height - logo->getSize().height) / 2)});
				
		frame->setBackgroundColor(0xFF, 0xFF, 0xFF, 0xFF);
		frame->add(logo);

		setFrame(frame);

		// 5초간 로고 화면에서 대기한다.
		thread::delay(5000);
		
		unlock();

		return error_t::ERROR_NONE;
	}
}


