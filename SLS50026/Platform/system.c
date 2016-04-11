/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: system.c,v $
 * Author	$Author: xuchaopeng $
 * Version	$Revision: 1.1 $
 * Date		$Date: 2015/09/17 01:35:32 $
 * Description	
	PT1003 ϵͳ��ʼ��
 ******************************************************************************
 */
#include "system.h"


// ��������
void pin_setup(void)
{
	// LTDC
	GPIO_SET_AF(H, 2, GPIO_AF_LTDC);	// LCD_R0
	GPIO_SET_AF(H, 3, GPIO_AF_LTDC);	// LCD_R1
	GPIO_SET_AF(H, 8, GPIO_AF_LTDC);	// LCD_R2
	GPIO_SET_AF(B, 0, GPIO_AF9);		// LCD_R3
	GPIO_SET_AF(H, 10, GPIO_AF_LTDC);	// LCD_R4
	GPIO_SET_AF(H, 11, GPIO_AF_LTDC);	// LCD_R5
	GPIO_SET_AF(B, 1, GPIO_AF9);		// LCD_R6
	GPIO_SET_AF(G, 6, GPIO_AF_LTDC);	// LCD_R7
	
	GPIO_SET_AF(E, 5, GPIO_AF_LTDC);	// LCD_G0
	GPIO_SET_AF(E, 6, GPIO_AF_LTDC);	// LCD_G1
	GPIO_SET_AF(H, 13, GPIO_AF_LTDC);	// LCD_G2
	GPIO_SET_AF(H, 14, GPIO_AF_LTDC);	// LCD_G3
	GPIO_SET_AF(H, 15, GPIO_AF_LTDC);	// LCD_G4
	GPIO_SET_AF(I, 0, GPIO_AF_LTDC);	// LCD_G5
	GPIO_SET_AF(I, 1, GPIO_AF_LTDC);	// LCD_G6
	GPIO_SET_AF(I, 2, GPIO_AF_LTDC);	// LCD_G7
	
	GPIO_SET_AF(E, 4, GPIO_AF_LTDC);	// LCD_B0
	GPIO_SET_AF(G, 12, GPIO_AF_LTDC);	// LCD_B1
	GPIO_SET_AF(G, 10, GPIO_AF_LTDC);	// LCD_B2
	GPIO_SET_AF(G, 11, GPIO_AF_LTDC);	// LCD_B3
	GPIO_SET_AF(I, 4, GPIO_AF_LTDC);	// LCD_B4
	GPIO_SET_AF(I, 5, GPIO_AF_LTDC);	// LCD_B5
	GPIO_SET_AF(I, 6, GPIO_AF_LTDC);	// LCD_B6
	GPIO_SET_AF(I, 7, GPIO_AF_LTDC);	// LCD_B7
	
	GPIO_SET_AF(I, 9, GPIO_AF_LTDC);	// LCD_VSYNC
	GPIO_SET_AF(I, 10, GPIO_AF_LTDC);	// LCD_HSYNC
	GPIO_SET_AF(F, 10, GPIO_AF_LTDC);	// LCD_DE
	GPIO_SET_AF(G, 7, GPIO_AF_LTDC);	// LCD_CLK
	
	// SDRAM
	GPIO_SET_AF(F, 0, GPIO_AF_FMC);		// FMC_A0
	GPIO_SET_AF(F, 1, GPIO_AF_FMC);		// FMC_A1
	GPIO_SET_AF(F, 2, GPIO_AF_FMC);		// FMC_A2
	GPIO_SET_AF(F, 3, GPIO_AF_FMC);		// FMC_A3
	GPIO_SET_AF(F, 4, GPIO_AF_FMC);		// FMC_A4
	GPIO_SET_AF(F, 5, GPIO_AF_FMC);		// FMC_A5
	GPIO_SET_AF(F, 12, GPIO_AF_FMC);	// FMC_A6
	GPIO_SET_AF(F, 13, GPIO_AF_FMC);	// FMC_A7
	GPIO_SET_AF(F, 14, GPIO_AF_FMC);	// FMC_A8
	GPIO_SET_AF(F, 15, GPIO_AF_FMC);	// FMC_A9
	GPIO_SET_AF(G, 0, GPIO_AF_FMC);		// FMC_A10
	GPIO_SET_AF(G, 1, GPIO_AF_FMC);		// FMC_A11
	
	GPIO_SET_AF(D, 14, GPIO_AF_FMC);	// FMC_D0
	GPIO_SET_AF(D, 15, GPIO_AF_FMC);	// FMC_D1
	GPIO_SET_AF(D, 0, GPIO_AF_FMC);		// FMC_D2
	GPIO_SET_AF(D, 1, GPIO_AF_FMC);		// FMC_D3
	GPIO_SET_AF(E, 7, GPIO_AF_FMC);		// FMC_D4
	GPIO_SET_AF(E, 8, GPIO_AF_FMC);		// FMC_D5
	GPIO_SET_AF(E, 9, GPIO_AF_FMC);		// FMC_D6
	GPIO_SET_AF(E, 10, GPIO_AF_FMC);	// FMC_D7
	GPIO_SET_AF(E, 11, GPIO_AF_FMC);	// FMC_D8
	GPIO_SET_AF(E, 12, GPIO_AF_FMC);	// FMC_D9
	GPIO_SET_AF(E, 13, GPIO_AF_FMC);	// FMC_D10
	GPIO_SET_AF(E, 14, GPIO_AF_FMC);	// FMC_D11
	GPIO_SET_AF(E, 15, GPIO_AF_FMC);	// FMC_D12
	GPIO_SET_AF(D, 8, GPIO_AF_FMC);		// FMC_D13
	GPIO_SET_AF(D, 9, GPIO_AF_FMC);		// FMC_D14
	GPIO_SET_AF(D, 10, GPIO_AF_FMC);	// FMC_D15

//	GPIO_SET_AF(D, 0, GPIO_AF_FMC);		// FMC_D0
//	GPIO_SET_AF(E, 9, GPIO_AF_FMC);		// FMC_D1
//	GPIO_SET_AF(D, 8, GPIO_AF_FMC);		// FMC_D2
//	GPIO_SET_AF(E, 12, GPIO_AF_FMC);	// FMC_D3
	
	GPIO_SET_AF(H, 6, GPIO_AF_FMC);		// FMC_SDNE1
	GPIO_SET_AF(H, 7, GPIO_AF_FMC);		// FMC_SDCKE1
	
	GPIO_SET_AF(G, 4, GPIO_AF_FMC);		// FMC_BA0
	GPIO_SET_AF(G, 5, GPIO_AF_FMC);		// FMC_BA1
	
	GPIO_SET_AF(G, 8, GPIO_AF_FMC);		// FMC_SDCLK
	GPIO_SET_AF(C, 0, GPIO_AF_FMC);		// FMC_SDNWE
	GPIO_SET_AF(F, 11, GPIO_AF_FMC);	// FMC_SDNRAS
	GPIO_SET_AF(G, 15, GPIO_AF_FMC);	// FMC_SDNCAS
	
	GPIO_SET_AF(E, 0, GPIO_AF_FMC);		// FMC_NBL0
	GPIO_SET_AF(E, 1, GPIO_AF_FMC);		// FMC_NBL1
	
	// CAN
	GPIO_SET_AF(B, 8, GPIO_AF_CAN1);	// CAN1_RX
	GPIO_SET_AF(B, 9, GPIO_AF_CAN1);	// CAN1_TX
	
	GPIO_SET_AF(B, 12, GPIO_AF_CAN2);	// CAN2_RX
	GPIO_SET_AF(B, 13, GPIO_AF_CAN2);	// CAN2_TX

	// USART
	GPIO_SET_AF(G, 9, GPIO_AF_USART6);	// USART6_RX
	GPIO_SET_AF(C, 6, GPIO_AF_USART6);	// USART6_TX
	
	GPIO_SET_AF(D, 6, GPIO_AF_USART2);	// USART2_RX
	GPIO_SET_AF(D, 5, GPIO_AF_USART2);	// USART2_TX
	
	GPIO_SET_AF(C, 11, GPIO_AF_USART2);	// USART3_RX
	GPIO_SET_AF(B, 10, GPIO_AF_USART2);	// USART3_TX
	
	// SPI
	GPIO_SET_AF(C, 2, GPIO_AF_SPI2);	// SPI2_MISO
	GPIO_SET_AF(C, 3, GPIO_AF_SPI2);	// SPI2_MOSI
	GPIO_SET_AF(D, 3, GPIO_AF_SPI2);	// SPI2_SCK
	
	GPIO_SET_AF(B, 4, GPIO_AF_SPI2);	// SPI3_MISO
	GPIO_SET_AF(C, 12, GPIO_AF_SPI2);	// SPI3_MOSI
	GPIO_SET_AF(C, 10, GPIO_AF_SPI2);	// SPI3_SCK
	
	// I2C
	GPIO_SET_AF(B, 6, GPIO_AF_I2C1);	// I2C1_SCL
	GPIO_SET_AF(B, 7, GPIO_AF_I2C1);	// I2C1_SDA
	
	GPIO_SET_AF(H, 4, GPIO_AF_I2C2);	// I2C2_SCL
	GPIO_SET_AF(H, 5, GPIO_AF_I2C2);	// I2C2_SDA
	
	GPIO_SET_AF(A, 8, GPIO_AF_I2C3);	// I2C3_SCL
	GPIO_SET_AF(C, 9, GPIO_AF_I2C3);	// I2C3_SDA
	
	// USB
	GPIO_SET_AF(A, 9, GPIO_AF_OTG_FS);	// OTG_FS_VBUS
	GPIO_SET_AF(A, 11, GPIO_AF_OTG_FS);	// OTG_FS_DM
	GPIO_SET_AF(A, 12, GPIO_AF_OTG_FS);	// OTG_FS_DP
	
	// ETH
	GPIO_SET_AF(C, 4, GPIO_AF_ETH);		// ETH_RXD0
	GPIO_SET_AF(C, 5, GPIO_AF_ETH);		// ETH_RXD1
	GPIO_SET_AF(G, 13, GPIO_AF_ETH);	// ETH_TXD0
	GPIO_SET_AF(G, 14, GPIO_AF_ETH);	// ETH_TXD1
	GPIO_SET_AF(C, 1, GPIO_AF_ETH);		// ETH_MDC
	GPIO_SET_AF(A, 1, GPIO_AF_ETH);		// ETH_REF_CLK
	GPIO_SET_AF(A, 2, GPIO_AF_ETH);		// ETH_MDIO
	GPIO_SET_AF(A, 7, GPIO_AF_ETH);		// ETH_CRS_DV
	GPIO_SET_AF(B, 11, GPIO_AF_ETH);	// ETH_TX_EN
	
	// LED
	GPIO_SET_LED(C,13);			// LED0
	GPIO_SET_LED(B,2);			// LED1
	GPIO_SET_LED(G,3);			// LED2
	
}


// ϵͳ��ʼ��
void SystemInit(void)
{
	// ����FPU
	#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
		SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  // set CP10 and CP11 Full Access
	#endif 
	
	// �ر�ȫ���ж�
	RCC->CIR	= 0x00000000;
	
	// -------------------- ����HSEʱ�� -------------------- 
	// ʹ���ⲿʱ��Դ��ΪHSE����ֹ�ڲ�����
	// ʹ����Դ����, ����·
	SET_BIT(RCC->CR, RCC_CR_HSEBYP);
	// ����HSE
	SET_BIT(RCC->CR, RCC_CR_HSEON);
	
	// �ȴ�HSE׼����
	while(!(RCC->CR&RCC_CR_HSERDY)){
		;
	}
	
	// -------------------- ����PLLϵ�� -------------------- 
	// �ⲿʱ��Դ8MHz��ϵͳʱ��180MHz
#define	PLL_M		8
#define	PLL_N		360
#define	PLL_P		2
#define	PLL_Q		7
#define	PLLSAI_N	182
#define	PLLSAI_R	7

	MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, PLL_M << 0);
	MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN, PLL_N << 6);
	MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLP, ((PLL_P >> 1) -1) << 16);
	MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ, PLL_Q << 24);

	// ��HSE��ΪPLL������
	SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE);
	
	/* Select regulator voltage output Scale 1 mode, System frequency up to 180 MHz */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS;
	
	// ����RCC_DCKCFGR��TIMPREΪ0,��APB�ķ�Ƶϵ��Ϊ1ʱ��Ƶ�ʱ��ֲ��䣬����ΪAPBƵ�ʵ�����
	CLEAR_BIT(RCC->DCKCFGR, RCC_DCKCFGR_TIMPRE);
	
	// -------------------- ����Ԥ��Ƶ -------------------- 
	// ����AHB��Ƶ	1
	MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);
	
	// ����APB1��Ƶ	4
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV4);
	
	// ����APB2��Ƶ	2
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV2);

	
	// ʹ��PLL
	SET_BIT(RCC->CR, RCC_CR_PLLON);
	
	// �ȴ�PLL�ȶ�
	while(!(RCC->CR&RCC_CR_PLLRDY)){
		;
	}
	
	// -----------------	����PLLSAI��ʱ��	-------------------
	MODIFY_REG(RCC->PLLSAICFGR, RCC_PLLSAICFGR_PLLSAIN, PLLSAI_N << 6);
	MODIFY_REG(RCC->PLLSAICFGR, RCC_PLLSAICFGR_PLLSAIR, PLLSAI_R << 28);
	
	// ����LCD_CLK��Ƶ��Ϊ6.5MHZ,����PLLCDCLK�ķ�ƵΪ4
	MODIFY_REG(RCC->DCKCFGR, 0x00030000, 1 << 16);
	// ʹ��PLLSAI
	SET_BIT(RCC->CR, RCC_CR_PLLSAION);
	// �ȴ�PLLSAI�ȶ�
	while(!(RCC->CR&RCC_CR_PLLSAION)){
		;
	}
	
	 /* Enable the Over-drive to extend the clock frequency to 180 Mhz */
	PWR->CR |= PWR_CR_ODEN;
	while((PWR->CSR & PWR_CSR_ODRDY) == 0)
	{
	}
	PWR->CR |= PWR_CR_ODSWEN;
	while((PWR->CSR & PWR_CSR_ODSWRDY) == 0)
	{
	} 
	
	/* Configure Flash prefetch, Instruction cache, Data cache and wait state */
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
	
	// -------------------- ѡ��ʱ��Դ -------------------- 
	// ѡ��PLLΪʱ��Դ
	MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
	
	// �ȴ����óɹ�
	while((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL){
		;
	}
	
	
	// �ر�ȫ���ж�
	RCC->CIR = 0x00000000;
	
	// ������ʱ��
	RCC->AHB1ENR	|= 			 \
		RCC_AHB1ENR_GPIOAEN        	|\
		RCC_AHB1ENR_GPIOBEN        	|\
		RCC_AHB1ENR_GPIOCEN        	|\
		RCC_AHB1ENR_GPIODEN        	|\
		RCC_AHB1ENR_GPIOEEN        	|\
		RCC_AHB1ENR_GPIOFEN        	|\
		RCC_AHB1ENR_GPIOGEN        	|\
		RCC_AHB1ENR_GPIOHEN        	|\
		RCC_AHB1ENR_GPIOIEN        	|\
		RCC_AHB1ENR_DMA1EN         	|\
		RCC_AHB1ENR_DMA2EN		|\
		RCC_AHB1ENR_DMA2DEN;
	RCC->AHB2ENR	|= RCC_AHB2ENR_OTGFSEN;
	RCC->APB1ENR	|=			 \
		RCC_APB1ENR_PWREN   		|\
		RCC_APB1ENR_TIM2EN   		|\
		RCC_APB1ENR_TIM3EN   		|\
		RCC_APB1ENR_TIM4EN   		|\
		RCC_APB1ENR_TIM5EN   		|\
		RCC_APB1ENR_TIM6EN   		|\
		RCC_APB1ENR_TIM7EN   		|\
		RCC_APB1ENR_TIM12EN  		|\
		RCC_APB1ENR_TIM13EN  		|\
		RCC_APB1ENR_TIM14EN  		|\
		RCC_APB1ENR_SPI2EN   		|\
		RCC_APB1ENR_CAN1EN   		|\
		RCC_APB1ENR_CAN2EN		|\
		RCC_APB1ENR_DACEN;
	RCC->APB2ENR	|=			 \
		RCC_APB2ENR_TIM1EN     		|\
		RCC_APB2ENR_TIM8EN     		|\
		RCC_APB2ENR_TIM9EN     		|\
		RCC_APB2ENR_TIM10EN    		|\
		RCC_APB2ENR_TIM11EN    		|\
		RCC_APB2ENR_ADC1EN     		|\
		RCC_APB2ENR_ADC2EN     		|\
		RCC_APB2ENR_ADC3EN     		|\
		RCC_APB2ENR_SPI1EN     		|\
		RCC_APB2ENR_LTDCEN     		|\
		RCC_APB2ENR_SYSCFGEN;
	RCC->AHB3ENR	|=
		RCC_AHB3ENR_FMCEN;
		
	
	// -------------------- �������� --------------------
	pin_setup();
	
	// ------------------- 	����TIM3��ʱ��  --------------
	/*  TIM3ʹ��APB1ʱ��Ƶ�ʣ�APB1Ƶ��Ϊ45MHZ,��TIM3��ʱ��Ƶ��Ϊ90MHZ��APB��Ƶ��Ϊ1ʱ����Ƶ�� */
	// ��������Ƶ��Ϊ1MHZ
	TIM3->CR1 = TIM_CR1_ARPE;
	TIM3->PSC = 0;
	TIM3->ARR = 90;            
	TIM3->CR1 = TIM_CR1_UDIS; 	// ��UDIS��1���͸����¼�
	TIM3->CR1 = TIM_CR1_DIR; 	//ѡ�������Ϊ��������ģʽ 
	
	
	
}
