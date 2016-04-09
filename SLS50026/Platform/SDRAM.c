/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: SDRAM.c,v $
 * Author	$Author: xuchaopeng $
 * Version	$Revision: 1.1 $
 * Date		$Date: 2015/09/17 01:35:31 $
 * Description	
	PT1003 SDRAM
 ******************************************************************************
 */
 
#include "SDRAM.h"
 
#define ERROR_BANK              -1
#define ERROR_ENABLE_STATE      -2 
#define ERROR_SDRAM_CHECK	-3
 
#define SDRAM_BANK1             0
#define SDRAM_BANK2             1
 
#define SDRAM_WRITE_PROTECT     0
#define SDRAM_WRITE_ENABLE      1
 
 /*DESCRIPTION
 *      SDRAM��ʼ������
 *ARGUMENTS
 * 	NULL
 *RETURN
 *	0 	�������óɹ�
 *NOTES
 *    
 */
int SDRAM_Init(void)
{
        uint32_t       MDR_temp = 0;
        
        // SDRAM bank��ʼ��
        SDRAM_Bank_initial(SDRAM_BANK2);
        
        // -------------- SDRAM ��ʼ������ --------------
        // ʱ������ʹ������
        while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);        // �ȴ�SDRAM������׼����
        // Clock Configuration Enable��Bank 2��1 Auto-refresh cycle��
        FMC_Bank5_6->SDCMR = FMC_SDCMR_MODE_0 | FMC_SDCMR_CTB2;
        
        // ��ʱ100us
        TIMER_Delay_us(100);
        
        // PALL����
        while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);        // �ȴ�SDRAM������׼����
        // PALL��Bank 2��1 Auto-refresh cycle��
        FMC_Bank5_6->SDCMR = FMC_SDCMR_MODE_1 | FMC_SDCMR_CTB2;
        
        // �Զ�ˢ������
        while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);        // �ȴ�SDRAM������׼����
        // Auto-refresh command��Bank 2��4 Auto-refresh cycle�������͵�һ�Σ�
        FMC_Bank5_6->SDCMR = (FMC_SDCMR_MODE_0 | FMC_SDCMR_MODE_1) |\
                              FMC_SDCMR_CTB2 | FMC_SDCMR_NRFS_0 | FMC_SDCMR_NRFS_1;
        
        while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);        // �ȴ�SDRAM������׼����
        // Auto-refresh command��Bank 2��4 Auto-refresh cycle�������͵ڶ��Σ�
        FMC_Bank5_6->SDCMR = (FMC_SDCMR_MODE_0 | FMC_SDCMR_MODE_1) |\
                              FMC_SDCMR_CTB2 | FMC_SDCMR_NRFS_0 | FMC_SDCMR_NRFS_1;
        
        
        // ����ģʽ�Ĵ���
        // �ⲿ�ڴ�ģʽ�Ĵ�������
        MDR_temp        = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |\
                                    SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |\
                                    SDRAM_MODEREG_CAS_LATENCY_3           |\
                                    SDRAM_MODEREG_OPERATING_MODE_STANDARD |\
                                    SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
                                    
        while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);        // �ȴ�SDRAM������׼����
        // Load Mode Register��Bank 2��1 Auto-refresh cycle��MDR��MDR_temp
        FMC_Bank5_6->SDCMR = FMC_SDCMR_MODE_2 | FMC_SDCMR_CTB2 | (MDR_temp<<9);
        
        // ����ˢ����
        // Refresh rate = (SDRAM refresh rate �� SDRAM clock frequency) �C 20
        // SDRAM refresh rate = SDRAM refresh period / Number of rows
        FMC_Bank5_6->SDRTR |= (683<< 1);        
        
        while(FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);        // �ȴ�SDRAM������׼����


        // дʹ�ܣ��ر�д������
        SDRAM_Write_Enable(SDRAM_BANK2, SDRAM_WRITE_ENABLE);
        
        return 0;
 }


 /*DESCRIPTION
 *      SDRAM дʹ�ܺ���
 *ARGUMENTS
 * 	SDRAM_Bank      SDRAM bank
 *      State           1��дʹ�ܣ�2��д��ʹ�ܣ�д������
 *RETURN
 *	0 	                �������óɹ�
 *      ERROR_BANK              bank�������
 *      ERROR_ENABLE_STATE      ����״̬����
 *NOTES
 *    
 */
int SDRAM_Write_Enable(uint32_t SDRAM_Bank, uint8_t State)
{
        if((SDRAM_Bank!=SDRAM_BANK1) || (SDRAM_Bank!=SDRAM_BANK2))
                return ERROR_BANK;
        
        // дʹ�ܣ��ر�д������
        if(State==SDRAM_WRITE_ENABLE){
               FMC_Bank5_6->SDCR[SDRAM_Bank] &=  (uint32_t)0x00007DFF;
        }else if(State==SDRAM_WRITE_PROTECT){   		// д����
               FMC_Bank5_6->SDCR[SDRAM_Bank] |=  (uint32_t)0x00000200;
        }else
               return ERROR_ENABLE_STATE;                       
        
        return 0;
}
 
 /*DESCRIPTION
 *      SDRAM��ʼ������
 *ARGUMENTS
 * 	SDRAM_Bank      SDRAM bank
 *RETURN
 *	0 	        �������óɹ�
 *      ERROR_BANK      bank�������
 *NOTES
 *    
 */
int SDRAM_Bank_initial(uint32_t SDRAM_Bank)
{
        // ���ݴ����bank������Ӧ��ʼ��
        if(SDRAM_Bank == SDRAM_BANK1){                   // bank1
                /* SDRAM bank ���ƼĴ�������
                 NC��8bit��NR��12bit��NWID��16bit��NB��4��CAS��3 cycles��WP��0(����д)��
                 SDCLK��2 HCLK cycle��RBURST��0��RPIPE��1 HCLK cycle */ 
		/* SDRAM bank ���ƼĴ�������
                 NC��10bit��NR��12bit��NWID��16bit��NB��4��CAS��3 cycles��WP��0(����д)��
                 SDCLK��2 HCLK cycle��RBURST��0��RPIPE��1 HCLK cycle */ 
                FMC_Bank5_6->SDCR[SDRAM_BANK1] &= 0x00000000;
                FMC_Bank5_6->SDCR[SDRAM_BANK1]  = FMC_SDCR1_NC_1	|\
						  FMC_SDCR1_NR_0        |\
						  FMC_SDCR2_MWID_0      |\
                                                  FMC_SDCR1_NB          |\
                                                  FMC_SDCR1_CAS         |\
                                                  FMC_SDCR1_SDCLK_1     |\
                                                  FMC_SDCR1_RPIPE_0;
//                FMC_Bank5_6->SDCR[SDRAM_BANK1]  = FMC_SDCR1_NR_0        |\
//                                                  FMC_SDCR1_MWID_0      |\
//                                                  FMC_SDCR1_NB          |\
//                                                  FMC_SDCR1_CAS         |\
//                                                  FMC_SDCR1_SDCLK_1     |\
//                                                  FMC_SDCR1_RPIPE_0;
                
                // DRAM bank ʱ��Ĵ�������
                // TMRD: 2��TXSR: 7��TRAS��4��TRC��7��TWR��2��TRP��2��TRCD��2
		// TMRD: 2��TXSR: 7��TRAS��4��TRC��6��TWR��2��TRP��2��TRCD��3
                FMC_Bank5_6->SDTR[SDRAM_BANK1] &= 0x00000000;
                FMC_Bank5_6->SDTR[SDRAM_BANK1]  = FMC_SDTR1_TMRD_0      |\
                                                  FMC_SDTR1_TXSR_2      |\
						  FMC_SDTR1_TXSR_1      |\
                                                  FMC_SDTR1_TRAS_1      |\
						  FMC_SDTR1_TRAS_0      |\
                                                  FMC_SDTR1_TRC_2       |\
                                                  FMC_SDTR1_TRC_0       |\
                                                  FMC_SDTR1_TWR_0       |\
                                                  FMC_SDTR1_TRP_0       |\
                                                  FMC_SDTR1_TRCD_0;
         
        }else if(SDRAM_Bank == SDRAM_BANK2){             // bank2
                /* SDRAM bank ���ƼĴ�������
                 NC: 8bit��NR: 12bit��NWID: 16bit��NB: 4��CAS: 3 cycles��WP: 0(����д)��
                 SDCLK��RBURST��RPUPE: don't care */ 
                FMC_Bank5_6->SDCR[SDRAM_BANK1] &= 0x00000000;
                FMC_Bank5_6->SDCR[SDRAM_BANK2] &= 0x00000000;
                FMC_Bank5_6->SDCR[SDRAM_BANK1]  = FMC_SDCR2_SDCLK_1 | FMC_SDCR2_RPIPE_0;
                FMC_Bank5_6->SDCR[SDRAM_BANK2]  = FMC_SDCR1_NC_1	|\
						  FMC_SDCR2_NR_0        |\
                                                  FMC_SDCR2_MWID_0      |\
                                                  FMC_SDCR2_NB          |\
                                                  FMC_SDCR2_CAS;
                
                // SDRAM bank ʱ��Ĵ�������
                // TMRD: 2��TXSR: 7��TRAS��4��TRC��7��TWR��2��TRP��2��TRCD��2
                FMC_Bank5_6->SDTR[SDRAM_BANK1] &= 0x00000000;
                FMC_Bank5_6->SDTR[SDRAM_BANK2] &= 0x00000000;                
                
                FMC_Bank5_6->SDTR[SDRAM_BANK1]  = FMC_SDTR2_TRC_2       |\
                                                  FMC_SDTR2_TRC_0       |\
                                                  FMC_SDTR2_TRP_0;
                
                FMC_Bank5_6->SDTR[SDRAM_BANK2]  = FMC_SDTR2_TMRD_0      |\
                                                  FMC_SDTR2_TXSR_2      |\
                                                  FMC_SDTR2_TXSR_1      |\
                                                  FMC_SDTR2_TRAS_1      |\
                                                  FMC_SDTR2_TRAS_0      |\
                                                  FMC_SDTR2_TWR_0       |\
                                                  FMC_SDTR2_TRCD_0;
        }else
                return ERROR_BANK;
        
        return 0;
}

 /*DESCRIPTION
 *      SDRAM�Լ캯��
 *ARGUMENTS
 * 	NULL
 *RETURN
 *	
 *NOTES
 *    1. ��SDRAM��������д�룬��ȡ֮����д���ֵ���жԱȣ���ͬ���Լ�ɹ�������ʧ��
 *    2. �Լ�ɹ���ʹLED2������ʧ����Ʋ��������ش���ֵ
 */
int SDRAM_SelfCheck()
{
	uint32_t	add_offset = 0;
	uint8_t		Wirte_data = 0xFF;	// д�������
	uint8_t		Read_data = 0;		// ��ȡ������
	
	// �Ȳ���
	for (add_offset = 0x00; add_offset < SDRAM_SIZE; add_offset++ ){
		*((uint8_t*) SDRAM_BASE + add_offset) = (uint8_t)0x00;
	}
	
	// д������
	for (add_offset = 0x00; add_offset < SDRAM_SIZE; add_offset++ ){
		*((uint8_t*) SDRAM_BASE + add_offset)  = (uint8_t)(Wirte_data);
	}
	// ��ȡ�Ƚ�
	add_offset = 0;
	while(add_offset<SDRAM_SIZE){
		// ��ȡ����
		Read_data	= *((uint8_t*) SDRAM_BASE + add_offset);
		// ��ͬ�����LED2
		if(Read_data == (uint8_t)(Wirte_data + add_offset)){
			 SET_LED(0, 0);
		}else{
			// �Լ�ʧ��
			SET_LED(0, 1);
			return ERROR_SDRAM_CHECK;
		}
		add_offset++;
	}
	
	return 0;

}


