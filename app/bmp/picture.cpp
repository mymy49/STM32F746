////////////////////////////////////////////////////////////////////////////////////////
//
// yssBmpMaker를 사용해 생성된 코드 입니다.
//
// Home Page : http://cafe.naver.com/yssoperatingsystem
//
////////////////////////////////////////////////////////////////////////////////////////

#include "picture.h"

static const unsigned char data[800] = // 0.8 kB
{
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 10
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 20
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 30
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 40
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 50
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 60
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 70
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 80
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 90
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 100
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 110
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 120
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 130
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 140
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 0x8c, 0xed, 		// 150
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 160
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 170
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 180
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 0x8c, 0xed, 		// 190
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 200
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 210
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 220
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 230
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 240
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 250
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 260
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 270
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 280
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 290
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 300
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 310
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 320
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 330
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 340
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 350
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 360
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 370
	0x00, 0x00, 0x8c, 0xed, 0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 		// 380
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 390
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 400
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 410
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 420
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 430
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 440
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 450
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 460
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 470
	0x8c, 0xed, 0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 480
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 490
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 500
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x00, 0x00, 0x8c, 0xed, 		// 510
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x00, 0x00, 0x8c, 0xed, 		// 520
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 530
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 540
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 550
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x00, 0x00, 0x8c, 0xed, 		// 560
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 0x8c, 0xed, 		// 570
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 580
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 590
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x00, 0x00, 0x8c, 0xed, 		// 600
	0x8c, 0xed, 0x00, 0x00, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 610
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 620
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 630
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x00, 0x00, 0x8c, 0xed, 		// 640
	0x8c, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 650
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 660
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// 670
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xed, 		// 680
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 690
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 700
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 710
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 720
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 730
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 740
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 750
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 760
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 770
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 780
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 		// 790
	0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed, 0x8c, 0xed		// 800
	
};

const Bitmap_t picture = 
{
	20,	// width
	20,	// height
	2,	// type = 0 : RGB565, 1 : RGB888, 2 : ARGB1555
	(unsigned char*)data
};

