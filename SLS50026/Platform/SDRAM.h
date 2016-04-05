/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: SDRAM.h,v $
 * Author	$Author: xuchaopeng $
 * Version	$Revision: 1.1 $
 * Date		$Date: 2015/09/17 01:35:31 $
 * Description	
	SDRAMͷ�ļ�
 ******************************************************************************
 */
 
#include "platform.h"

// SDRAM�Ļ���ַ
#define SDRAM_BASE	(uint32_t)0xD0000000
// SDRAM���ڴ��С
#define SDRAM_SIZE	(uint32_t)0x800000


/**
  * @brief  FMC SDRAM Mode definition register defines
  */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200) 


// ��������
// -----------------------  SDRAM -----------------------
int SDRAM_Init(void);						// SDRAM��ʼ��
int SDRAM_Bank_initial(uint32_t SDRAM_Bank);                    // SDRAM bank��ʼ������
int SDRAM_Write_Enable(uint32_t SDRAM_Bank, uint8_t State);     // SDRAM дʹ�ܺ���

int SDRAM_SelfCheck(void);					// SDRAM�Լ�
