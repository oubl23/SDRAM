/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: RENDER.h,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.3 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	PT1003  ��ͼʵ��ͷ�ļ�
 ******************************************************************************
 */
#include "platform.h"
#include <string.h>
#include "LCD.h"
#include "SDRAM.h"
#include "DMA2D.h"
#include "FONT.h"
#include "../Texture/Texture.h"

#define TEXTURES_MAX  200	// �����������
#define MAP_LIST_MAX  200 	// �����ͼ��������
// ��������

extern  uint32_t CurrentFrameBuffer;
extern  uint32_t CurrentLayer;



// ����ṹ��
typedef	struct{
	uint32_t	Texture_w;	// �����
	uint32_t	Texture_h;	// �����
	uint8_t		Texture_type;	// ������������
	uint8_t*	Texture_addr;	// ����������ʼ��ַ
} texture_t;

// ��ͼ�ṹ��
typedef	struct{
	uint16_t	x;		// �����������Ļ����x����Ļ���½�Ϊԭ�㣩
	uint16_t	y;		// �����������Ļ����y����Ļ���½�Ϊԭ�㣩
	// ��ͼѡ��
	// �����������꣨�������½�Ϊԭ�㣩
	// bit0-13����������y���꣨�������½�Ϊԭ�㣩���λΪ����λ
	// bit14-27����������x���꣨�������½�Ϊԭ�㣩���λΪ����λ
	// bit29��0��̬��ͼ��1��̬��ͼ
	// bit30��0������ת��1������ת
	// bit31��0��ͼ������Ч��1��ͼ������Ч
	uint32_t	option;		
	uint32_t	color;		// ��ͼ��ɫ��A8R8G8B8
	uint16_t	index;		// ��ͼ��Ӧ����������
	float		angle;		// ��ת�Ƕȣ���λΪ�ȣ�0λ��x�᷽����ʱ��Ϊ���ӡ�0.0<angle<=360.0
} map;

#define	MAP_IS_VALID(m)		(((m).option & (1UL<<31))?1:0)	//�ж����������Ƿ�
#define	MAP_IS_ROTATING(m)	(((m).option & (1UL<<30))?1:0)	//�ж���ͼ�Ƿ���ת
#define	MAP_IS_DYNAMIC(m)	(((m).option & (1UL<<29))?1:0)	//�ж��Ƿ��Ǿ�̬��ͼ���Ƕ�̬��ͼ

texture_t	textures[TEXTURES_MAX];	// �������飬ÿ����Ա��һ������ṹ��
map		map_list[MAP_LIST_MAX];	// ��ͼ�����б�ÿ����Ա��һ����ͼ�����������α������б�����ɻ�ͼ	


DMA2D_config	 	m_DMA2D_config;
DMA2D_BGconfig		m_DMA2D_BGconfig;
DMA2D_FGconfig		m_DMA2D_FGconfig;
// ��������
void RENDER_DrawChar(uint16_t Xpos, uint16_t Ypos, uint8_t* Ascii, uint32_t Color);		// �����ַ�
					
