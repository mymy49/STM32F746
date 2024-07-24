/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <bsp.h>
#include <yss.h>
#include <yss/event.h>
#include <targets/st/bitfield_stm32f746xx.h>

#include <mod/rgb_tft_lcd/RK043FN48H.h>
#include <mod/sdram/MT48LC4M32B2B5_6A.h>
#include <mod/ctouch/FT5336.h>

FunctionQueue fq(16);
RK043FN48H lcd;
FT5336 touch;

#if defined(MB1191_B_03)
N25Q128A1 qflashMem;
#endif

void initializeBoard(void)
{
	// USART1 초기화 (Virtual Com Port)
	gpioA.setAsAltFunc(9, Gpio::PA9_USART1_TX);
	gpioB.setAsAltFunc(7, Gpio::PB7_USART1_RX);

	usart1.enableClock();
	usart1.initialize(115200, 128);
	usart1.enableInterrupt();

	// I2C3 초기화
	gpioH.setAsAltFunc(7, Gpio::PH7_I2C3_SCL, Gpio::OSPEED_MID, Gpio::OTYPE_OPEN_DRAIN);
	gpioH.setAsAltFunc(8, Gpio::PH8_I2C3_SDA, Gpio::OSPEED_MID, Gpio::OTYPE_OPEN_DRAIN);

	i2c3.enableClock();
	i2c3.initializeAsMain(define::i2c::speed::STANDARD);
	i2c3.enableInterrupt();

	// SD 메모리 초기화
	gpioC.setAsAltFunc(8, Gpio::PC8_SDIO_D0, Gpio::OSPEED_MID);
	gpioC.setAsAltFunc(9, Gpio::PC9_SDIO_D1, Gpio::OSPEED_MID);
	gpioC.setAsAltFunc(10, Gpio::PC10_SDIO_D2, Gpio::OSPEED_MID);
	gpioC.setAsAltFunc(11, Gpio::PC11_SDIO_D3, Gpio::OSPEED_MID);
	gpioC.setAsAltFunc(12, Gpio::PC12_SDIO_CK, Gpio::OSPEED_MID);
	gpioD.setAsAltFunc(2, Gpio::PD2_SDIO_CMD, Gpio::OSPEED_MID);
	
	sdmmc.enableClock();
	sdmmc.initialize();
	sdmmc.setVcc(3.3);
	sdmmc.enableInterrupt();

	// setDetectPin() 함수를 가장 마지막에 호출해야 함
	sdmmc.setDetectPin({&gpioC, 13});

#if defined(MB1191_B_03)
	// Quadspi 초기화
	gpioB.setAsAltFunc(2, Gpio::PB2_QUADSPI_CLK);
	gpioB.setAsAltFunc(6, Gpio::PB6_QUADSPI_BK1_NCS);
	gpioD.setAsAltFunc(11, Gpio::PD11_QUADSPI_BK1_IO0);
	gpioD.setAsAltFunc(12, Gpio::PD12_QUADSPI_BK1_IO1);
	gpioE.setAsAltFunc(2, Gpio::PE2_QUADSPI_BK1_IO2);
	gpioD.setAsAltFunc(13, Gpio::PD13_QUADSPI_BK1_IO3);

	quadspi.enableClock();
	quadspi.initialize();
	quadspi.enableInterrupt();
#endif

	// 터치 초기화
	const FT5336::Config touchConfig = 
	{
		i2c3,			//I2c &peri;
		{&gpioI, 13},	//Gpio::Pin isrPin;
		{0, 0}			//Gpio::Pin resetPin;
	};

	touch.initialize(touchConfig);
	event::setPointerDevice(touch);

	// TFT LCD 초기화
	Gpio::altFuncPort_t lcdPort[28] =
	{
		{GPIOJ, 6, Gpio::PJ6_LCD_R7},
		{GPIOJ, 5, Gpio::PJ5_LCD_R6},
		{GPIOJ, 4, Gpio::PJ4_LCD_R5},
		{GPIOJ, 3, Gpio::PJ3_LCD_R4},
		{GPIOJ, 2, Gpio::PJ2_LCD_R3},
		{GPIOJ, 1, Gpio::PJ1_LCD_R2},
		{GPIOJ, 0, Gpio::PJ0_LCD_R1},
		{GPIOI, 15, Gpio::PI15_LCD_R0},

		{GPIOK, 2, Gpio::PK2_LCD_G7},
		{GPIOK, 1, Gpio::PK1_LCD_G6},
		{GPIOK, 0, Gpio::PK0_LCD_G5},
		{GPIOJ, 11, Gpio::PJ11_LCD_G4},
		{GPIOJ, 10, Gpio::PJ10_LCD_G3},
		{GPIOJ, 9, Gpio::PJ9_LCD_G2},
		{GPIOJ, 8, Gpio::PJ8_LCD_G1},
		{GPIOJ, 7, Gpio::PJ7_LCD_G0},

		{GPIOK, 6, Gpio::PK6_LCD_B7},
		{GPIOK, 5, Gpio::PK5_LCD_B6},
		{GPIOK, 4, Gpio::PK4_LCD_B5},
		{GPIOG, 12, Gpio::PG12_LCD_B4},
		{GPIOJ, 15, Gpio::PJ15_LCD_B3},
		{GPIOJ, 14, Gpio::PJ14_LCD_B2},
		{GPIOJ, 13, Gpio::PJ13_LCD_B1},
		{GPIOE, 4, Gpio::PE4_LCD_B0},

		{GPIOI, 9, Gpio::PI9_LCD_VSYNC},
		{GPIOI, 10, Gpio::PI10_LCD_HSYNC},
		{GPIOK, 7, Gpio::PK7_LCD_DE},
		{GPIOI, 14, Gpio::PI14_LCD_CLK}
	};

	gpioA.setPackageAsAltFunc(lcdPort, 28, Gpio::OSPEED_FAST, Gpio::OTYPE_PUSH_PULL);

	gpioI.setAsOutput(12);	// LCD DISP 핀 활성화
	gpioI.setOutput(12, true);

	ltdc.enableClock();
	ltdc.initialize(lcd.getSpecification());
	ltdc.enableInterrupt();

	// Quadspi Memory 초기화
	const N25Q128A1::config_t config = 
	{
		quadspi,
		define::quadspi::bank::BANK1
	};

#if defined(MB1191_B_03)
	qflashMem.setConfig(config);
	qflashMem.initialize();
#endif

	// LED 초기화
	Led::initilize();
}

// OS에서 자동으로 호출함
void initializeSdram(void)
{
	Gpio::altFuncPort_t sdramPort[38]{
		{GPIOF, 0, Gpio::PF0_FMC_A0},
		{GPIOF, 1, Gpio::PF1_FMC_A1},
		{GPIOF, 2, Gpio::PF2_FMC_A2},
		{GPIOF, 3, Gpio::PF3_FMC_A3},
		{GPIOF, 4, Gpio::PF4_FMC_A4},
		{GPIOF, 5, Gpio::PF5_FMC_A5},
		{GPIOF, 12, Gpio::PF12_FMC_A6},
		{GPIOF, 13, Gpio::PF13_FMC_A7},
		{GPIOF, 14, Gpio::PF14_FMC_A8},
		{GPIOF, 15, Gpio::PF15_FMC_A9},
		{GPIOG, 0, Gpio::PG0_FMC_A10},
		{GPIOG, 1, Gpio::PG1_FMC_A11},
		{GPIOG, 4, Gpio::PG4_FMC_BA0},
		{GPIOG, 5, Gpio::PG5_FMC_BA1},
		{GPIOD, 14, Gpio::PD14_FMC_D0},
		{GPIOD, 15, Gpio::PD15_FMC_D1},
		{GPIOD, 0, Gpio::PD0_FMC_D2},
		{GPIOD, 1, Gpio::PD1_FMC_D3},
		{GPIOE, 7, Gpio::PE7_FMC_D4},
		{GPIOE, 8, Gpio::PE8_FMC_D5},
		{GPIOE, 9, Gpio::PE9_FMC_D6},
		{GPIOE, 10, Gpio::PE10_FMC_D7},
		{GPIOE, 11, Gpio::PE11_FMC_D8},
		{GPIOE, 12, Gpio::PE12_FMC_D9},
		{GPIOE, 13, Gpio::PE13_FMC_D10},
		{GPIOE, 14, Gpio::PE14_FMC_D11},
		{GPIOE, 15, Gpio::PE15_FMC_D12},
		{GPIOD, 8, Gpio::PD8_FMC_D13},
		{GPIOD, 9, Gpio::PD9_FMC_D14},
		{GPIOD, 10, Gpio::PD10_FMC_D15},
		{GPIOE, 0, Gpio::PE0_FMC_NBL0},
		{GPIOE, 1, Gpio::PE1_FMC_NBL1},
		{GPIOG, 8, Gpio::PG8_FMC_SDCLK},
		{GPIOH, 5, Gpio::PH5_FMC_SDNWE},
		{GPIOF, 11, Gpio::PF11_FMC_SDNRAS},
		{GPIOG, 15, Gpio::PG15_FMC_SDNCAS},
		{GPIOC, 3, Gpio::PC3_FMC_SDCKE0},
		{GPIOH, 3, Gpio::PH3_FMC_SDNE0}
	};

	gpioA.setPackageAsAltFunc(sdramPort, 38, Gpio::OSPEED_FAST, Gpio::OTYPE_PUSH_PULL);

	clock.enableSdram();
	sdram.initialize(define::sdram::bank::BANK1, MT48LC4M32B2B5_6A, 216000000);
}

void initializeSystem(void)
{
	using namespace define::clock;

	// 외부 클럭 활성화
#if defined(HSE_CLOCK_FREQ)
	clock.enableHse(HSE_CLOCK_FREQ);
#endif

	// Power Controller 활성화
	clock.enableApb1Clock(RCC_APB1ENR_PWREN_Pos);

	// Main PLL 클럭 설정
	// inputVCO = inputClock / m;	1~2 MHz를 만들어야 함
	// VCO = inputVCO * n;			192~432 MHz를 만들어야 함
	// P(PLLCLK) = VCO / pDiv;		180 MHz를 넘어선 안됨
	// Q(PLL48CK) = VCO / qDiv;		적정 클럭은 48 MHz, 75MHz를 넘어선 안됨
	// R은 사용 안함

	// SAI PLL 클럭 설정
	// inputVCO = inputClock / m;	Main PLL에서 설정된 값을 그대로 적용 받음
	// VCO = inputVCO * n;			192~432 MHz를 만들어야 함
	// P는 사용 안함
	// Q(PLLSAICLK) = VCO / qDiv;	45 MHz를 넘어선 안됨
	// R(PLLLCDCLK) = VCO / rDiv;	42 MHz를 넘어선 안됨

	// Main PLL 설정
	clock.enableMainPll(
#if defined(HSE_CLOCK_FREQ)
		pll::src::HSE,				// uint8_t src
		HSE_CLOCK_FREQ / 1000000,	// uint8_t m
#else
		pll::src::HSI,				// uint8_t src
		16000000 / 1000000,			// uint8_t m
#endif
		432,						// uint16_t n
		pll::pdiv::DIV2,			// uint8_t pDiv
		pll::qdiv::DIV9,			// uint8_t qDiv
		pll::rdiv::DIV7				// uint8_t rDiv
	);
	
	// SAI PLL 설정
	clock.enableSaiPll(
		192,                 // uint32_t n
		saipll::pdiv::DIV4,  // uint8_t pDiv
		saipll::qdiv::DIV15, // uint8_t qDiv
		saipll::rdiv::DIV7   // uint8_t rDiv
	);

	// 시스템 클럭 설정
	flash.setLatency(216000000, 33);
	clock.setSysclk(
		sysclk::src::PLL,       // uint8_t sysclkSrc;
		sysclk::ahbDiv::NO_DIV, // uint8_t ahb;
		sysclk::apbDiv::DIV4,   // uint8_t apb1;
		sysclk::apbDiv::DIV2,   // uint8_t apb2;
		33						// uint8_t vcc
	);

	// 명령어 캐쉬 활성화
	SCB_EnableICache();
	
	// Flash Prefetch, ART Accelerator 활성화
	flash.enableArtAccelerator();
	flash.enablePrefetch();
	
	// SDRAM 주소 Remap
	clock.enableApb2Clock(RCC_APB2ENR_SYSCFGEN_Pos);
	setFieldData(SYSCFG->MEMRMP, SYSCFG_MEMRMP_SWP_FMC_Msk, 1, SYSCFG_MEMRMP_SWP_FMC_Pos);

	// GPIO 클럭 활성화
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOAEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOBEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOCEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIODEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOEEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOFEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOGEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOHEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOIEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOJEN_Pos);
	clock.enableAhb1Clock(RCC_AHB1ENR_GPIOKEN_Pos);
}
