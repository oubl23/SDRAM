/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: main.h,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.3 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	主函数头文件
 ******************************************************************************
 */
#include "../Platform/platform.h"


// 贴图选项
#define	MAP_OPTION_VALID			((uint32_t)0x80000000) //有效
#define	MAP_OPTION_ROTATING			((uint32_t)0x40000000) //旋转
#define	MAP_OPTION_DYNAMIC			((uint32_t)0x20000000) //动态
#define MAP_OPTION_UNVALID			((uint32_t)0x00000000)

// 颜色选项
#define COLOR32_WHITE		0xFFFFFFFF
#define	COLOR32_BLACK		0xFF000000
#define COLOR32_RED		0xFFFF0000
#define COLOR32_YELLOW		0xFFFFFF00
