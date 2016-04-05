/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: DMA2D.h,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.1 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	PT1003 SDRAM
 ******************************************************************************
 */
 
#include "system.h"

//���������ַ
#define DMA2D_SDRAM_ADR			   SDRAM_BASE				//�����ɫ����
#define DMA2D_FG_ADR		           &texture_Test_data1			//��������FG��ɫ����
#define DMA2D_BG_ADR		           &texture_Test_data			//��������BG��ɫ����
#define DMA2D_CLUT_ADRESS		   &CLUT_COLOR					//���ұ��ַ
//LCD ��������
#define LCD_DIR_HORIZONTAL     		  0x0000
#define LCD_DIR_VERTICAL        	  0x0001


//DMA2D mode
#define DMA2D_MODE_M2M				   ((uint32_t)0x00000000) // �ڴ浽�ڴ棬����FG��ȡ
#define DMA2D_MODE_M2M_PFC			   ((uint32_t)0x00010000) // �ڴ浽�ڴ棬����FG PFC�����ȡ
#define DMA2D_MODE_M2M_BLE			   ((uint32_t)0x00020000) // �ڴ浽�ڴ棬ִ��PFC���һ��BG FG
#define DMA2D_MODE_R2M			 	   ((uint32_t)0x00030000) // �Ĵ������ڴ�(�޼���BG��FG)

//DMA2D����
#define DMA2D_CR_MASK                  		   ((uint32_t)0xFFFCE0FC)  //DMA2D CR Mask
#define PFCCR_MASK              		   ((uint32_t)0x00FC00C0)  /* DMA2D FGPFCCR Mask */
//DMA2D��ɫ�Ĵ�����ɫ��ʽ
#define DMA2D_CMODE_ARGB8888                       ((uint32_t)0x00000000)
#define DMA2D_CMODE_RGB888                         ((uint32_t)0x00000001)
#define DMA2D_CMODE_RGB565                         ((uint32_t)0x00000002)
#define DMA2D_CMODE_ARGB1555                       ((uint32_t)0x00000003)
#define DMA2D_CMODE_ARGB4444                       ((uint32_t)0x00000004)
#define DMA2D_CMODE_L8		                   ((uint32_t)0x00000005)
#define DMA2D_CMODE_AL44	                   ((uint32_t)0x00000006)
#define DMA2D_CMODE_AL88                           ((uint32_t)0x00000007)
#define DMA2D_CMODE_L4                             ((uint32_t)0x00000008)
// DMA2D CLUT ��ɫģʽ
#define DMA2D_CCMODE_ARGB8888                      ((uint32_t)0x00000000)
#define DMA2D_CCMODE_RGB888                        ((uint32_t)0x00000010)

// DMA2D Alpha Mode
#define DMA2D_AM_0                        	  	0 //���޸�͸����
#define DMA2D_AM_1                        	  	1//͸�����滻Ϊ��������ֵ
#define DMA2D_AM_2                        	 	2 //͸�����滻Ϊ�˻�

// DMA2D�ṹ��
typedef struct DMA2D_config_s{
	 uint32_t DMA2D_Mode;   		// ����DMA2D�ķ�ʽ
	 uint32_t DMA2D_CMode;          	// �����ɫ��ʽ           
	 uint32_t DMA2D_Blue;           	// ���ͼƬ����ɫֵ 
	 uint32_t DMA2D_Green;			// ���ͼƬ����ɫֵ 
	 uint32_t DMA2D_Red; 			// ���ͼƬ����ɫֵ 
	 uint32_t DMA2D_Alpha; 			// ���ͼƬ��͸���� 
	 uint32_t DMA2D_OMAdd;          	// ���ͼƬ�����ݵ�ַ
	 uint32_t DMA2D_OLineOffset;   		// �����ƫ�Ƶ�ַ
	 uint32_t DMA2D_NumberLine;     	// ����������ݵ�����            
	 uint32_t DMA2D_PixelPerLine;   	// ������ÿ�е�������                	
} DMA2D_config;

// DMA2D ǰ����FG�ṹ��
typedef struct DMA2D_FGconfig_s{
	uint32_t DMA2D_FGMA;        		// ͼƬ���ݵ�ַ
	uint32_t DMA2D_FGO;			// ��ƫ��
	uint32_t DMA2D_FGCM;            	// ������ɫģʽ
	uint32_t DMA2D_FG_CLUT_CM;      	// CLUT��ɫģʽ            
	uint32_t DMA2D_FG_CLUT_Size;    	// CLUT���ݴ�С
	uint32_t DMA2D_FGPFC_ALPHA_Mode;    	// ͸���ȷ�ʽ
	uint32_t DMA2D_FGPFC_ALPHA_Value;   	// ͸����ֵ��0xFF��͸����0x00͸��
	uint32_t DMA2D_FGC_Blue;            	// B��ɫֵ	
	uint32_t DMA2D_FGC_Green;           	// G��ɫֵ	
	uint32_t DMA2D_FGC_Red;             	// R��ɫֵ
	uint32_t DMA2D_FGCMAR;              	// CLUT���ݵ�ַ���������ж��壩
} DMA2D_FGconfig;

// DMA2D ǰ����FG�ṹ��
typedef struct DMA2D_BGconfig_s{
	uint32_t DMA2D_BGMA;        		// ͼƬ���ݵ�ַ
	uint32_t DMA2D_BGO;			// ��ƫ��
	uint32_t DMA2D_BGCM;            	// ������ɫģʽ
	uint32_t DMA2D_BG_CLUT_CM;      	// CLUT��ɫģʽ            
	uint32_t DMA2D_BG_CLUT_Size;    	// CLUT���ݴ�С
	uint32_t DMA2D_BGPFC_ALPHA_Mode;    	// ͸���ȷ�ʽ
	uint32_t DMA2D_BGPFC_ALPHA_Value;   	// ͸����ֵ��0xFF��͸����0x00͸��
	uint32_t DMA2D_BGC_Blue;            	// B��ɫֵ	
	uint32_t DMA2D_BGC_Green;           	// G��ɫֵ	
	uint32_t DMA2D_BGC_Red;             	// R��ɫֵ
	uint32_t DMA2D_BGCMAR;              	// CLUT���ݵ�ַ���������ж��壩
	
} DMA2D_BGconfig;

void DMA2D_Config(DMA2D_config *m_DMA2D_config);			// ����DMA2D
void DMA2D_FGConfig(DMA2D_FGconfig *m_DMA2D_FGconfig);			// ����DMA2D FG
void DMA2D_FG_StructInit(DMA2D_FGconfig *m_DMA2D_FGconfig);		// ǰ����FG�ṹ���ʼ��
void DMA2D_BG_StructInit(DMA2D_BGconfig *m_DMA2D_BGconfig);		// ������BG�ṹ���ʼ��
void DMA2D_BGConfig(DMA2D_BGconfig *m_DMA2D_BGconfig);			// ����DMA2D BG
void DMA2D_StartTransfer(void);						// DMA2D��ʼ��������	
void DMA2D_AbortTransfer(void);						// ��ֹ����

extern uint32_t CLUT_COLOR[256];
