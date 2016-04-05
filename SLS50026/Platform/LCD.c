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
	PT1003  LCD驱动
 ******************************************************************************
 */
 
#include "LCD.h"

/* Default LCD configuration with LCD Layer 1 */
uint32_t CurrentFrameBuffer = GRAM_BASE_LAYER1;
uint32_t CurrentLayer = LCD_BACKGROUND_LAYER;
 
LCD_config     m_LCD_config;                   // LCD配置结构体参数
 
 /*DESCRIPTION
 *      LCD液晶屏配置
 *ARGUMENTS
 * 	LCD_Layers      要初始化的层，0：背景层；1：层1；2：层2；3：所有层
 *RETURN
 *	0 	函数调用成功
 *NOTES
 *    
 */
int LCD_Initial(uint8_t   LCD_Layers)
{
        // 参数初始化
        uint32_t       m_LCD_HBP               = 0;    // 累加行前沿
        uint32_t       m_LCD_VBP               = 0;    // 累加场前沿
        uint32_t       m_LCD_Width             = 0;    // 累加宽度
        uint32_t       m_LCD_Height            = 0;    // 累加高度
        uint32_t       m_LCD_Total_Width       = 0;    // 总共宽度
        uint32_t       m_LCD_Total_Height      = 0;    // 总共高度


        m_LCD_config.LCD_HorizontalSync_Width  = 0;    // 行同步宽度
        m_LCD_config.LCD_VerticalSync_Height   = 0;    // 场同步宽度
        m_LCD_config.LCD_HBP                   = 68;   // 行后沿
        m_LCD_config.LCD_VBP                   = 18;   // 场后沿
        m_LCD_config.LCD_HFP                   = 20;   // 行前沿
        m_LCD_config.LCD_VFP                   = 4;    // 场前沿
        m_LCD_config.LCD_Width                 = LCD_WIDTH;  	// 有效像素宽
        m_LCD_config.LCD_Height                = LCD_HEIGHT;  	// 有效像素高

        m_LCD_HBP      = (m_LCD_config.LCD_HorizontalSync_Width-1)+m_LCD_config.LCD_HBP;
        m_LCD_VBP      = (m_LCD_config.LCD_VerticalSync_Height-1)+m_LCD_config.LCD_VBP;

        m_LCD_Width    = m_LCD_HBP+m_LCD_config.LCD_Width;
        m_LCD_Height   = m_LCD_VBP+m_LCD_config.LCD_Height;

        m_LCD_Total_Width      = m_LCD_Width+ m_LCD_config.LCD_HFP;
        m_LCD_Total_Height     = m_LCD_Height+m_LCD_config.LCD_VFP;

        // 配置同步脉冲值
        LTDC->SSCR &= ~(LTDC_SSCR_VSH | LTDC_SSCR_HSW);
        LTDC->SSCR |= (( m_LCD_config.LCD_HorizontalSync_Width-1)<< 16)|\
        (m_LCD_config.LCD_VerticalSync_Height-1);
        
	// 配置HBP和VBP
        LTDC->BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
        LTDC->BPCR |= ((m_LCD_HBP << 16) | m_LCD_VBP);

        // 配置图像显示区域
        LTDC->AWCR &= ~(LTDC_AWCR_AAH | LTDC_AWCR_AAW);
        LTDC->AWCR |= ((m_LCD_Width << 16) | m_LCD_Height);

        // 总长宽配置
        LTDC->TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
        LTDC->TWCR |= ((m_LCD_Total_Width << 16) | m_LCD_Total_Height);

        // LTDC极性配置（初始时都配置为低）参考LCD datasheet
        LTDC->GCR &= ~(GCR_MASK);
        LTDC->GCR |=  0x30000000;   

        // 设置背景RGB颜色(黑色)
        LTDC->BCCR &= ~(LTDC_BCCR_BCBLUE | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCRED);
        LTDC->BCCR = 0x3A000000;
        
        // 据传入参数初始化层
	switch(LCD_Layers){
		// 背景层
		case LCD_BACKGROUND_LAYER:
			break;
		// 层1
		case LCD_LAYER_ONE:
			// 记录当前层
			CurrentLayer		= LCD_LAYER_ONE;
			// 初始化层1
			LCD_LayerInit(LTDC_Layer1);
			// 设置当前可操作的缓冲地址
			CurrentFrameBuffer      = GRAM_BASE_LAYER1;
			break;
		// 层2
		case LCD_LAYER_TWO:
			// 记录当前层
			CurrentLayer		= LCD_LAYER_TWO;
			// 初始化层2		
			LCD_LayerInit(LTDC_Layer2);
			// 设置当前可操作的缓冲地址
			CurrentFrameBuffer      = GRAM_BASE_LAYER1;
			break;
		// 所有层
		case LCD_LAYER_ALL:
			// 记录当前层
			CurrentLayer		= LCD_LAYER_ALL;
			// 初始化层1与层2
			LCD_LayerInit(LTDC_Layer1);
			LCD_LayerInit(LTDC_Layer2);
			// 记录当前层，设置当前可操作的缓冲地址
			CurrentFrameBuffer      = GRAM_BASE_LAYER2;
			break;
		default:
			;
	}
        	
        // 使能LTDC
        LTDC->GCR |= (uint32_t)LTDC_GCR_LTDCEN;
	
	// 设置重载寄存器， 立即重载
	LCD_ReloadReg(LTDC_SRCR_IMR);
				
        
        return 0;
}

/*DESCRIPTION
 *      根据传入参数对LCD层初始化
 *ARGUMENTS
 * 	LTDC_Layerx           传入的层结构体参数
 *RETURN
 *	0 	函数调用成功
 *      1       层传入参数错误
 *NOTES
 *    LCD的layer共两层
 */
int LCD_LayerInit(LTDC_Layer_TypeDef* LTDC_Layerx)
{
        // 每个像素所占字节
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
                // 其它颜色格式
                ; 
        
        
        // 行起始、终止位置
        LTDC_Layerx->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
        LTDC_Layerx->WHPCR = (m_LCD_Layer_config.LCD_HorizontalStart | (m_LCD_Layer_config.LCD_HorizontalStop<<16));
        
        // 场起始、中止位置
        LTDC_Layerx->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
        LTDC_Layerx->WVPCR  = (m_LCD_Layer_config.LCD_VerticalStart | (m_LCD_Layer_config.LCD_VerticalStop<<16));
        
        // 像素格式
        LTDC_Layerx->PFCR &= ~(LTDC_LxPFCR_PF);
        LTDC_Layerx->PFCR = (m_LCD_Layer_config.LCD_PixelFormat);
        
        // 默认颜色值（黑色）
        LTDC_Layerx->DCCR &=  ~(LTDC_LxDCCR_DCBLUE | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCALPHA);
        LTDC_Layerx->DCCR |= 0x00000000;
        
        // alpha值
        LTDC_Layerx->CACR &= ~(LTDC_LxCACR_CONSTA);
        LTDC_Layerx->CACR = (m_LCD_Layer_config.LCD_ConstantAlpha);
        
        
        // 其它配置
        if(LTDC_Layerx==LTDC_Layer1){
                // 混合因子
                LTDC_Layerx->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
                LTDC_Layerx->BFCR = (LTDC_BlendingFactor1_CA | LTDC_BlendingFactor2_CA);
                
                // 帧缓存起始地址，该地址定义在SDRAM上
                LTDC_Layerx->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
                LTDC_Layerx->CFBAR = GRAM_BASE_LAYER1;
        }else if(LTDC_Layerx==LTDC_Layer2){
                // 混合因子
                LTDC_Layerx->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
                LTDC_Layerx->BFCR = (LTDC_BlendingFactor1_PAxCA | LTDC_BlendingFactor2_PAxCA);
                
                // 帧缓存起始地址，该地址定义在SDRAM上
                LTDC_Layerx->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
                LTDC_Layerx->CFBAR = ((CurrentLayer==LCD_LAYER_ALL)?GRAM_BASE_LAYER2:GRAM_BASE_LAYER1);
        }else
                return 1;
        
	// 帧缓存间隔
        LTDC_Layerx->CFBLR  &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
        LTDC_Layerx->CFBLR = (((m_LCD_config.LCD_Width*Pixel_N)+3) | ((m_LCD_config.LCD_Width*Pixel_N)<<16));
	
	// 帧缓存数
	LTDC_Layerx->CFBLNR  &= ~(LTDC_LxCFBLNR_CFBLNBR);
	LTDC_Layerx->CFBLNR  = m_LCD_config.LCD_Height; 
	
	
        // 设置重载寄存器， 立即重载
	LCD_ReloadReg(LTDC_SRCR_IMR);
        
        // 层使能
        LTDC_Layerx->CR |= (uint32_t)LTDC_LxCR_LEN;
        
        // 设置重载寄存器， 立即重载
	LCD_ReloadReg(LTDC_SRCR_IMR);
        
        // 激活抖动功能
        LTDC->GCR |= (uint32_t)LTDC_GCR_DTEN;
        
        
        return 0;
}

/*DESCRIPTION
 *      根据传入参数对LCD重载类型设置
 *ARGUMENTS
 * 	LCD_Reload	重载类型，LTDC_SRCR_IMR：立即重载；LTDC_SRCR_VBR：场消隐重载
 *RETURN
 *	NULL
 *NOTES
 *    
 */
void LCD_ReloadReg(uint32_t LCD_Reload)
{
	// 设置重载类型
	LTDC->SRCR	= (uint32_t)LCD_Reload;
	
}

/*DESCRIPTION
 *      LCD屏幕自检
 *ARGUMENTS
 * 	NULL
 *RETURN
 *	NULL
 *NOTES
 *    实现横、纵条纹及渐变纹理的显示自检
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
	
	// 横向条纹
	for(add_offset=0; add_offset<(LCD_WIDTH*LCD_HEIGHT*3); add_offset++){
		// 显示R、G、B三色条纹
		if(add_offset<(LCD_WIDTH*3*(LCD_HEIGHT/3))){
			// 红
			COLOR_DISPLAY_HORIZONTAL_AREA(add_offset, 0xFF0000);
		}else if((add_offset>=(LCD_WIDTH*3*(LCD_HEIGHT/3))) && (add_offset<(LCD_WIDTH*3*(LCD_HEIGHT/3)*2))){
			// 绿
			COLOR_DISPLAY_HORIZONTAL_AREA(add_offset, 0x00FF00);
		}else{
			// 蓝
			COLOR_DISPLAY_HORIZONTAL_AREA(add_offset, 0x0000FF);
		}
	}
	
	// 延时2s
	TIMER_Delay_ms(2000);

#define COLOR_DISPLAY_VERTICAL_AREA(ADD_OFFSET, COLOR)							\
	if(ADD_OFFSET%3==0)										\
		*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+ADD_OFFSET) = (COLOR&0xFF);	\
	else if(ADD_OFFSET%3==1)									\
		*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+ADD_OFFSET) = ((COLOR>>8)&0xFF);	\
	else if(ADD_OFFSET%3==2)									\
		*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+ADD_OFFSET) = ((COLOR>>16)&0xFF);
	
	// 纵向条纹
	for(index_y=0; index_y<LCD_HEIGHT; index_y++){
		for(index_x=0; index_x<LCD_WIDTH*3; index_x++){
			if(index_x<((LCD_WIDTH*3)/4)){
				// 红
				COLOR_DISPLAY_VERTICAL_AREA(index_x, 0xFF0000);
			}else if((index_x>=((LCD_WIDTH*3)/4)) && (index_x<(((LCD_WIDTH*3)/4)*2))){
				// 绿
				COLOR_DISPLAY_VERTICAL_AREA(index_x, 0x00FF00);
			}else if((index_x>=(((LCD_WIDTH*3)/4)*2)) && (index_x<(((LCD_WIDTH*3)/4)*3))){
				// 蓝
				COLOR_DISPLAY_VERTICAL_AREA(index_x, 0x0000FF);
			}else{
				// 红
				COLOR_DISPLAY_VERTICAL_AREA(index_x, 0xFF0000);
			}
		}
		 
	}
	
	// 延时2s
	TIMER_Delay_ms(2000);

	
	// 横向渐变
	for(index_y=0; index_y<LCD_HEIGHT; index_y++){
		if(index_y<(LCD_HEIGHT/3)){
			// R渐变
			for(index_x=0; index_x<LCD_WIDTH*3; index_x++){
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_WIDTH-(index_x/3))*255)/LCD_WIDTH)&0xFF;
			}
		}else if((index_y>=(LCD_HEIGHT/3)) && (index_y<((LCD_HEIGHT/3)*2))){
			// G渐变
			for(index_x=0; index_x<LCD_WIDTH*3; index_x++){
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_WIDTH-(index_x/3))*255)/LCD_WIDTH)&0xFF;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
			}
		}else{
			// G渐变
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
	
	// 延时2s
	TIMER_Delay_ms(2000);
	
	// 纵向渐变
	for(index_y=0; index_y<LCD_HEIGHT; index_y++){
		for(index_x=0; index_x<LCD_WIDTH*3; index_x++){
			if(index_x<((LCD_WIDTH*3)/4)){
				// 红
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_HEIGHT-index_y)*255)/LCD_HEIGHT)&0xFF;
			}else if((index_x>=((LCD_WIDTH*3)/4)) && (index_x<(((LCD_WIDTH*3)/4)*2))){
				// 绿
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_HEIGHT-index_y)*255)/LCD_HEIGHT)&0xFF;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
			}else if((index_x>=(((LCD_WIDTH*3)/4)*2)) && (index_x<(((LCD_WIDTH*3)/4)*3))){
				// 蓝
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_HEIGHT-index_y)*255)/LCD_HEIGHT)&0xFF;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
			}else{
				// 红
				if(index_x%3==0)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==1)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = 0x00;
				if(index_x%3==2)
					*((uint8_t*)CurrentFrameBuffer+(index_y*LCD_WIDTH*3)+index_x) = (((LCD_HEIGHT-index_y)*255)/LCD_HEIGHT)&0xFF;
			}
		}
	}
	// 延时2s
	TIMER_Delay_ms(2000);
	
}

