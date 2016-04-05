/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: platform.h,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.3 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	�ӿ��ļ����ӿڰ����У�
	1. GPIO                LED����������/�������
	2. TIMER               ��ʱ������                 
	3. RENDER              ��ͼ��
        
 ******************************************************************************
 */
#include "system.h"

//������������
extern const unsigned char** 	texture_pointer;
extern const unsigned int*	texture_size_pointer;
extern const unsigned int	texture_n;
extern const unsigned int* 	texture_type_pointer;



// ��������:��4λ��ÿ���ض�Ӧ���ֽ�������4λ����������
// 0��ʾ�ر���������ͣ�������
#define	TEXTURE_TYPE_NULL	0x00
// 8bit����0x0��Ӧ��͸����0xFF��Ӧ����ͼ��ɫ��ÿ����1�ֽ�
	
// �����iΪ����
#define TEXTURE_WIDTH(i)	(texture_size_pointer[i]>>16)&0xFFFF
#define TEXTURE_TYPE(i)		(texture_type_pointer[i])&0xFF;
// ����ߣ�iΪ����
#define TEXTURE_HEIGHT(i)	(texture_size_pointer[i])&0xFFFF
// �������ƣ�iΪ����
#define TEXTURE_NAME(i)		(unsigned char*)(texture_pointer[i])	
	





// ----------------------- GPIO -----------------------
int SET_LED(int number, int value);				// LED��/�����ã�numberΪLED��ţ�valueΪ����value=1: ���� value=0: ��

// ----------------------- TIMER -----------------------
int TIMER_Delay_us(int n);					// us��ʱ��
#define TIMER_Delay_ms(n)	TIMER_Delay_us(n*1000)		// ms��ʱ��	

// -----------------------  RENDER -----------------------
int RENDER_initial(void);                                       // ��ͼ��ʼ��
void RENDER_Clear(uint32_t Color);				// ����

int RENDER_DisplayString(uint32_t x, uint32_t y, uint8_t *str, uint32_t Color);         // ��ʾ�ַ�

int RENDER_load_texture(void);					// ��������

// ������ͼ
void RENDER_Clear_Original(uint16_t index,uint32_t Xpos,uint32_t Ypos,uint32_t Color); //���ԭʼλ�õĵ�����

void RENDER_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction,uint32_t color); // ����

void RENDER_Bleding_Image(uint16_t Xpos,uint16_t Ypos,uint8_t index,uint32_t Color);
void RENDER_ShowColor(uint16_t Xpos, uint16_t Ypos,uint16_t index,uint32_t ColorARGB);	//��ʾ��ɫ
void RENDER_PFC(uint16_t Xpos, uint16_t Ypos,uint32_t index);
void RENDER_PFC_CLUT(uint16_t Xpos, uint16_t Ypos,uint32_t index);

int RENDER_add_map(uint16_t x, uint16_t y, uint32_t option, uint32_t color, uint16_t index,  float angle);
void RENDER_draw(void);		//������ͼ
