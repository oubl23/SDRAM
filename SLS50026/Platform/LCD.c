/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: LCD.c,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.2 $
 * Date		$Date: 2015/10/30 06:34:38 $
 * Description	
	PT1003  LCD����
 ******************************************************************************
 */
 
#include "LCD.h"

/* Default LCD configuration with LCD Layer 1 */
uint32_t CurrentFrameBuffer = GRAM_BASE_LAYER1;
uint32_t CurrentLayer = LCD_BACKGROUND_LAYER;
 
LCD_config     m_LCD_config;                   // LCD���ýṹ�����
 
 /*DESCRIPTION
 *      LCDҺ��������
 *ARGUMENTS
 * 	LCD_Layers      Ҫ��ʼ���Ĳ㣬0�������㣻1����1��2����2��3�����в�
 *RETURN
 *	0 	�������óɹ�
 *NOTES
 *    
 */
int LCD_Initial(uint8_t   LCD_Layers)
{
        // ������ʼ��
        uint32_t       m_LCD_HBP               = 0;    // �ۼ���ǰ��
        uint32_t       m_LCD_VBP               = 0;    // �ۼӳ�ǰ��
        uint32_t       m_LCD_Width             = 0;    // �ۼӿ��
        uint32_t       m_LCD_Height            = 0;    // �ۼӸ߶�
        uint32_t       m_LCD_Total_Width       = 0;    // �ܹ����
        uint32_t       m_LCD_Total_Height      = 0;    // �ܹ��߶�


        m_LCD_config.LCD_HorizontalSync_Width  = 0;    // ��ͬ�����
        m_LCD_config.LCD_VerticalSync_Height   = 0;    // ��ͬ�����
        m_LCD_config.LCD_HBP                   = 68;   // �к���
        m_LCD_config.LCD_VBP                   = 18;   // ������
        m_LCD_config.LCD_HFP                   = 20;   // ��ǰ��
        m_LCD_config.LCD_VFP                   = 4;    // ��ǰ��
        m_LCD_config.LCD_Width                 = LCD_WIDTH;  	// ��Ч���ؿ�
        m_LCD_config.LCD_Height                = LCD_HEIGHT;  	// ��Ч���ظ�

        m_LCD_HBP      = (m_LCD_config.LCD_HorizontalSync_Width-1)+m_LCD_config.LCD_HBP;
        m_LCD_VBP      = (m_LCD_config.LCD_VerticalSync_Height-1)+m_LCD_config.LCD_VBP;

        m_LCD_Width    = m_LCD_HBP+m_LCD_config.LCD_Width;
        m_LCD_Height   = m_LCD_VBP+m_LCD_config.LCD_Height;

        m_LCD_Total_Width      = m_LCD_Width+ m_LCD_config.LCD_HFP;
        m_LCD_Total_Height     = m_LCD_Height+m_LCD_config.LCD_VFP;

        // ����ͬ������ֵ
        LTDC->SSCR &= ~(LTDC_SSCR_VSH | LTDC_SSCR_HSW);
        LTDC->SSCR |= (( m_LCD_config.LCD_HorizontalSync_Width-1)<< 16)|\
        (m_LCD_config.LCD_VerticalSync_Height-1);
        
	// ����HBP��VBP
        LTDC->BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
        LTDC->BPCR |= ((m_LCD_HBP << 16) | m_LCD_VBP);

        // ����ͼ����ʾ����
        LTDC->AWCR &= ~(LTDC_AWCR_AAH | LTDC_AWCR_AAW);
        LTDC->AWCR |= ((m_LCD_Width << 16) | m_LCD_Height);

        // �ܳ�������
        LTDC->TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
        LTDC->TWCR |= ((m_LCD_Total_Width << 16) | m_LCD_Total_Height);

        // LTDC�������ã���ʼʱ������Ϊ�ͣ��ο�LCD datasheet
        LTDC->GCR &= ~(GCR_MASK);
        LTDC->GCR |=  0x30000000;   

        // ���ñ���RGB��ɫ(��ɫ)
        LTDC->BCCR &= ~(LTDC_BCCR_BCBLUE | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCRED);
        LTDC->BCCR = 0x3A000000;
        
        // �ݴ��������ʼ����
	switch(LCD_Layers){
		// ������
		case LCD_BACKGROUND_LAYER:
			break;
		// ��1
		case LCD_LAYER_ONE:
			// ��¼��ǰ��
			CurrentLayer		= LCD_LAYER_ONE;
			// ��ʼ����1
			LCD_LayerInit(LTDC_Layer1);
			// ���õ�ǰ�ɲ����Ļ����ַ
			CurrentFrameBuffer      = GRAM_BASE_LAYER1;
			break;
		// ��2
		case LCD_LAYER_TWO:
			// ��¼��ǰ��
			CurrentLayer		= LCD_LAYER_TWO;
			// ��ʼ����2		
			LCD_LayerInit(LTDC_Layer2);
			// ���õ�ǰ�ɲ����Ļ����ַ
			CurrentFrameBuffer      = GRAM_BASE_LAYER1;
			break;
		// ���в�
		case LCD_LAYER_ALL:
			// ��¼��ǰ��
			CurrentLayer		= LCD_LAYER_ALL;
			// ��ʼ����1���2
			LCD_LayerInit(LTDC_Layer1);
			LCD_LayerInit(LTDC_Layer2);
			// ��¼��ǰ�㣬���õ�ǰ�ɲ����Ļ����ַ
			CurrentFrameBuffer      = GRAM_BASE_LAYER2;
			break;
		default:
			;
	}
        	
        // ʹ��LTDC
        LTDC->GCR |= (uint32_t)LTDC_GCR_LTDCEN;
	
	// �������ؼĴ����� ��������
	LCD_ReloadReg(LTDC_SRCR_IMR);
				
        
        return 0;
}

/*DESCRIPTION
 *      ���ݴ��������LCD���ʼ��
 *ARGUMENTS
 * 	LTDC_Layerx           ����Ĳ�ṹ�����
 *RETURN
 *	0 	�������óɹ�
 *      1       �㴫���������
 *NOTES
 *    LCD��layer������
 */
int LCD_LayerInit(LTDC_Layer_TypeDef* LTDC_Layerx)
{
        // ÿ��������ռ�ֽ�
        uint8_t Pixel_N = 0;    
        LCD_Layer_config        m_LCD_Layer_config;
        // Horizontal Start
        m_LCD_Layer_config.LCD_HorizontalStart  = m_LCD_config.LCD_HorizontalSync_Width+m_LCD_config.LCD_HBP;
        // Horizontal Stop
        m_LCD_Layer_config.LCD_HorizontalStop   = m_LCD_Layer_config.LCD_HorizontalStart+m_LCD_config.LCD_Width-1;
        // Vertical start
        m_LCD_Layer_config.LCD_VerticalStart    = m_LCD_config.LCD_HorizontalSync_Width+m_LCD_config.LCD_VBP;
        // Vertical stop
        m_LCD_Layer_config.LCD_VerticalStop     = m_LCD_Layer_config.LCD_VerticalStart+ m_LCD_config.LCD_Height-1;
        // Pixel Format
        m_LCD_Layer_config.LCD_PixelFormat      = LTDC_Pixelformat_ARGB8888;       // RGB888
        // Alpha constant
        m_LCD_Layer_config.LCD_ConstantAlpha    = 255; 

        
        if(m_LCD_Layer_config.LCD_PixelFormat == LTDC_Pixelformat_RGB565){
                Pixel_N = 2;
        }else if(m_LCD_Layer_config.LCD_PixelFormat == LTDC_Pixelformat_ARGB8888){
                Pixel_N = 4;
        }else if(m_LCD_Layer_config.LCD_PixelFormat == LTDC_Pixelformat_RGB888){
                Pixel_N = 3;
        }else
                // ������ɫ��ʽ
                ; 
        
        
        // ����ʼ����ֹλ��
        LTDC_Layerx->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
        LTDC_Layerx->WHPCR = (m_LCD_Layer_config.LCD_HorizontalStart | (m_LCD_Layer_config.LCD_HorizontalStop<<16));
        
        // ����ʼ����ֹλ��
        LTDC_Layerx->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
        LTDC_Layerx->WVPCR  = (m_LCD_Layer_config.LCD_VerticalStart | (m_LCD_Layer_config.LCD_VerticalStop<<16));
        
        // ���ظ�ʽ
        LTDC_Layerx->PFCR &= ~(LTDC_LxPFCR_PF);
        LTDC_Layerx->PFCR = (m_LCD_Layer_config.LCD_PixelFormat);
        
        // Ĭ����ɫֵ����ɫ��
        LTDC_Layerx->DCCR &=  ~(LTDC_LxDCCR_DCBLUE | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCALPHA);
        LTDC_Layerx->DCCR |= 0x00000000;
        
        // alphaֵ
        LTDC_Layerx->CACR &= ~(LTDC_LxCACR_CONSTA);
        LTDC_Layerx->CACR = (m_LCD_Layer_config.LCD_ConstantAlpha);
        
        
        // ��������
        if(LTDC_Layerx==LTDC_Layer1){
                // �������
                LTDC_Layerx->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
                LTDC_Layerx->BFCR = (LTDC_BlendingFactor1_CA | LTDC_BlendingFactor2_CA);
                
                // ֡������ʼ��ַ���õ�ַ������SDRAM��
                LTDC_Layerx->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
                LTDC_Layerx->CFBAR = GRAM_BASE_LAYER1;
        }else if(LTDC_Layerx==LTDC_Layer2){
                // �������
                LTDC_Layerx->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
                LTDC_Layerx->BFCR = (LTDC_BlendingFactor1_PAxCA | LTDC_BlendingFactor2_PAxCA);
                
                // ֡������ʼ��ַ���õ�ַ������SDRAM��
                LTDC_Layerx->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
                LTDC_Layerx->CFBAR = ((CurrentLayer==LCD_LAYER_ALL)?GRAM_BASE_LAYER2:GRAM_BASE_LAYER1);
        }else
                return 1;
        
	// ֡������
        LTDC_Layerx->CFBLR  &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
        LTDC_Layerx->CFBLR = (((m_LCD_config.LCD_Width*Pixel_N)+3) | ((m_LCD_config.LCD_Width*Pixel_N)<<16));
	
	// ֡������
	LTDC_Layerx->CFBLNR  &= ~(LTDC_LxCFBLNR_CFBLNBR);
	LTDC_Layerx->CFBLNR  = m_LCD_config.LCD_Height; 
	
	
        // �������ؼĴ����� ��������
	LCD_ReloadReg(LTDC_SRCR_IMR);
        
        // ��ʹ��
        LTDC_Layerx->CR |= (uint32_t)LTDC_LxCR_LEN;
        
        // �������ؼĴ����� ��������
	LCD_ReloadReg(LTDC_SRCR_IMR);
        
        // ���������
        LTDC->GCR |= (uint32_t)LTDC_GCR_DTEN;
        
        
        return 0;
}

/*DESCRIPTION
 *      ���ݴ��������LCD������������
 *ARGUMENTS
 * 	LCD_Reload	�������ͣ�LTDC_SRCR_IMR���������أ�LTDC_SRCR_VBR������������
 *RETURN
 *	NULL
 *NOTES
 *    
 */
void LCD_ReloadReg(uint32_t LCD_Reload)
{
	// ������������
	LTDC->SRCR	= (uint32_t)LCD_Reload;
	
}

/*DESCRIPTION
 *      LCD��Ļ�Լ�
 *ARGUMENTS
 * 	NULL
 *RETURN
 *	NULL
 *NOTES
 *    ʵ�ֺᡢ�����Ƽ������������ʾ�Լ�
 */
void LCD_SelfCheck(void)
{
	uint32_t	add_offset = 0;
	uint32_t	index_x	= 0;
	uint32_t	index_y	= 0;

#define COLOR_DISPLAY_HORIZONTAL_AREA(ADD_OFFSET, COLOR)				\
	if(ADD_OFFSET%3==0)								\
		*((uint8_t*)CurrentFrameBuffer+ADD_OFFSET)	= (COLOR&0xFF); 	\
	else if(ADD_OFFSET%3==1)							\
		*((uint8_t*)CurrentFrameBuffer+ADD_OFFSET)	= ((COLOR>>8)&0xFF);	\
	else if(ADD_OFFSET%3==2)							\
		*((uint8_t*)CurrentFrameBuffer+ADD_OFFSET)	= ((COLOR>>16)&0xFF);	
	
	// ��������
	for(add_offset=0; add_offset<(LCD_WIDTH*LCD_HEIGHT*3); add_offset++){
		// ��ʾR��G��B��ɫ����
		if(add_offset<(LCD_WIDTH*3*(LCD_HEIGHT/3))){
			// ��
			COLOR_DISPLAY_HORIZONTAL_AREA(add_offset, 0xFF0000);
		}else if((add_offset>=(LCD_WIDTH*3*(LCD_HEIGHT/3))) && (add_offset<(LCD_WIDTH*3*(LCD_HEIGHT/3)*2))){
			// ��
			COLOR_DISPLAY_HORIZONTAL_AREA(add_offset, 0x00FF00);
		}else{
			// ��
			COLOR_DISPLAY_HORIZONTAL_AREA(add_offset, 0x0000FF);
		}
	}
	
	// ��ʱ2s
	TIMER_Delay_ms(2000);

#define COLOR_DISPLAY_VERTICAL_AREA(ADD_OFFSET, COLOR)							\
	if(ADD_OFFSET%3==0)										\
		*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+ADD_OFFSET) = (COLOR&0xFF);	\
	else if(ADD_OFFSET%3==1)									\
		*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+ADD_OFFSET) = ((COLOR>>8)&0xFF);	\
	else if(ADD_OFFSET%3==2)									\
		*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+ADD_OFFSET) = ((COLOR>>16)&0xFF);
	
	// ��������
	for(index_y=0; index_y<LCD_HEIGHT; index_y++){
		for(index_x=0; index_x<LCD_WIDTH*3; index_x++){
			if(index_x<((LCD_WIDTH*3)/4)){
				// ��
				COLOR_DISPLAY_VERTICAL_AREA(index_x, 0xFF0000);
			}else if((index_x>=((LCD_WIDTH*3)/4)) && (index_x<(((LCD_WIDTH*3)/4)*2))){
				// ��
				COLOR_DISPLAY_VERTICAL_AREA(index_x, 0x00FF00);
			}else if((index_x>=(((LCD_WIDTH*3)/4)*2)) && (index_x<(((LCD_WIDTH*3)/4)*3))){
				// ��
				COLOR_DISPLAY_VERTICAL_AREA(index_x, 0x0000FF);
			}else{
				// ��
				COLOR_DISPLAY_VERTICAL_AREA(index_x, 0xFF0000);
			}
		}
		 
	}
	
	// ��ʱ2s
	TIMER_Delay_ms(2000);

	
	// ���򽥱�
	for(index_y=0; index_y<LCD_HEIGHT; index_y++){
		if(index_y<(LCD_HEIGHT/3)){
			// R����
			for(index_x=0; index_x<LCD_WIDTH*3; index_x++){
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_WIDTH-(index_x/3))*255)/LCD_WIDTH)&0xFF;
			}
		}else if((index_y>=(LCD_HEIGHT/3)) && (index_y<((LCD_HEIGHT/3)*2))){
			// G����
			for(index_x=0; index_x<LCD_WIDTH*3; index_x++){
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_WIDTH-(index_x/3))*255)/LCD_WIDTH)&0xFF;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
			}
		}else{
			// G����
			for(index_x=0; index_x<LCD_WIDTH*3; index_x++){
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_WIDTH-(index_x/3))*255)/LCD_WIDTH)&0xFF;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
			}
		}
		
	}
	
	// ��ʱ2s
	TIMER_Delay_ms(2000);
	
	// ���򽥱�
	for(index_y=0; index_y<LCD_HEIGHT; index_y++){
		for(index_x=0; index_x<LCD_WIDTH*3; index_x++){
			if(index_x<((LCD_WIDTH*3)/4)){
				// ��
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_HEIGHT-index_y)*255)/LCD_HEIGHT)&0xFF;
			}else if((index_x>=((LCD_WIDTH*3)/4)) && (index_x<(((LCD_WIDTH*3)/4)*2))){
				// ��
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_HEIGHT-index_y)*255)/LCD_HEIGHT)&0xFF;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
			}else if((index_x>=(((LCD_WIDTH*3)/4)*2)) && (index_x<(((LCD_WIDTH*3)/4)*3))){
				// ��
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_HEIGHT-index_y)*255)/LCD_HEIGHT)&0xFF;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
			}else{
				// ��
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_HEIGHT-index_y)*255)/LCD_HEIGHT)&0xFF;
			}
		}
	}
	// ��ʱ2s
	TIMER_Delay_ms(2000);
	
}

