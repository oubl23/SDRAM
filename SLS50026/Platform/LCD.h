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
	LCD头文件
 ******************************************************************************
 */
#include "platform.h"
#include "SDRAM.h"

// 显示分辨率
#define LCD_WIDTH		320
#define LCD_HEIGHT		240

// 缓冲大小定义（以ARGB计算，大小为LCD_WIDTH*LCD_HEIGHT*4）
#define BUFFER_OFFSET          	((uint32_t)0x4B000)

// SDRAM内存分配，依次为层1 GRAM、层2 GRAM、BGRAM、TEXTURE
#define	GRAM_BASE_LAYER1	SDRAM_BASE	//0xD0000000
#define GRAM_SIZE_LAYER1	BUFFER_OFFSET
#define GRAM_BASE_LAYER2	(GRAM_BASE_LAYER1+BUFFER_OFFSET) //0xD004B000
#define GRAM_SIZE_LAYER2	BUFFER_OFFSET
// 静态显示在显示屏幕上面，只是起到保存数据的作用
#define BGRASE_BASE		(GRAM_BASE_LAYER2+BUFFER_OFFSET) //D0096000
#define BGRASE_SIZE		BUFFER_OFFSET

// 混合的目的地址
#define BELEDING_BASE		BGRASE_BASE+BUFFER_OFFSET
#define BELEDING_SIZE		BUFFER_OFFSET
#define TEXTURE_BASE		BELEDING_BASE+BUFFER_OFFSET //D00E1000,D0119400


#define GCR_MASK               	((uint32_t)0x0FFE888F)

// 像素格式
#define LTDC_Pixelformat_ARGB8888                  ((uint32_t)0x00000000)
#define LTDC_Pixelformat_RGB888                    ((uint32_t)0x00000001)
#define LTDC_Pixelformat_RGB565                    ((uint32_t)0x00000002)
#define LTDC_Pixelformat_ARGB1555                  ((uint32_t)0x00000003)
#define LTDC_Pixelformat_ARGB4444                  ((uint32_t)0x00000004)
#define LTDC_Pixelformat_L8                        ((uint32_t)0x00000005)
#define LTDC_Pixelformat_AL44                      ((uint32_t)0x00000006)
#define LTDC_Pixelformat_AL88                      ((uint32_t)0x00000007)

// 混合因子
#define LTDC_BlendingFactor1_CA                    ((uint32_t)0x00000400)
#define LTDC_BlendingFactor1_PAxCA                 ((uint32_t)0x00000600)
#define LTDC_BlendingFactor2_CA                    ((uint32_t)0x00000005)
#define LTDC_BlendingFactor2_PAxCA                 ((uint32_t)0x00000007)

// 变量定义

// LCD 配置结构体
typedef struct LCD_config_s{
        uint32_t        LCD_HorizontalSync_Width;       // 行同步宽度
        uint32_t        LCD_VerticalSync_Height;        // 场同步宽度
        uint32_t        LCD_HBP;                        // 行后沿
        uint32_t        LCD_VBP;                        // 场后沿
        uint32_t        LCD_HFP;                        // 行前沿
        uint32_t        LCD_VFP;                        // 场前沿
        uint32_t        LCD_Width;                      // 有效像素宽
        uint32_t        LCD_Height;                     // 有效像素高
}LCD_config;

// LCD layer配置结构体
typedef struct LCD_Layer_config_s{
        uint32_t        LCD_HorizontalStart;            // 窗口显示行起始位置
        uint32_t        LCD_HorizontalStop;             // 窗口显示行终止位置
        uint32_t        LCD_VerticalStart;              // 窗口显示场起始位置 
        uint32_t        LCD_VerticalStop;               // 窗口显示场终止位置 
        uint32_t        LCD_PixelFormat;                // 像素格式: ARGB8888，RGB888，RGB565等
        uint32_t        LCD_ConstantAlpha;              // 指定的常量Alpha，用于混合
} LCD_Layer_config;

// 函数定义
#define LCD_BACKGROUND_LAYER    0
#define LCD_LAYER_ONE           1
#define LCD_LAYER_TWO           2
#define LCD_LAYER_ALL           3


int LCD_Initial(uint8_t   LCD_Layers);					        // 液晶屏初始化					
void LCD_SelfCheck(void);							// LCD自检
int LCD_Clear(uint16_t color);							// 清屏操作
int Pixel(uint16_t x0,uint16_t y0,uint16_t w,uint16_t h, uint16_t color);	
int LCD_LayerInit(LTDC_Layer_TypeDef* LTDC_Layerx);     			// LCD层初始化, 根据传入参数对相应层初始化
void LCD_ReloadReg(uint32_t LCD_Reload);					// 重载类型

