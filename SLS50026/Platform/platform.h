/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: platform.h,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.3 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	接口文件，接口包含有：
	1. GPIO                LED、基本输入/输出操作
	2. TIMER               定时器驱动                 
	3. RENDER              绘图库
        
 ******************************************************************************
 */
#include "system.h"

//纹理数据类型
extern const unsigned char** 	texture_pointer;
extern const unsigned int*	texture_size_pointer;
extern const unsigned int	texture_n;
extern const unsigned int* 	texture_type_pointer;



// 纹理类型:低4位是每像素对应的字节数，高4位是纹理类型
// 0表示特别的纹理类型：空纹理
#define	TEXTURE_TYPE_NULL	0x00
// 8bit纹理，0x0对应于透明，0xFF对应于贴图颜色，每像素1字节
	
// 纹理宽，i为索引
#define TEXTURE_WIDTH(i)	(texture_size_pointer[i]>>16)&0xFFFF
#define TEXTURE_TYPE(i)		(texture_type_pointer[i])&0xFF;
// 纹理高，i为索引
#define TEXTURE_HEIGHT(i)	(texture_size_pointer[i])&0xFFFF
// 纹理名称，i为索引
#define TEXTURE_NAME(i)		(unsigned char*)(texture_pointer[i])	
	





// ----------------------- GPIO -----------------------
int SET_LED(int number, int value);				// LED亮/灭设置，number为LED编号，value为亮灭，value=1: 亮； value=0: 灭；

// ----------------------- TIMER -----------------------
int TIMER_Delay_us(int n);					// us定时器
#define TIMER_Delay_ms(n)	TIMER_Delay_us(n*1000)		// ms定时器	

// -----------------------  RENDER -----------------------
int RENDER_initial(void);                                       // 绘图初始化
void RENDER_Clear(uint32_t Color);				// 清屏

int RENDER_DisplayString(uint32_t x, uint32_t y, uint8_t *str, uint32_t Color);         // 显示字符

int RENDER_load_texture(void);					// 载入纹理

// 纹理贴图
void RENDER_Clear_Original(uint16_t index,uint32_t Xpos,uint32_t Ypos,uint32_t Color); //清除原始位置的的数据

void RENDER_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction,uint32_t color); // 画线

void RENDER_Bleding_Image(uint16_t Xpos,uint16_t Ypos,uint8_t index,uint32_t Color);
void RENDER_ShowColor(uint16_t Xpos, uint16_t Ypos,uint16_t index,uint32_t ColorARGB);	//显示颜色
void RENDER_PFC(uint16_t Xpos, uint16_t Ypos,uint32_t index);
void RENDER_PFC_CLUT(uint16_t Xpos, uint16_t Ypos,uint32_t index);

int RENDER_add_map(uint16_t x, uint16_t y, uint32_t option, uint32_t color, uint16_t index,  float angle);
void RENDER_draw(void);		//纹理贴图
