/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: TIMER.c,v $
 * Author	$Author: xuchaopeng $
 * Version	$Revision: 1.1 $
 * Date		$Date: 2015/09/17 01:35:31 $
 * Description	
	PT1003 定时器
 ******************************************************************************
 */
 
 #include "TIMER.h"
 
/*DESCRIPTION
 *      用户使用的微秒定时器
 *ARGUMENTS
 * 	n	用户希望延时的微秒数
 *RETURN
 *	0 	函数调用成功
 *NOTES
 *    
 */
 
int TIMER_Delay_us(int n)
{	
	TIM3->CNT	= 0;
	TIM3->CR1 = TIM_CR1_CEN; 			// 启动定时器
	for(;n>=0;n--){
		while(!(TIM3->SR&TIM_SR_UIF));		// 等待计时器溢出
		
		CLEAR_BIT(TIM3->SR, TIM_SR_UIF);	// 清除标志位
		
	}
	
	CLEAR_BIT(TIM3->CR1,TIM_CR1_CEN);		// 关闭定时器
	return 0;
}


