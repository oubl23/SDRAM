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
	GPIO����ʵ��
 ******************************************************************************
 */
#include "GPIO.h"

 /*DESCRIPTION
 *      LED����������
 *ARGUMENTS
 * 	number		0��LED0��1��LED1��2��LED2
 *	value		0��������1�� ��
 *RETURN
 *	0 		�������óɹ�
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
		case 2:		// ��̵�2���̣�
			GPIO_OUTPUT(G, 3, value);
			break;
		default:
			;
	}
	
	return 0;
	
}
