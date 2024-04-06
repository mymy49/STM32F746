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

#include <task.h>
#include <yss.h>
#include <bsp.h>
#include <task.h>
#include <../bmp/mainBackground.h>
#include <../bmp/infoButton.h>
#include <../bmp/imageButton.h>

namespace Task
{
	static Frame *gFrame;

	void handler_infoBt(void)
	{
		fq.lock();
		fq.add(handleInfoPage);
		fq.unlock();
	}

	void handler_imageBt(void)
	{
		fq.lock();
		fq.add(handleImagePage);
		fq.unlock();
	}

	error_t handleMainPage(FunctionQueue *obj)
	{
		(void)obj;

		lock();	// unlock()을 만날 때까지 외부에서 이 함수를 강제 종료 시키지 못한다.
		clearTask();	// 이전에 등록된 쓰레드 등을 전부 제거한다.

		gFrame = new Frame;
		Bitmap *bmp = new Bitmap;
		ImageButton *infoBt = new ImageButton(&infoButton);
		ImageButton *imageBt = new ImageButton(&imageButton);

		infoBt->setPushEventHandler(handler_infoBt);
		infoBt->setPosition(30, 30);

		imageBt->setPushEventHandler(handler_imageBt);
		imageBt->setPosition(120, 30);

		bmp->setBmp(mainBackground);
		gFrame->add(bmp);
		gFrame->add(infoBt);
		gFrame->add(imageBt);

		setFrame(gFrame);

		unlock();	// 외부에서 강제로 종료가 가능하다.

		return error_t::ERROR_NONE;
	}
}


