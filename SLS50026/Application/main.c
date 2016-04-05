 /**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: main.c,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.3 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	PT1003 主函数框架
 ******************************************************************************
 */
#include "main.h"
#include "../Platform/SDRAM.h" 
//static void Delay(__IO uint32_t nCount)
//{
//  /* Decrement nCount value */
//  while (nCount != 0)
//  {
//    nCount--;
//  }
//}
#define BLACKGROUND_COLOR	0xFFFFFFFF
void texture_load(void);
int main(void)
{ 
//	uint16_t  x= 100;
//	uint16_t  y= 100;
//	uint32_t i=10;
//	uint32_t n=10;
	// LED初始化不亮
//	SET_LED(0, 1);
//	SET_LED(1, 1);
//	Delay(0x3FFFFF);
	SDRAM_Init();
	SDRAM_SelfCheck();
//        // 绘图显示初始化， 包含对SDRAM、LCD的初始化和自检
//        RENDER_initial(); 
//        
//	//载入纹理
//	RENDER_load_texture();	
//	
//	// 清屏
//	RENDER_Clear(BLACKGROUND_COLOR);	
//	
//	// 字符显示测试
//	RENDER_DisplayString(100, 60, (uint8_t*)"Test OK!", 0x00FF00);
//	// 清屏
//	RENDER_Clear(BLACKGROUND_COLOR);
//	RENDER_add_map(0,0,MAP_OPTION_VALID,0xFFFFFFFF,0,0);
//	RENDER_add_map(70,20,MAP_OPTION_VALID,0xFFFFFFFF,1,0);
	while(1){

//		RENDER_add_map(x +=10,y+=10,MAP_OPTION_VALID|MAP_OPTION_DYNAMIC,0x64FF0000,2,0);
//		RENDER_add_map(i +=10,n+=10,MAP_OPTION_VALID|MAP_OPTION_DYNAMIC,0x64FF0000,1,0);
//		RENDER_add_map(50,80,MAP_OPTION_VALID|MAP_OPTION_DYNAMIC,0xFFFF0000,0,0);
//		RENDER_draw();
	}
	
}	 

 /* 
 * DESCRIPTION
 * 	纹理载入
 * ARGUMENTS
 *	
 * RETURN
 *	
 * NOTES
 *	依次载入需要绘制的纹理
 */ 
//void texture_load(void)
//{
//	
//	RENDER_load_texture(0, TEXTURE_WIDTH(0), TEXTURE_HEIGHT(0), TEXTURE_TYPE_24BIT);
//	

//	RENDER_load_texture(1, TEXTURE_WIDTH(1), TEXTURE_HEIGHT(1), TEXTURE_TYPE_8BIT);
//	

//	RENDER_load_texture(2, TEXTURE_WIDTH(2), TEXTURE_HEIGHT(2), TEXTURE_TYPE_16BIT);
//	
//}
