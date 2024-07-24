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
#include <../bmp/infoBackground.h>
#include <../bmp/xButton.h>
#include <../bmp/folder.h>
#include <../bmp/picture.h>
#include <../font/Noto_Sans_CJK_HK_14.h>

#include <yss/Directory.h>
#include <yss/Fat32.h>
#include <yss/File.h>
#include <stdio.h>
#include <string.h>

#define MAX_LIST_COUNT		10

typedef struct __attribute__((packed))
{
	uint16_t signature;
	uint32_t size;
	uint32_t reserved;
	uint32_t dataOffset;
	uint32_t infoHeaderSize;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bitCount;
}BmpHeader_t;

class BmpViewer : public Object
{
public :
	BmpViewer(void)
	{
		setSize(480, 272);
		mFrameBuffer->clear();
	}

	virtual ~BmpViewer(void)
	{
		
	}

	void active(File *file)
	{
		uint8_t *buf, r, g, b;
		uint16_t index, w, h, width, height, offset = 0;
		BmpHeader_t *header;
		Color color;

		buf = new uint8_t[512];

		mFile = file;
		
		// BMP 파일 처리
		file->moveToStart();
		file->read(buf, 512);
		
		header = (BmpHeader_t*)buf;

		if(header->signature != 0x4D42 || header->bitCount != 24)
			goto error_handler;

		height = header->height;
		width = header->width;

		if(width > 480)
		{			
			offset = width - 480;
			width = 480;
		}
		
		index = header->width * 3 % 4;
		if(index)
			offset += index;

		if(height > 272)
			height = 272;

		index = header->dataOffset;

		for(int16_t y = height; y >= 0; y--)
		{
			for(int16_t x = 0; x < width; x++)
			{
				b = buf[index++];
				if(index >= 512)
				{
					index = 0;
					file->read(buf, 512);
				}
				
				g = buf[index++];
				if(index >= 512)
				{
					index = 0;
					file->read(buf, 512);
				}

				r = buf[index++];
				if(index >= 512)
				{
					index = 0;
					file->read(buf, 512);
				}

				color.setColor(r, g, b);
				mFrameBuffer->drawDot(x, y, color);
			}
			
			for(uint16_t x = 0; x < offset; x++)
			{
				index++;
				if(index >= 512)
				{
					index = 0;
					file->read(buf, 512);
				}
			}
		}
				
		setVisible(true);
		update();

error_handler :
		delete buf;
	}

private :
	File *mFile;

	virtual void paint(void)
	{
	}

	virtual Object *handlerPush(Position_t pos)
	{
		(void)pos;

		setVisible(false);
		update();

		return this;
	}
};

class FileExplorer : public Object
{
public :
	FileExplorer(void)
	{
		mFat32Dir = new Fat32(sdmmc);
		mFat32File = new Fat32(sdmmc);
		mDir = new Directory(mFat32Dir);
		mFile = new File(mFat32File);

		setSize(480, 272);
		mLastDirCnt = mLastFileCnt = 0;
		mDisplayedFileCount = mDisplayedFolderCount = 0;
		mPage = 0;
		mLastConnectFlag = false;
		mBmpViewer = 0;

		for(uint8_t i=0;i<MAX_LIST_COUNT;i++)
			mList[i] = 0;

		mFrameBuffer->setBackgroundColor(0x30, 0xFF, 0x30);
	}

	virtual ~FileExplorer(void)
	{
		delete mDir;
		delete mFat32Dir;
	}
	
	void refresh(void)
	{
		bool flag = sdmmc.isConnected();

		if(flag && mLastConnectFlag == false)
		{
			mDir->initialize();
			mLastConnectFlag = true;
		}
		else if(!flag)
		{
			for(int32_t i=0;i<MAX_LIST_COUNT;i++)
				mList[i] = 0;

			mLastDirCnt = mLastFileCnt = 0;
			mDisplayedFileCount = mDisplayedFolderCount = 0;
			mPage = 0;
			mLastConnectFlag = false;
		}

		paint();
		update();
	}

	void setBmpViewer(BmpViewer *obj)
	{
		mBmpViewer = obj;
	}

private :
	int32_t mLastFileCnt, mLastDirCnt, mList[10], mPage;
	uint8_t mDisplayedFileCount, mDisplayedFolderCount;
	const Position_t mListStartPos = {10, 10};
	const Size_t mListSize = {460, 24};
	bool mLastConnectFlag;
	Fat32 *mFat32Dir, *mFat32File;
	Directory *mDir;
	File *mFile;
	BmpViewer *mBmpViewer;

	virtual void paint(void)
	{
		int32_t len;
		char *str = new char[256];
		char *name = new char[256];
		Position_t posIcon = mListStartPos, posName = {(int16_t)(mListStartPos.x + 25), (int16_t)(mListStartPos.y + 2)};

		if(sdmmc.isConnected())
		{
			int32_t fileCnt = mDir->getFileCount(), dirCnt = mDir->getDirectoryCount();
			int32_t drawCnt = 0;

			mFrameBuffer->clear();

			mFrameBuffer->setBrushColor(0x30, 0x80, 0x30);
			mFrameBuffer->fillRect({5, 5}, Size_t{470, 262});

			mFrameBuffer->setFontColor(0xFF, 0xFF, 0xFF);
			mFrameBuffer->setFont(Font_Noto_Sans_CJK_HK_14);
			
			for(int32_t i=mPage*MAX_LIST_COUNT;i<dirCnt;i++)
			{
				if(drawCnt >= MAX_LIST_COUNT)
					break;

				mDir->getDirectoryName(i, name, 256);

				sprintf(str, "%s", name);
				mFrameBuffer->drawBitmap(posIcon, folder);
				mFrameBuffer->drawString(posName, str);

				posName.y += 24;
				posIcon.y += 24;
				mList[drawCnt++] = i;
				mDisplayedFolderCount = drawCnt;
			}

			for(int32_t i=mPage*MAX_LIST_COUNT;i<fileCnt;i++)
			{
				if(drawCnt >= MAX_LIST_COUNT)
					break;

				mDir->getFileName(i, name, 256);
				len = strlen(name);

				if(	(name[len-4] == '.' && name[len-3] == 'b' && name[len-2] == 'm' && name[len-1] == 'p') ||
					(name[len-4] == '.' && name[len-3] == 'B' && name[len-2] == 'M' && name[len-1] == 'P'))
				{
					sprintf(str, "%s", name);
					mFrameBuffer->drawBitmap(posIcon, picture);
					mFrameBuffer->drawString(posName, str);

					posName.y += 24;
					posIcon.y += 24;
					mList[drawCnt++] = i;
					mDisplayedFileCount = drawCnt - mDisplayedFolderCount;
				}
			}
			Object::update();

			for(int32_t i=drawCnt;i<MAX_LIST_COUNT;i++)
			{
				mList[drawCnt++] = 0;
			}
		}
		else
		{
			mFrameBuffer->clear();
			Object::update();
		}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmismatched-new-delete"
		delete str;
		delete name;
#pragma GCC diagnostic pop
	}

	virtual Object *handlerPush(Position_t pos)
	{
		int32_t index;
		char *name = new char[256];

		pos.x -= mListStartPos.x;
		pos.y -= mListStartPos.y;
		index = pos.y / mListSize.height;
		
		if(pos.x < mListSize.width && index < MAX_LIST_COUNT)
		{
			if(index < mDisplayedFolderCount)
			{
				mDir->enterDirectory(mList[index]);
				mPage = 0;
				refresh();
			}
			else if(index < mDisplayedFolderCount + mDisplayedFileCount)
			{
				if(mBmpViewer)
				{
					mFile->initialize();
					mFile->setPath(mDir->getCurrentDirectoryCluster());
					mDir->getFileName(mList[index], name, 256);
					mFile->open(name, File::READ_ONLY);
					mBmpViewer->active(mFile);
					mFile->close();
					refresh();
				}
			}
		}
		
		delete name;

		return this;
	}
};

namespace Task
{
	void handler_xBt(void);

	static Frame *gFrame;
	static FileExplorer *gFileExplorer;
	static BmpViewer *gBmpViewer;

	void thread_handleImagePage(void)
	{
		bool mLastConnectFlag = false, flag;
		
		gFileExplorer->refresh();

		while(1)
		{
			flag = sdmmc.isConnected();

			if(mLastConnectFlag != flag)
			{
				mLastConnectFlag = flag;
				gFileExplorer->refresh();
			}
			thread::yield();
		}
	}

	error_t handleImagePage(FunctionQueue *obj)
	{
		(void)obj;

		lock();	// unlock()을 만날 때까지 외부에서 이 함수를 강제 종료 시키지 못한다.
		clearTask();	// 이전에 등록된 쓰레드 등을 전부 제거한다.

		gFrame = new Frame;
		gFileExplorer = new FileExplorer;
		gBmpViewer = new BmpViewer;
		ImageButton *xBt = new ImageButton(&xButton);

		xBt->setPushEventHandler(handler_xBt);
		xBt->setPosition(480 - 35 - 10, 10);

		gBmpViewer->setVisible(false);

		gFileExplorer->setBmpViewer(gBmpViewer);
		
		gFrame->add(gFileExplorer);
		gFrame->add(gBmpViewer);
		gFrame->add(xBt);

		setFrame(gFrame);

		addThread(thread_handleImagePage, 1024);	// thread_handleMainPage() 함수를 스케줄러에 등록한다.
													// addThread() 함수를 통해 등록된 쓰레드는 clearTask() 함수 호출시 종료 된다.

		unlock();	// 외부에서 강제로 종료가 가능하다.

		return error_t::ERROR_NONE;
	}
}


