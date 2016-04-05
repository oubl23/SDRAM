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
	PT1003 ��ʱ��
 ******************************************************************************
 */
 
 #include "TIMER.h"
 
/*DESCRIPTION
 *      �û�ʹ�õ�΢�붨ʱ��
 *ARGUMENTS
 * 	n	�û�ϣ����ʱ��΢����
 *RETURN
 *	0 	�������óɹ�
 *NOTES
 *    
 */
 
int TIMER_Delay_us(int n)
{	
	TIM3->CNT	= 0;
	TIM3->CR1 = TIM_CR1_CEN; 			// ������ʱ��
	for(;n>=0;n--){
		while(!(TIM3->SR&TIM_SR_UIF));		// �ȴ���ʱ�����
		
		CLEAR_BIT(TIM3->SR, TIM_SR_UIF);	// �����־λ
		
	}
	
	CLEAR_BIT(TIM3->CR1,TIM_CR1_CEN);		// �رն�ʱ��
	return 0;
}


