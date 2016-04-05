 /**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: RENDER.c,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.3 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	PT1003  ͼ�λ�����ʾʵ��
 ******************************************************************************
 */

#include "RENDER.h"

uint32_t	BlackGround_Color = 0xFFFFFFFF;
	

 /*DESCRIPTION
 *      ��ͼ��ʼ��
 *ARGUMENTS
 * 	NULL
 *RETURN
 *	0 	��ʼ���ɹ�
 *NOTES
 *    
 */
int RENDER_initial(void)
{
	// SDRAM��ʼ��
	SDRAM_Init();
	
	// SDRAM�Լ죬�ɹ���LED2���������Լ�ʧ�����Ϩ��
//	SDRAM_SelfCheck();
	
        // LCD��ʼ��
	LCD_Initial(LCD_LAYER_TWO);
	
	// LCD�Լ죬�����ᡢ�����Ƽ��������򽥱�
//	LCD_SelfCheck();
	
//	// �ַ���ʾ����
//	RENDER_DisplayString(100, 120, (uint8_t*)"SUCCESS!", 0x00FF00);
//	RENDER_DisplayString(100, 60, (uint8_t*)"XCP!", 0x00FF00);
	
	// ��������
	
	
	
        return 0;
}

 /*DESCRIPTION
 *      ����
 *ARGUMENTS
 * 	Color	���������ɫ
 *RETURN
 *	NULL
 *NOTES
 *    ������ɫֵ��ʵ������
 */
void RENDER_Clear(uint32_t Color)
{
	// ���������24bit��ɫ
	uint32_t	m_offset=0;
	
	// ��ȡ����������ɫ
	BlackGround_Color	= Color;
	
	for(m_offset=0; m_offset<BUFFER_OFFSET; m_offset++){
		if(m_offset%4==0)
			*((uint8_t*)CurrentFrameBuffer+m_offset)	= (Color&0xFF);
		else if(m_offset%4==1)
			*((uint8_t*)CurrentFrameBuffer+m_offset)	= ((Color>>8)&0xFF);
		else if(m_offset%4==2)
			*((uint8_t*)CurrentFrameBuffer+m_offset)	= ((Color>>16)&0xFF);
		else if(m_offset%4==3)
			*((uint8_t*)CurrentFrameBuffer+m_offset)	= ((Color>>24)&0xFF);
	}	
	
}

/*DESCRIPTION
 *      ������Ҫ����������
 *ARGUMENTS
 * 	Color	���������ɫ
 *	index	����ֵ
 * 	Xpos	��Ļ������ֵ
 *	Ypos	��Ļ������ֵ
 *RETURN
 *	NULL
 *NOTES
 *    ������ɫֵ��ʵ������
 */
void RENDER_Clear_Original(uint16_t index,uint32_t Xpos,uint32_t Ypos,uint32_t Color)
{
	// ���������24bit��ɫ
	uint32_t	w	= 0;
	uint32_t	h	= 0;
	uint32_t 	Xadress	= CurrentFrameBuffer+4*(Ypos*LCD_WIDTH+Xpos);	
	uint32_t	adress	= 0;
	// ��ȡ����������ɫ
	BlackGround_Color	= Color;
	// ��ȡ�����λ��
	
	//texture_pointer[index]
	for(h=0;h<textures[index].Texture_h;h++){
		for(w=0;w<textures[index].Texture_w;w++){
			adress			= Xadress+4*(h*LCD_WIDTH+w);
			*((uint8_t*)adress)	=Color&0xFF;
			*((uint8_t*)(adress+1))	=(Color>>8)&0xFF;
			*((uint8_t*)(adress+2))	=(Color>>16)&0xFF;
			*((uint8_t*)(adress+3))	=(Color>>24)&0xFF;			
		}
	}		
}

/*DESCRIPTION
 *      ��������
 *ARGUMENTS
 * 	index 	����ֵ
 *	w	�������ݿ��
 *	h	�������ݸ߶�
 * 	type	������������
 *RETURN
 *	0	�ɹ�������������
 *NOTES
 *    ����������������
 */
int RENDER_load_texture()
{
	uint32_t	base  = 0;
        uint32_t	size  = 0;
	uint8_t		index = 0;
	
	base	= TEXTURE_BASE;
	// ������Ϣд��
	for(index=0;index<texture_n;index++)
	{
		textures[index].Texture_h	= TEXTURE_HEIGHT(index);
		textures[index].Texture_w	= TEXTURE_WIDTH(index);		
		textures[index].Texture_type	= TEXTURE_TYPE(index);
		//��������ÿ�����ض�Ӧ���ֽ���
		if(textures[index].Texture_type==TEXTURE_TYPE_8BIT){
			textures[index].Texture_type =1;
		} else if(textures[index].Texture_type==TEXTURE_TYPE_16BIT){
			textures[index].Texture_type =2;
		} else if(textures[index].Texture_type==TEXTURE_TYPE_24BIT){
			textures[index].Texture_type =3;
		} else if(textures[index].Texture_type==TEXTURE_TYPE_32BIT){
			textures[index].Texture_type =4;
		} 
		size = textures[index].Texture_h*textures[index].Texture_w*textures[index].Texture_type;
		
		// ���SDRAM�ڵĵ�ַ
		if(index==0){
			textures[index].Texture_addr	= (uint8_t*)base;
		} else
			textures[index].Texture_addr	= textures[index-1].Texture_addr + textures[index-1].Texture_h*textures[index-1].Texture_w*textures[index-1].Texture_type;

		memcpy(textures[index].Texture_addr, texture_pointer[index], size);
		
	}
	return 0;
}     
        

/*DESCRIPTION
 *      �ַ���ʾ
 *ARGUMENTS
 * 	x		�ַ���ʾ��ʼx����
 *	y		�ַ���ʾ��ʼy����
 *	str		��Ҫ��ʾ�ַ���
 *RETURN
 *	0 		�ַ���ʾ�ɹ�
 *NOTES
 *    ��ʾ�ַ�16*24�������壬����ʾ�ɴ�ӡ�ַ����ӿո�ASCII��32����ʼ��~��ASCII��126��ֹ
 */
int RENDER_DisplayString(uint32_t x, uint32_t y, uint8_t *str, uint32_t Color)
{	
	while((x<LCD_WIDTH) && ((*str != 0) & (((x + DotMatrixFont16x24.Width) & 0xFFFF) >= DotMatrixFont16x24.Width))){
		// ��ʾ�ַ�����ʾ��
		RENDER_DrawChar(x, y, str, Color);
		x+=DotMatrixFont16x24.Width;
		str++;
	}
	
	return 0;
}	

/*DESCRIPTION
 *      �����ַ�
 *ARGUMENTS
 * 	Xpos		�ַ���ʾ��׼��x����		
 *	YPos		�ַ���ʾ��׼��y����
 *	Ascii		�ַ�Ascii��
 *	Color		��ʾ���ַ���ɫ
 *RETURN
 *	NULL
 *NOTES
 *    
 */
void RENDER_DrawChar(uint16_t Xpos, uint16_t Ypos, uint8_t* Ascii, uint32_t Color)
{
	uint32_t	index = 0;
	uint32_t	counter = 0;
	uint32_t  	Xaddress = 0;
	const uint16_t*	Text = 0;
	
	
	Text		= &DotMatrixFont16x24.FontData[(*Ascii -=32) * DotMatrixFont16x24.Height];
	Xaddress 	= (Ypos*LCD_WIDTH*4)+(Xpos*4);
	
	// ��ʾ�ַ���ָ������
	for(index=0; index<DotMatrixFont16x24.Height; index++){
		for(counter=0; counter<(DotMatrixFont16x24.Width*4); counter++){
			// ����ʾ����Ϊ����ɫ���ṩ�ĵ�������Ϊ����
			if(((Text[index] & (0x1 << (counter/4))) == 0x00)){
				if(counter%4==0)
					*((uint8_t*)CurrentFrameBuffer+Xaddress+counter)	= (BlackGround_Color&0xFF);
				if(counter%4==1)
					*((uint8_t*)CurrentFrameBuffer+Xaddress+counter)	= ((BlackGround_Color>>8)&0xFF);
				if(counter%4==2)
					*((uint8_t*)CurrentFrameBuffer+Xaddress+counter)	= ((BlackGround_Color>>16)&0xFF);
				if(counter%4==3)
					*((uint8_t*)CurrentFrameBuffer+Xaddress+counter)	= ((BlackGround_Color>>24)&0xFF);
			}else{
				if(counter%4==0)
					*((uint8_t*)CurrentFrameBuffer+counter+Xaddress)	= (Color&0xFF);
				if(counter%4==1)
					*((uint8_t*)CurrentFrameBuffer+counter+Xaddress)	= ((Color>>8)&0xFF);
				if(counter%4==2)
					*((uint8_t*)CurrentFrameBuffer+counter+Xaddress)	= ((Color>>16)&0xFF);
				if(counter%4==3)
					*((uint8_t*)CurrentFrameBuffer+counter+Xaddress)	= ((Color>>24)&0xFF);
			}
		}
		Xaddress+=(LCD_WIDTH*4);
	}
	
}


int RENDER_DisplayLine(uint32_t stx, uint32_t sty, uint32_t enx, uint32_t eny);         // ��ʾ��





/* 
 * DESCRIPTION
 * 	��ӵ���ͼ�б�
 * ARGUMENTS
 *	x		�����������Ļ����x����Ļ���½�Ϊԭ�㣩
 *	y	 	�����������Ļ����y����Ļ���½�Ϊԭ�㣩
 *	option		��ͼѡ��
 *	color		��ͼ��ɫ
 *	index		��������
 *	angle		��ת�Ƕ�	
 * RETURN
 *	0		��ӳɹ�
 * NOTES
 *	���ε��øú������б�����ͼ�б�
 */ 
// ��ͼ����
int RENDER_add_map(uint16_t x, uint16_t y, uint32_t option, uint32_t color, uint16_t index,  float angle)
{
	int	n;
	
	n	= 0;
	// �ж����һ����Ч����ͼ
	while(MAP_IS_VALID(map_list[n])){
		n++;
	}
	// �ж��Ƿ񳬳������Χ
	if(n>=MAP_LIST_MAX)
		return -1;
	
	map_list[n].x		= x;
	map_list[n].y		= y;
	map_list[n].option	= option;
	map_list[n].color	= color;
	map_list[n].index	= index;
	map_list[n].angle	= angle;
	
	return 0;
}	

/* 
 * DESCRIPTION
 * 	���ô˺�����ʼ��ͼ��
 * ARGUMENTS
 *
 * RETURN
 *	
 * NOTES
 *	
 */ 
void RENDER_draw(void)
{
	int	num;
	int 	i;
	num	= 0;
	// �ж����һ����Ч����ͼ
	while(MAP_IS_VALID(map_list[num])){
		num++;
	}
	// �ж��Ƿ񳬳������Χ
	if(num>=MAP_LIST_MAX)
		return;
	
	
	for(i=0;i<num;i++){		
		if(!MAP_IS_VALID(map_list[i]))
			continue;
		// �߽紦��
		if(map_list[i].x+textures[map_list[i].index].Texture_w>LCD_WIDTH||map_list[i].y+textures[map_list[i].index].Texture_h>LCD_HEIGHT){
			continue;		
		}
		
		//����ɫΪ��ɫʱ������ʾ��ǰͼƬ������Ϊ������ɫ��ʱ����ʾ����������ɫֵ
		if(map_list[i].color==0xFFFFFFFF)
			RENDER_PFC(map_list[i].x,map_list[i].y,map_list[i].index);
		else{
			RENDER_ShowColor(map_list[i].x,map_list[i].y,map_list[i].index,map_list[i].color);			
		}
	}
	//�ӳ�ʱ�䣬���㿴��ͼƬ���ƶ�Ч��
	TIMER_Delay_ms(400);
	for(i=0;i<num;i++){
		// �ж��Ǿ�̬���Ƕ�̬ͼƬ����̬ͼ��Ҫ����ǰ����
		if(MAP_IS_DYNAMIC(map_list[i])){
			RENDER_Clear_Original(map_list[i].index,map_list[i].x,map_list[i].y,0xFFFFFFFF);			
		}
		map_list[i].option	= 0x00;		
	}
	
}


/*DESCRIPTION
 *      DMA2D���ͼƬ
 *ARGUMENTS
 * 	Xpos		��Ļ������
 *	Ypos		��Ļ������
 *	Length		���س���
 *	Direction	����
 *	ColorARGB	��ɫֵ
 *RETURN 
 *NOTES
 *    
 */
void RENDER_Bleding_Image(uint16_t Xpos,uint16_t Ypos,uint8_t index,uint32_t Color)
{
	uint32_t Xadress	= 0;
	uint32_t size		= 0;
	uint8_t  alpha		= 0;
	uint32_t i		= 0;
	
	
	Xadress			= 4*(Ypos*LCD_WIDTH +Xpos) + DMA2D_SDRAM_ADR;
	size			=  textures[index].Texture_w* textures[index].Texture_h* 3;
	
	//д�����ݵ���ϵ�ַ��ȥ����ΪRGB888��ʽ����
	for(i=0;i<size;i+=3){
		*(uint8_t*)(BELEDING_BASE+i)	= (Color&0xFF);
		*(uint8_t*)(BELEDING_BASE+i+1)	= ((Color>>8)&0xFF);
		*(uint8_t*)(BELEDING_BASE+i+2)	= ((Color>>16)&0xFF);
	}
	// ���alphaֵ
	alpha			= (Color>>24)&0xFF;
	
	//DMA2Dģʽ �洢�����洢����ִ�л��
	m_DMA2D_config.DMA2D_Mode	= DMA2D_MODE_M2M_BLE;
	
	//�����ɫģʽ
	m_DMA2D_config.DMA2D_CMode	= DMA2D_CMODE_ARGB8888;
	
	//������ʾ����ɫ
	m_DMA2D_config.DMA2D_Alpha	= 0;
	m_DMA2D_config.DMA2D_Red	= 0;
	m_DMA2D_config.DMA2D_Green	= 0;
	m_DMA2D_config.DMA2D_Blue	= 0;
	
	//������������ݵ�ַ
	m_DMA2D_config.DMA2D_OMAdd	= Xadress;
	//������ƫ��
	m_DMA2D_config.DMA2D_OLineOffset = LCD_WIDTH-textures[index].Texture_w;
	//����ÿ��������������
	m_DMA2D_config.DMA2D_PixelPerLine = textures[index].Texture_w;
	m_DMA2D_config.DMA2D_NumberLine	= textures[index].Texture_h;
	
	// ������ؼĴ���
	DMA2D_Config(&m_DMA2D_config);
	
	//��ʼ��FG��BG�ṹ��	
	DMA2D_FG_StructInit(&m_DMA2D_FGconfig);
	DMA2D_BG_StructInit(&m_DMA2D_BGconfig);
	
	//FG=255,��ʾΪFGͼ��
	
	
	
	// ��ɫ���������ַ,�����ɫ���׵�ַ
	m_DMA2D_BGconfig.DMA2D_BGMA			= (uint32_t)BELEDING_BASE;
	// ������ɫģʽ
	m_DMA2D_BGconfig.DMA2D_BGCM			= DMA2D_CMODE_RGB888;
	// ͸����ģʽ
	m_DMA2D_BGconfig.DMA2D_BGPFC_ALPHA_Mode		= DMA2D_AM_1;
	// ͸����ֵ
	m_DMA2D_BGconfig.DMA2D_BGPFC_ALPHA_Value	= 100;	
	
	DMA2D_BGConfig(&m_DMA2D_BGconfig);
	
	// ��ɫ���������ַ
	m_DMA2D_FGconfig.DMA2D_FGMA			= (uint32_t)textures[index].Texture_addr;
	// ������ɫģʽ
	if(textures[index].Texture_type==1){
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_L8;
		// ���ұ��ַ
		m_DMA2D_FGconfig.DMA2D_FGCMAR	= (uint32_t)DMA2D_CLUT_ADRESS;
		// ��ɫ���ұ���ɫģʽ
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_CM = DMA2D_CCMODE_ARGB8888;
		
		// ��ɫ���ұ��С
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_Size =255;		
	} else if(textures[index].Texture_type==2)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB565;
	else if(textures[index].Texture_type==3)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB888;
	else if(textures[index].Texture_type==4)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_ARGB8888;
	
	// ͸����ģʽ
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Mode		= DMA2D_AM_1;
	// ͸����ֵ
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Value	= 255*(alpha-m_DMA2D_BGconfig.DMA2D_BGPFC_ALPHA_Value)/(255-m_DMA2D_BGconfig.DMA2D_BGPFC_ALPHA_Value);	
	
	DMA2D_FGConfig(&m_DMA2D_FGconfig);
	DMA2D->FGPFCCR |= 1<<5;
	while((DMA2D->ISR&DMA2D_ISR_CTCIF)!=0x10){
	};
	
	
	DMA2D_StartTransfer();	
	
}
 /*DESCRIPTION
 *      DMA2D��ֱ��
 *ARGUMENTS
 * 	Xpos		��Ļ������
 *	Ypos		��Ļ������
 *	ColorARGB	��ɫֵ
 *RETURN 
 *NOTES
 *    
 */
void RENDER_ShowColor(uint16_t Xpos, uint16_t Ypos,uint16_t index,uint32_t ColorARGB)
{
	uint32_t Xaddress =  0;
	Xaddress = DMA2D_SDRAM_ADR + 4*(LCD_WIDTH*Ypos + Xpos);
	
	//DMA2Dģʽ �Ĵ������洢��
	m_DMA2D_config.DMA2D_Mode	= DMA2D_MODE_R2M;
	
	//�����ɫģʽ
	m_DMA2D_config.DMA2D_CMode	= DMA2D_CMODE_ARGB8888;
	
	//������ʾ����ɫ
	m_DMA2D_config.DMA2D_Alpha	= (ColorARGB&0xFF000000)>>24;
	m_DMA2D_config.DMA2D_Red	= (ColorARGB&0x00FF0000)>>16;
	m_DMA2D_config.DMA2D_Green	= (ColorARGB&0x0000FF00)>>8;
	m_DMA2D_config.DMA2D_Blue	= (ColorARGB&0x000000FF);
	
	//������������ݵ�ַ
	m_DMA2D_config.DMA2D_OMAdd	= Xaddress;
	

	//������ƫ��
	m_DMA2D_config.DMA2D_OLineOffset = LCD_WIDTH-textures[index].Texture_w;
	//����ÿ��������������
	m_DMA2D_config.DMA2D_PixelPerLine = textures[index].Texture_w;
	m_DMA2D_config.DMA2D_NumberLine	= textures[index].Texture_h;

	DMA2D_Config(&m_DMA2D_config);
	// ���ݴ���
	DMA2D_StartTransfer();	
	while((DMA2D->ISR&0x02)!=0x02){
			
	}
	
	DMA2D->IFCR |= 0x02;
	
	while((DMA2D->ISR&0x02)!=0x00){	
						
	}
	
}
 /*DESCRIPTION
 *      DMA2D��ֱ��
 *ARGUMENTS
 * 	Xpos		��Ļ������
 *	Ypos		��Ļ������
 *	Length		���س���
 *	Direction	����
 *	ColorARGB	��ɫֵ
 *RETURN 
 *NOTES
 *    
 */
void RENDER_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction,uint32_t ColorARGB)
{
	uint32_t Xaddress =  0;
	Xaddress = DMA2D_SDRAM_ADR + 4*(320*Ypos + Xpos);
	
	//DMA2Dģʽ �Ĵ������洢��
	m_DMA2D_config.DMA2D_Mode	= DMA2D_MODE_R2M;
	
	//�����ɫģʽ
	m_DMA2D_config.DMA2D_CMode	= DMA2D_CMODE_ARGB8888;
	
	//������ʾ����ɫ
	m_DMA2D_config.DMA2D_Alpha	= (ColorARGB&0xFF000000)>>24;
	m_DMA2D_config.DMA2D_Red	= (ColorARGB&0x00FF0000)>>16;
	m_DMA2D_config.DMA2D_Green	= (ColorARGB&0x0000FF00)>>8;
	m_DMA2D_config.DMA2D_Blue	= (ColorARGB&0x000000FF);
	
	//������������ݵ�ַ
	m_DMA2D_config.DMA2D_OMAdd	= Xaddress;
	
	// ��ƫ�ƣ�ÿ��������������
	if(Direction==LCD_DIR_HORIZONTAL){
		m_DMA2D_config.DMA2D_OLineOffset	= 0x00;
		m_DMA2D_config.DMA2D_PixelPerLine	= Length;
		m_DMA2D_config.DMA2D_NumberLine		= 1;
	} else if(Direction==LCD_DIR_VERTICAL){
		m_DMA2D_config.DMA2D_OLineOffset	= LCD_WIDTH-1;
		m_DMA2D_config.DMA2D_PixelPerLine	= 1;
		m_DMA2D_config.DMA2D_NumberLine		= Length;
	} else{
		m_DMA2D_config.DMA2D_OLineOffset	= LCD_WIDTH-2;
		m_DMA2D_config.DMA2D_PixelPerLine	= 1;
		m_DMA2D_config.DMA2D_NumberLine		= Length;
	}
		
	DMA2D_Config(&m_DMA2D_config);
	// ���ݴ���
	DMA2D_StartTransfer();	
}

 /*DESCRIPTION
 *      DMA2D
 *ARGUMENTS
 * 	Xpos		��Ļ������
 *	Ypos		��Ļ������
 *	Length		���س���
 *	Direction	����
 *	ColorARGB	��ɫֵ
 *RETURN 
 *NOTES
 *    
 */

void RENDER_PFC(uint16_t Xpos, uint16_t Ypos,uint32_t index)
{
	
	uint32_t Xadress	= 0;
	Xadress			= 4*(Ypos*LCD_WIDTH +Xpos) + DMA2D_SDRAM_ADR;
	
	m_DMA2D_config.DMA2D_Mode	= DMA2D_MODE_M2M_PFC;
	
	//�����ɫģʽ
	m_DMA2D_config.DMA2D_CMode	= DMA2D_CMODE_ARGB8888;
	
	//������ʾ����ɫ
	m_DMA2D_config.DMA2D_Alpha	= 0;
	m_DMA2D_config.DMA2D_Red	= 0;
	m_DMA2D_config.DMA2D_Green	= 0;
	m_DMA2D_config.DMA2D_Blue	= 0;
	
	//������������ݵ�ַ
	m_DMA2D_config.DMA2D_OMAdd	= Xadress;
	//������ƫ��
	m_DMA2D_config.DMA2D_OLineOffset = LCD_WIDTH-textures[index].Texture_w;
	//����ÿ��������������
	m_DMA2D_config.DMA2D_PixelPerLine = textures[index].Texture_w;
	m_DMA2D_config.DMA2D_NumberLine	= textures[index].Texture_h;
	
	// ������ؼĴ���
	DMA2D_Config(&m_DMA2D_config);
	
	//��ʼ��FG��BG�ṹ��
	DMA2D_FG_StructInit(&m_DMA2D_FGconfig);
	DMA2D_BG_StructInit(&m_DMA2D_BGconfig);
	
	// ��ɫ���������ַ
	m_DMA2D_FGconfig.DMA2D_FGMA			= (uint32_t)textures[index].Texture_addr;
	// ������ɫģʽ
	if(textures[index].Texture_type==1){
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_L8;
		// ���ұ��ַ
		m_DMA2D_FGconfig.DMA2D_FGCMAR	= (uint32_t)DMA2D_CLUT_ADRESS;
		// ��ɫ���ұ���ɫģʽ
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_CM = DMA2D_CCMODE_ARGB8888;		
		// ��ɫ���ұ��С
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_Size =255;		
	}
	else if(textures[index].Texture_type==2)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB565;
	else if(textures[index].Texture_type==3)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB888;
	else if(textures[index].Texture_type==4)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_ARGB8888;
	
	DMA2D_FGConfig(&m_DMA2D_FGconfig);
	// ͸����ģʽ
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Mode		= DMA2D_AM_1;
	// ͸����ֵ
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Value	= 255;	
	
	DMA2D_FGConfig(&m_DMA2D_FGconfig);
	
	DMA2D->FGPFCCR |= 1<<5;	
	while((DMA2D->ISR&0x10)!=0x10){
	}
	DMA2D_StartTransfer();	

	while((DMA2D->ISR&0x12)!=0x12){
			
	}
	
	DMA2D->IFCR |= 0x12;
	
	while((DMA2D->ISR&0x12)!=0x00){	
						
	}
	
}
 /*DESCRIPTION
 *      DMA2D
 *ARGUMENTS
 * 	Xpos		��Ļ������
 *	Ypos		��Ļ������
 *	index		��������ֵ
 *RETURN 
 *NOTES
 *    
 */
void RENDER_PFC_CLUT(uint16_t Xpos, uint16_t Ypos,uint32_t index)
{
	uint32_t Xadress	= 0;
	Xadress			=4*(Ypos*LCD_WIDTH +Xpos) + DMA2D_SDRAM_ADR;
	//DMA2Dģʽ �Ĵ������洢��
	m_DMA2D_config.DMA2D_Mode	= DMA2D_MODE_M2M_PFC;
	
	//�����ɫģʽ
	m_DMA2D_config.DMA2D_CMode	= DMA2D_CMODE_ARGB8888;
	
	//������ʾ����ɫ
	m_DMA2D_config.DMA2D_Alpha	= 0;
	m_DMA2D_config.DMA2D_Red	= 0;
	m_DMA2D_config.DMA2D_Green	= 0;
	m_DMA2D_config.DMA2D_Blue	= 0;
	
	//������������ݵ�ַ
	m_DMA2D_config.DMA2D_OMAdd	= Xadress;
	//������ƫ��
	m_DMA2D_config.DMA2D_OLineOffset = LCD_WIDTH-textures[index].Texture_w;
	//����ÿ��������������
	m_DMA2D_config.DMA2D_PixelPerLine = textures[index].Texture_w;
	m_DMA2D_config.DMA2D_NumberLine	= textures[index].Texture_h;
	
	// ������ؼĴ���
	DMA2D_Config(&m_DMA2D_config);
	
	//��ʼ��FG��BG�ṹ��	
	DMA2D_FG_StructInit(&m_DMA2D_FGconfig);
	DMA2D_BG_StructInit(&m_DMA2D_BGconfig);
	
	// ��ɫ���������ַ
	m_DMA2D_FGconfig.DMA2D_FGMA			= (uint32_t)textures[index].Texture_addr;
	// ������ɫģʽ
	if(textures[index].Texture_type==1){
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_L8;
		// ���ұ��ַ
		m_DMA2D_FGconfig.DMA2D_FGCMAR	= (uint32_t)DMA2D_CLUT_ADRESS;
		// ��ɫ���ұ���ɫģʽ
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_CM = DMA2D_CCMODE_ARGB8888;
		
		// ��ɫ���ұ��С
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_Size =255;		
	} else if(textures[index].Texture_type==2)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB565;
	else if(textures[index].Texture_type==3)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB888;
	else if(textures[index].Texture_type==4)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_ARGB8888;
	
	// ͸����ģʽ
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Mode		= DMA2D_AM_1;
	// ͸����ֵ
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Value	= 255;	
	
	DMA2D_FGConfig(&m_DMA2D_FGconfig);
	DMA2D->FGPFCCR |= 1<<5;
	while((DMA2D->ISR&DMA2D_ISR_CTCIF)!=0x10){
	};
	DMA2D_StartTransfer();	
	
	DMA2D->CR |= (uint32_t)0x0;	
}

