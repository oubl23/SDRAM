/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: GPIO.c,v $
 * Author	$Author: xuchaopeng $
 * Version	$Revision: 1.1 $
 * Date		$Date: 2015/09/17 01:35:31 $
 * Description	
	GPIO操作实现
 ******************************************************************************
 */
#include "GPIO.h"

 /*DESCRIPTION
 *      LED亮、灭设置
 *ARGUMENTS
 * 	number		0：LED0；1：LED1；2：LED2
 *	value		0：不亮；1： 亮
 *RETURN
 *	0 		函数调用成功
 *NOTES
 *    
 */
int SET_LED(int number, int value)
{
	switch(number){
		case 0:		// LED2
			GPIO_OUTPUT(C, 13, value);
			break;
		case 1:		// LED3
			GPIO_OUTPUT(B, 2, value);
			break;
		case 2:		// 编程灯2（绿）
			GPIO_OUTPUT(G, 3, value);
			break;
		default:
			;
	}
	
	return 0;
	
}
