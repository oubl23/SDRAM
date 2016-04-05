/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: DMA2D.h,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.1 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	PT1003 SDRAM
 ******************************************************************************
 */
 
#include "system.h"

//数据输入地址
#define DMA2D_SDRAM_ADR			   SDRAM_BASE				//输出颜色数据
#define DMA2D_FG_ADR		           &texture_Test_data1			//数据输入FG颜色数据
#define DMA2D_BG_ADR		           &texture_Test_data			//数据输入BG颜色数据
#define DMA2D_CLUT_ADRESS		   &CLUT_COLOR					//查找表地址
//LCD 画线配置
#define LCD_DIR_HORIZONTAL     		  0x0000
#define LCD_DIR_VERTICAL        	  0x0001


//DMA2D mode
#define DMA2D_MODE_M2M				   ((uint32_t)0x00000000) // 内存到内存，仅限FG获取
#define DMA2D_MODE_M2M_PFC			   ((uint32_t)0x00010000) // 内存到内存，仅限FG PFC激活获取
#define DMA2D_MODE_M2M_BLE			   ((uint32_t)0x00020000) // 内存到内存，执行PFC并且混合BG FG
#define DMA2D_MODE_R2M			 	   ((uint32_t)0x00030000) // 寄存器到内存(无激活BG和FG)

//DMA2D掩码
#define DMA2D_CR_MASK                  		   ((uint32_t)0xFFFCE0FC)  //DMA2D CR Mask
#define PFCCR_MASK              		   ((uint32_t)0x00FC00C0)  /* DMA2D FGPFCCR Mask */
//DMA2D颜色寄存器颜色格式
#define DMA2D_CMODE_ARGB8888                       ((uint32_t)0x00000000)
#define DMA2D_CMODE_RGB888                         ((uint32_t)0x00000001)
#define DMA2D_CMODE_RGB565                         ((uint32_t)0x00000002)
#define DMA2D_CMODE_ARGB1555                       ((uint32_t)0x00000003)
#define DMA2D_CMODE_ARGB4444                       ((uint32_t)0x00000004)
#define DMA2D_CMODE_L8		                   ((uint32_t)0x00000005)
#define DMA2D_CMODE_AL44	                   ((uint32_t)0x00000006)
#define DMA2D_CMODE_AL88                           ((uint32_t)0x00000007)
#define DMA2D_CMODE_L4                             ((uint32_t)0x00000008)
// DMA2D CLUT 颜色模式
#define DMA2D_CCMODE_ARGB8888                      ((uint32_t)0x00000000)
#define DMA2D_CCMODE_RGB888                        ((uint32_t)0x00000010)

// DMA2D Alpha Mode
#define DMA2D_AM_0                        	  	0 //不修改透明度
#define DMA2D_AM_1                        	  	1//透明度替换为传进来的值
#define DMA2D_AM_2                        	 	2 //透明度替换为乘积

// DMA2D结构体
typedef struct DMA2D_config_s{
	 uint32_t DMA2D_Mode;   		// 配置DMA2D的方式
	 uint32_t DMA2D_CMode;          	// 输出颜色格式           
	 uint32_t DMA2D_Blue;           	// 输出图片蓝颜色值 
	 uint32_t DMA2D_Green;			// 输出图片绿颜色值 
	 uint32_t DMA2D_Red; 			// 输出图片红颜色值 
	 uint32_t DMA2D_Alpha; 			// 输出图片的透明度 
	 uint32_t DMA2D_OMAdd;          	// 输出图片的数据地址
	 uint32_t DMA2D_OLineOffset;   		// 输出行偏移地址
	 uint32_t DMA2D_NumberLine;     	// 待传输的数据的行数            
	 uint32_t DMA2D_PixelPerLine;   	// 待传输每行的像素数                	
} DMA2D_config;

// DMA2D 前景层FG结构体
typedef struct DMA2D_FGconfig_s{
	uint32_t DMA2D_FGMA;        		// 图片数据地址
	uint32_t DMA2D_FGO;			// 行偏移
	uint32_t DMA2D_FGCM;            	// 输入颜色模式
	uint32_t DMA2D_FG_CLUT_CM;      	// CLUT颜色模式            
	uint32_t DMA2D_FG_CLUT_Size;    	// CLUT数据大小
	uint32_t DMA2D_FGPFC_ALPHA_Mode;    	// 透明度方式
	uint32_t DMA2D_FGPFC_ALPHA_Value;   	// 透明度值，0xFF不透明，0x00透明
	uint32_t DMA2D_FGC_Blue;            	// B颜色值	
	uint32_t DMA2D_FGC_Green;           	// G颜色值	
	uint32_t DMA2D_FGC_Red;             	// R颜色值
	uint32_t DMA2D_FGCMAR;              	// CLUT数据地址（可以自行定义）
} DMA2D_FGconfig;

// DMA2D 前景层FG结构体
typedef struct DMA2D_BGconfig_s{
	uint32_t DMA2D_BGMA;        		// 图片数据地址
	uint32_t DMA2D_BGO;			// 行偏移
	uint32_t DMA2D_BGCM;            	// 输入颜色模式
	uint32_t DMA2D_BG_CLUT_CM;      	// CLUT颜色模式            
	uint32_t DMA2D_BG_CLUT_Size;    	// CLUT数据大小
	uint32_t DMA2D_BGPFC_ALPHA_Mode;    	// 透明度方式
	uint32_t DMA2D_BGPFC_ALPHA_Value;   	// 透明度值，0xFF不透明，0x00透明
	uint32_t DMA2D_BGC_Blue;            	// B颜色值	
	uint32_t DMA2D_BGC_Green;           	// G颜色值	
	uint32_t DMA2D_BGC_Red;             	// R颜色值
	uint32_t DMA2D_BGCMAR;              	// CLUT数据地址（可以自行定义）
	
} DMA2D_BGconfig;

void DMA2D_Config(DMA2D_config *m_DMA2D_config);			// 配置DMA2D
void DMA2D_FGConfig(DMA2D_FGconfig *m_DMA2D_FGconfig);			// 配置DMA2D FG
void DMA2D_FG_StructInit(DMA2D_FGconfig *m_DMA2D_FGconfig);		// 前景层FG结构体初始化
void DMA2D_BG_StructInit(DMA2D_BGconfig *m_DMA2D_BGconfig);		// 背景层BG结构体初始化
void DMA2D_BGConfig(DMA2D_BGconfig *m_DMA2D_BGconfig);			// 配置DMA2D BG
void DMA2D_StartTransfer(void);						// DMA2D开始传输数据	
void DMA2D_AbortTransfer(void);						// 终止传输

extern uint32_t CLUT_COLOR[256];
