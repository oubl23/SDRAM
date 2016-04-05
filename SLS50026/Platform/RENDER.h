/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: RENDER.h,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.3 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	PT1003  绘图实现头文件
 ******************************************************************************
 */
#include "platform.h"
#include <string.h>
#include "LCD.h"
#include "SDRAM.h"
#include "DMA2D.h"
#include "FONT.h"
#include "../Texture/Texture.h"

#define TEXTURES_MAX  200	// 最大纹理数据
#define MAP_LIST_MAX  200 	// 最大贴图纹理数据
// 申明定义

extern  uint32_t CurrentFrameBuffer;
extern  uint32_t CurrentLayer;



// 纹理结构体
typedef	struct{
	uint32_t	Texture_w;	// 纹理宽
	uint32_t	Texture_h;	// 纹理高
	uint8_t		Texture_type;	// 纹理数据类型
	uint8_t*	Texture_addr;	// 纹理数据起始地址
} texture_t;

// 贴图结构体
typedef	struct{
	uint16_t	x;		// 纹理对齐点的屏幕坐标x（屏幕左下角为原点）
	uint16_t	y;		// 纹理对齐点的屏幕坐标y（屏幕左下角为原点）
	// 贴图选项
	// 纹理对齐点坐标（纹理左下角为原点）
	// bit0-13：纹理对齐点y坐标（纹理左下角为原点）最高位为符号位
	// bit14-27：纹理对齐点x坐标（纹理左下角为原点）最高位为符号位
	// bit29：0静态贴图；1动态贴图
	// bit30：0纹理不旋转；1纹理旋转
	// bit31：0贴图操作无效；1贴图操作有效
	uint32_t	option;		
	uint32_t	color;		// 贴图颜色，A8R8G8B8
	uint16_t	index;		// 贴图对应的纹理索引
	float		angle;		// 旋转角度，单位为度，0位置x轴方向，逆时针为增加。0.0<angle<=360.0
} map;

#define	MAP_IS_VALID(m)		(((m).option & (1UL<<31))?1:0)	//判断纹理数据是否
#define	MAP_IS_ROTATING(m)	(((m).option & (1UL<<30))?1:0)	//判断贴图是否旋转
#define	MAP_IS_DYNAMIC(m)	(((m).option & (1UL<<29))?1:0)	//判断是否是静态贴图还是动态贴图

texture_t	textures[TEXTURES_MAX];	// 纹理数组，每个成员是一个纹理结构体
map		map_list[MAP_LIST_MAX];	// 绘图操作列表，每个成员是一个绘图操作，将依次遍历此列表以完成绘图	


DMA2D_config	 	m_DMA2D_config;
DMA2D_BGconfig		m_DMA2D_BGconfig;
DMA2D_FGconfig		m_DMA2D_FGconfig;
// 函数定义
void RENDER_DrawChar(uint16_t Xpos, uint16_t Ypos, uint8_t* Ascii, uint32_t Color);		// 绘制字符
					
