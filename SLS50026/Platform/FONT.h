 /**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: FONT.h,v $
 * Author	$Author: xuchaopeng $
 * Version	$Revision: 1.1 $
 * Date		$Date: 2015/09/17 01:35:31 $
 * Description	
	点阵字库 
 ******************************************************************************
 */
#include "platform.h"

// 字库结构体
typedef struct DotMatrixFont_s{    
	const uint16_t*		FontData;
	uint16_t 		Width;
	uint16_t 		Height;
  
} DotMatrixFont;

extern DotMatrixFont DotMatrixFont16x24;

