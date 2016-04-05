/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: LCD.h,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.3 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	LCDͷ�ļ�
 ******************************************************************************
 */
#include "platform.h"
#include "SDRAM.h"

// ��ʾ�ֱ���
#define LCD_WIDTH		320
#define LCD_HEIGHT		240

// �����С���壨��ARGB���㣬��СΪLCD_WIDTH*LCD_HEIGHT*4��
#define BUFFER_OFFSET          	((uint32_t)0x4B000)

// SDRAM�ڴ���䣬����Ϊ��1 GRAM����2 GRAM��BGRAM��TEXTURE
#define	GRAM_BASE_LAYER1	SDRAM_BASE	//0xD0000000
#define GRAM_SIZE_LAYER1	BUFFER_OFFSET
#define GRAM_BASE_LAYER2	(GRAM_BASE_LAYER1+BUFFER_OFFSET) //0xD004B000
#define GRAM_SIZE_LAYER2	BUFFER_OFFSET
// ��̬��ʾ����ʾ��Ļ���棬ֻ���𵽱������ݵ�����
#define BGRASE_BASE		(GRAM_BASE_LAYER2+BUFFER_OFFSET) //D0096000
#define BGRASE_SIZE		BUFFER_OFFSET

// ��ϵ�Ŀ�ĵ�ַ
#define BELEDING_BASE		BGRASE_BASE+BUFFER_OFFSET
#define BELEDING_SIZE		BUFFER_OFFSET
#define TEXTURE_BASE		BELEDING_BASE+BUFFER_OFFSET //D00E1000,D0119400


#define GCR_MASK               	((uint32_t)0x0FFE888F)

// ���ظ�ʽ
#define LTDC_Pixelformat_ARGB8888                  ((uint32_t)0x00000000)
#define LTDC_Pixelformat_RGB888                    ((uint32_t)0x00000001)
#define LTDC_Pixelformat_RGB565                    ((uint32_t)0x00000002)
#define LTDC_Pixelformat_ARGB1555                  ((uint32_t)0x00000003)
#define LTDC_Pixelformat_ARGB4444                  ((uint32_t)0x00000004)
#define LTDC_Pixelformat_L8                        ((uint32_t)0x00000005)
#define LTDC_Pixelformat_AL44                      ((uint32_t)0x00000006)
#define LTDC_Pixelformat_AL88                      ((uint32_t)0x00000007)

// �������
#define LTDC_BlendingFactor1_CA                    ((uint32_t)0x00000400)
#define LTDC_BlendingFactor1_PAxCA                 ((uint32_t)0x00000600)
#define LTDC_BlendingFactor2_CA                    ((uint32_t)0x00000005)
#define LTDC_BlendingFactor2_PAxCA                 ((uint32_t)0x00000007)

// ��������

// LCD ���ýṹ��
typedef struct LCD_config_s{
        uint32_t        LCD_HorizontalSync_Width;       // ��ͬ�����
        uint32_t        LCD_VerticalSync_Height;        // ��ͬ�����
        uint32_t        LCD_HBP;                        // �к���
        uint32_t        LCD_VBP;                        // ������
        uint32_t        LCD_HFP;                        // ��ǰ��
        uint32_t        LCD_VFP;                        // ��ǰ��
        uint32_t        LCD_Width;                      // ��Ч���ؿ�
        uint32_t        LCD_Height;                     // ��Ч���ظ�
}LCD_config;

// LCD layer���ýṹ��
typedef struct LCD_Layer_config_s{
        uint32_t        LCD_HorizontalStart;            // ������ʾ����ʼλ��
        uint32_t        LCD_HorizontalStop;             // ������ʾ����ֹλ��
        uint32_t        LCD_VerticalStart;              // ������ʾ����ʼλ�� 
        uint32_t        LCD_VerticalStop;               // ������ʾ����ֹλ�� 
        uint32_t        LCD_PixelFormat;                // ���ظ�ʽ: ARGB8888��RGB888��RGB565��
        uint32_t        LCD_ConstantAlpha;              // ָ���ĳ���Alpha�����ڻ��
} LCD_Layer_config;

// ��������
#define LCD_BACKGROUND_LAYER    0
#define LCD_LAYER_ONE           1
#define LCD_LAYER_TWO           2
#define LCD_LAYER_ALL           3


int LCD_Initial(uint8_t   LCD_Layers);					        // Һ������ʼ��					
void LCD_SelfCheck(void);							// LCD�Լ�
int LCD_Clear(uint16_t color);							// ��������
int Pixel(uint16_t x0,uint16_t y0,uint16_t w,uint16_t h, uint16_t color);	
int LCD_LayerInit(LTDC_Layer_TypeDef* LTDC_Layerx);     			// LCD���ʼ��, ���ݴ����������Ӧ���ʼ��
void LCD_ReloadReg(uint32_t LCD_Reload);					// ��������

