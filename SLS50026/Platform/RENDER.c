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
	PT1003  图形绘制显示实现
 ******************************************************************************
 */

#include "RENDER.h"

uint32_t	BlackGround_Color = 0xFFFFFFFF;
	

 /*DESCRIPTION
 *      绘图初始化
 *ARGUMENTS
 * 	NULL
 *RETURN
 *	0 	初始化成功
 *NOTES
 *    
 */
int RENDER_initial(void)
{
	// SDRAM初始化
	SDRAM_Init();
	
	// SDRAM自检，成功则LED2灯亮，若自检失败则灯熄灭
//	SDRAM_SelfCheck();
	
        // LCD初始化
	LCD_Initial(LCD_LAYER_TWO);
	
	// LCD自检，包括横、竖条纹及横向、纵向渐变
//	LCD_SelfCheck();
	
//	// 字符显示测试
//	RENDER_DisplayString(100, 120, (uint8_t*)"SUCCESS!", 0x00FF00);
//	RENDER_DisplayString(100, 60, (uint8_t*)"XCP!", 0x00FF00);
	
	// 载入纹理
	
	
	
        return 0;
}

 /*DESCRIPTION
 *      清屏
 *ARGUMENTS
 * 	Color	清屏后的颜色
 *RETURN
 *	NULL
 *NOTES
 *    传入颜色值后，实现清屏
 */
void RENDER_Clear(uint32_t Color)
{
	// 这里仅处理24bit颜色
	uint32_t	m_offset=0;
	
	// 获取传入清屏颜色
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
 *      清理需要擦除的纹理
 *ARGUMENTS
 * 	Color	清屏后的颜色
 *	index	索引值
 * 	Xpos	屏幕横坐标值
 *	Ypos	屏幕纵坐标值
 *RETURN
 *	NULL
 *NOTES
 *    传入颜色值后，实现清屏
 */
void RENDER_Clear_Original(uint16_t index,uint32_t Xpos,uint32_t Ypos,uint32_t Color)
{
	// 这里仅处理24bit颜色
	uint32_t	w	= 0;
	uint32_t	h	= 0;
	uint32_t 	Xadress	= CurrentFrameBuffer+4*(Ypos*LCD_WIDTH+Xpos);	
	uint32_t	adress	= 0;
	// 获取传入清屏颜色
	BlackGround_Color	= Color;
	// 获取清理的位置
	
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
 *      载入纹理
 *ARGUMENTS
 * 	index 	索引值
 *	w	文理数据宽度
 *	h	文理数据高度
 * 	type	纹理数据类型
 *RETURN
 *	0	成功载入纹理数据
 *NOTES
 *    依次载入纹理数据
 */
int RENDER_load_texture()
{
	uint32_t	base  = 0;
        uint32_t	size  = 0;
	uint8_t		index = 0;
	
	base	= TEXTURE_BASE;
	// 纹理信息写入
	for(index=0;index<texture_n;index++)
	{
		textures[index].Texture_h	= TEXTURE_HEIGHT(index);
		textures[index].Texture_w	= TEXTURE_WIDTH(index);		
		textures[index].Texture_type	= TEXTURE_TYPE(index);
		//纹理数据每个像素对应的字节数
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
		
		// 获得SDRAM内的地址
		if(index==0){
			textures[index].Texture_addr	= (uint8_t*)base;
		} else
			textures[index].Texture_addr	= textures[index-1].Texture_addr + textures[index-1].Texture_h*textures[index-1].Texture_w*textures[index-1].Texture_type;

		memcpy(textures[index].Texture_addr, texture_pointer[index], size);
		
	}
	return 0;
}     
        

/*DESCRIPTION
 *      字符显示
 *ARGUMENTS
 * 	x		字符显示起始x坐标
 *	y		字符显示起始y坐标
 *	str		需要显示字符串
 *RETURN
 *	0 		字符显示成功
 *NOTES
 *    显示字符16*24点阵字体，仅显示可打印字符，从空格（ASCII码32）起始到~（ASCII码126）止
 */
int RENDER_DisplayString(uint32_t x, uint32_t y, uint8_t *str, uint32_t Color)
{	
	while((x<LCD_WIDTH) && ((*str != 0) & (((x + DotMatrixFont16x24.Width) & 0xFFFF) >= DotMatrixFont16x24.Width))){
		// 显示字符到显示屏
		RENDER_DrawChar(x, y, str, Color);
		x+=DotMatrixFont16x24.Width;
		str++;
	}
	
	return 0;
}	

/*DESCRIPTION
 *      绘制字符
 *ARGUMENTS
 * 	Xpos		字符显示基准点x坐标		
 *	YPos		字符显示基准点y坐标
 *	Ascii		字符Ascii码
 *	Color		显示的字符颜色
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
	
	// 显示字符到指定区域
	for(index=0; index<DotMatrixFont16x24.Height; index++){
		for(counter=0; counter<(DotMatrixFont16x24.Width*4); counter++){
			// 不显示部分为背景色（提供的点阵字体为镜像）
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


int RENDER_DisplayLine(uint32_t stx, uint32_t sty, uint32_t enx, uint32_t eny);         // 显示线





/* 
 * DESCRIPTION
 * 	添加到绘图列表
 * ARGUMENTS
 *	x		纹理对齐点的屏幕坐标x（屏幕左下角为原点）
 *	y	 	纹理对齐点的屏幕坐标y（屏幕左下角为原点）
 *	option		贴图选项
 *	color		贴图颜色
 *	index		纹理索引
 *	angle		旋转角度	
 * RETURN
 *	0		添加成功
 * NOTES
 *	依次调用该函数进行遍历绘图列表
 */ 
// 贴图数量
int RENDER_add_map(uint16_t x, uint16_t y, uint32_t option, uint32_t color, uint16_t index,  float angle)
{
	int	n;
	
	n	= 0;
	// 判断最后一个有效的贴图
	while(MAP_IS_VALID(map_list[n])){
		n++;
	}
	// 判断是否超出这个范围
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
 * 	调用此函数开始绘图。
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
	// 判断最后一个有效的贴图
	while(MAP_IS_VALID(map_list[num])){
		num++;
	}
	// 判断是否超出这个范围
	if(num>=MAP_LIST_MAX)
		return;
	
	
	for(i=0;i<num;i++){		
		if(!MAP_IS_VALID(map_list[i]))
			continue;
		// 边界处理
		if(map_list[i].x+textures[map_list[i].index].Texture_w>LCD_WIDTH||map_list[i].y+textures[map_list[i].index].Texture_h>LCD_HEIGHT){
			continue;		
		}
		
		//当颜色为白色时，就显示当前图片的纹理；为其他颜色的时候，显示传进来的颜色值
		if(map_list[i].color==0xFFFFFFFF)
			RENDER_PFC(map_list[i].x,map_list[i].y,map_list[i].index);
		else{
			RENDER_ShowColor(map_list[i].x,map_list[i].y,map_list[i].index,map_list[i].color);			
		}
	}
	//延迟时间，方便看到图片的移动效果
	TIMER_Delay_ms(400);
	for(i=0;i<num;i++){
		// 判断是静态还是动态图片，动态图需要清理当前数据
		if(MAP_IS_DYNAMIC(map_list[i])){
			RENDER_Clear_Original(map_list[i].index,map_list[i].x,map_list[i].y,0xFFFFFFFF);			
		}
		map_list[i].option	= 0x00;		
	}
	
}


/*DESCRIPTION
 *      DMA2D混合图片
 *ARGUMENTS
 * 	Xpos		屏幕横坐标
 *	Ypos		屏幕纵坐标
 *	Length		像素长度
 *	Direction	方向
 *	ColorARGB	颜色值
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
	
	//写入数据到混合地址中去，作为RGB888方式传入
	for(i=0;i<size;i+=3){
		*(uint8_t*)(BELEDING_BASE+i)	= (Color&0xFF);
		*(uint8_t*)(BELEDING_BASE+i+1)	= ((Color>>8)&0xFF);
		*(uint8_t*)(BELEDING_BASE+i+2)	= ((Color>>16)&0xFF);
	}
	// 获得alpha值
	alpha			= (Color>>24)&0xFF;
	
	//DMA2D模式 存储器到存储器并执行混合
	m_DMA2D_config.DMA2D_Mode	= DMA2D_MODE_M2M_BLE;
	
	//输出颜色模式
	m_DMA2D_config.DMA2D_CMode	= DMA2D_CMODE_ARGB8888;
	
	//配置显示的颜色
	m_DMA2D_config.DMA2D_Alpha	= 0;
	m_DMA2D_config.DMA2D_Red	= 0;
	m_DMA2D_config.DMA2D_Green	= 0;
	m_DMA2D_config.DMA2D_Blue	= 0;
	
	//配置输出的数据地址
	m_DMA2D_config.DMA2D_OMAdd	= Xadress;
	//配置行偏移
	m_DMA2D_config.DMA2D_OLineOffset = LCD_WIDTH-textures[index].Texture_w;
	//配置每行像素数和行数
	m_DMA2D_config.DMA2D_PixelPerLine = textures[index].Texture_w;
	m_DMA2D_config.DMA2D_NumberLine	= textures[index].Texture_h;
	
	// 配置相关寄存器
	DMA2D_Config(&m_DMA2D_config);
	
	//初始化FG和BG结构体	
	DMA2D_FG_StructInit(&m_DMA2D_FGconfig);
	DMA2D_BG_StructInit(&m_DMA2D_BGconfig);
	
	//FG=255,显示为FG图像
	
	
	
	// 颜色数据输入地址,混合颜色的首地址
	m_DMA2D_BGconfig.DMA2D_BGMA			= (uint32_t)BELEDING_BASE;
	// 输入颜色模式
	m_DMA2D_BGconfig.DMA2D_BGCM			= DMA2D_CMODE_RGB888;
	// 透明度模式
	m_DMA2D_BGconfig.DMA2D_BGPFC_ALPHA_Mode		= DMA2D_AM_1;
	// 透明度值
	m_DMA2D_BGconfig.DMA2D_BGPFC_ALPHA_Value	= 100;	
	
	DMA2D_BGConfig(&m_DMA2D_BGconfig);
	
	// 颜色数据输入地址
	m_DMA2D_FGconfig.DMA2D_FGMA			= (uint32_t)textures[index].Texture_addr;
	// 输入颜色模式
	if(textures[index].Texture_type==1){
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_L8;
		// 查找表地址
		m_DMA2D_FGconfig.DMA2D_FGCMAR	= (uint32_t)DMA2D_CLUT_ADRESS;
		// 颜色查找表颜色模式
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_CM = DMA2D_CCMODE_ARGB8888;
		
		// 颜色查找表大小
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_Size =255;		
	} else if(textures[index].Texture_type==2)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB565;
	else if(textures[index].Texture_type==3)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB888;
	else if(textures[index].Texture_type==4)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_ARGB8888;
	
	// 透明度模式
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Mode		= DMA2D_AM_1;
	// 透明度值
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Value	= 255*(alpha-m_DMA2D_BGconfig.DMA2D_BGPFC_ALPHA_Value)/(255-m_DMA2D_BGconfig.DMA2D_BGPFC_ALPHA_Value);	
	
	DMA2D_FGConfig(&m_DMA2D_FGconfig);
	DMA2D->FGPFCCR |= 1<<5;
	while((DMA2D->ISR&DMA2D_ISR_CTCIF)!=0x10){
	};
	
	
	DMA2D_StartTransfer();	
	
}
 /*DESCRIPTION
 *      DMA2D画直线
 *ARGUMENTS
 * 	Xpos		屏幕横坐标
 *	Ypos		屏幕纵坐标
 *	ColorARGB	颜色值
 *RETURN 
 *NOTES
 *    
 */
void RENDER_ShowColor(uint16_t Xpos, uint16_t Ypos,uint16_t index,uint32_t ColorARGB)
{
	uint32_t Xaddress =  0;
	Xaddress = DMA2D_SDRAM_ADR + 4*(LCD_WIDTH*Ypos + Xpos);
	
	//DMA2D模式 寄存器到存储器
	m_DMA2D_config.DMA2D_Mode	= DMA2D_MODE_R2M;
	
	//输出颜色模式
	m_DMA2D_config.DMA2D_CMode	= DMA2D_CMODE_ARGB8888;
	
	//配置显示的颜色
	m_DMA2D_config.DMA2D_Alpha	= (ColorARGB&0xFF000000)>>24;
	m_DMA2D_config.DMA2D_Red	= (ColorARGB&0x00FF0000)>>16;
	m_DMA2D_config.DMA2D_Green	= (ColorARGB&0x0000FF00)>>8;
	m_DMA2D_config.DMA2D_Blue	= (ColorARGB&0x000000FF);
	
	//配置输出的数据地址
	m_DMA2D_config.DMA2D_OMAdd	= Xaddress;
	

	//配置行偏移
	m_DMA2D_config.DMA2D_OLineOffset = LCD_WIDTH-textures[index].Texture_w;
	//配置每行像素数和行数
	m_DMA2D_config.DMA2D_PixelPerLine = textures[index].Texture_w;
	m_DMA2D_config.DMA2D_NumberLine	= textures[index].Texture_h;

	DMA2D_Config(&m_DMA2D_config);
	// 数据传输
	DMA2D_StartTransfer();	
	while((DMA2D->ISR&0x02)!=0x02){
			
	}
	
	DMA2D->IFCR |= 0x02;
	
	while((DMA2D->ISR&0x02)!=0x00){	
						
	}
	
}
 /*DESCRIPTION
 *      DMA2D画直线
 *ARGUMENTS
 * 	Xpos		屏幕横坐标
 *	Ypos		屏幕纵坐标
 *	Length		像素长度
 *	Direction	方向
 *	ColorARGB	颜色值
 *RETURN 
 *NOTES
 *    
 */
void RENDER_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction,uint32_t ColorARGB)
{
	uint32_t Xaddress =  0;
	Xaddress = DMA2D_SDRAM_ADR + 4*(320*Ypos + Xpos);
	
	//DMA2D模式 寄存器到存储器
	m_DMA2D_config.DMA2D_Mode	= DMA2D_MODE_R2M;
	
	//输出颜色模式
	m_DMA2D_config.DMA2D_CMode	= DMA2D_CMODE_ARGB8888;
	
	//配置显示的颜色
	m_DMA2D_config.DMA2D_Alpha	= (ColorARGB&0xFF000000)>>24;
	m_DMA2D_config.DMA2D_Red	= (ColorARGB&0x00FF0000)>>16;
	m_DMA2D_config.DMA2D_Green	= (ColorARGB&0x0000FF00)>>8;
	m_DMA2D_config.DMA2D_Blue	= (ColorARGB&0x000000FF);
	
	//配置输出的数据地址
	m_DMA2D_config.DMA2D_OMAdd	= Xaddress;
	
	// 行偏移，每行像素数和行数
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
	// 数据传输
	DMA2D_StartTransfer();	
}

 /*DESCRIPTION
 *      DMA2D
 *ARGUMENTS
 * 	Xpos		屏幕横坐标
 *	Ypos		屏幕纵坐标
 *	Length		像素长度
 *	Direction	方向
 *	ColorARGB	颜色值
 *RETURN 
 *NOTES
 *    
 */

void RENDER_PFC(uint16_t Xpos, uint16_t Ypos,uint32_t index)
{
	
	uint32_t Xadress	= 0;
	Xadress			= 4*(Ypos*LCD_WIDTH +Xpos) + DMA2D_SDRAM_ADR;
	
	m_DMA2D_config.DMA2D_Mode	= DMA2D_MODE_M2M_PFC;
	
	//输出颜色模式
	m_DMA2D_config.DMA2D_CMode	= DMA2D_CMODE_ARGB8888;
	
	//配置显示的颜色
	m_DMA2D_config.DMA2D_Alpha	= 0;
	m_DMA2D_config.DMA2D_Red	= 0;
	m_DMA2D_config.DMA2D_Green	= 0;
	m_DMA2D_config.DMA2D_Blue	= 0;
	
	//配置输出的数据地址
	m_DMA2D_config.DMA2D_OMAdd	= Xadress;
	//配置行偏移
	m_DMA2D_config.DMA2D_OLineOffset = LCD_WIDTH-textures[index].Texture_w;
	//配置每行像素数和行数
	m_DMA2D_config.DMA2D_PixelPerLine = textures[index].Texture_w;
	m_DMA2D_config.DMA2D_NumberLine	= textures[index].Texture_h;
	
	// 配置相关寄存器
	DMA2D_Config(&m_DMA2D_config);
	
	//初始化FG和BG结构体
	DMA2D_FG_StructInit(&m_DMA2D_FGconfig);
	DMA2D_BG_StructInit(&m_DMA2D_BGconfig);
	
	// 颜色数据输入地址
	m_DMA2D_FGconfig.DMA2D_FGMA			= (uint32_t)textures[index].Texture_addr;
	// 输入颜色模式
	if(textures[index].Texture_type==1){
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_L8;
		// 查找表地址
		m_DMA2D_FGconfig.DMA2D_FGCMAR	= (uint32_t)DMA2D_CLUT_ADRESS;
		// 颜色查找表颜色模式
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_CM = DMA2D_CCMODE_ARGB8888;		
		// 颜色查找表大小
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_Size =255;		
	}
	else if(textures[index].Texture_type==2)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB565;
	else if(textures[index].Texture_type==3)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB888;
	else if(textures[index].Texture_type==4)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_ARGB8888;
	
	DMA2D_FGConfig(&m_DMA2D_FGconfig);
	// 透明度模式
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Mode		= DMA2D_AM_1;
	// 透明度值
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
 * 	Xpos		屏幕横坐标
 *	Ypos		屏幕纵坐标
 *	index		纹理索引值
 *RETURN 
 *NOTES
 *    
 */
void RENDER_PFC_CLUT(uint16_t Xpos, uint16_t Ypos,uint32_t index)
{
	uint32_t Xadress	= 0;
	Xadress			=4*(Ypos*LCD_WIDTH +Xpos) + DMA2D_SDRAM_ADR;
	//DMA2D模式 寄存器到存储器
	m_DMA2D_config.DMA2D_Mode	= DMA2D_MODE_M2M_PFC;
	
	//输出颜色模式
	m_DMA2D_config.DMA2D_CMode	= DMA2D_CMODE_ARGB8888;
	
	//配置显示的颜色
	m_DMA2D_config.DMA2D_Alpha	= 0;
	m_DMA2D_config.DMA2D_Red	= 0;
	m_DMA2D_config.DMA2D_Green	= 0;
	m_DMA2D_config.DMA2D_Blue	= 0;
	
	//配置输出的数据地址
	m_DMA2D_config.DMA2D_OMAdd	= Xadress;
	//配置行偏移
	m_DMA2D_config.DMA2D_OLineOffset = LCD_WIDTH-textures[index].Texture_w;
	//配置每行像素数和行数
	m_DMA2D_config.DMA2D_PixelPerLine = textures[index].Texture_w;
	m_DMA2D_config.DMA2D_NumberLine	= textures[index].Texture_h;
	
	// 配置相关寄存器
	DMA2D_Config(&m_DMA2D_config);
	
	//初始化FG和BG结构体	
	DMA2D_FG_StructInit(&m_DMA2D_FGconfig);
	DMA2D_BG_StructInit(&m_DMA2D_BGconfig);
	
	// 颜色数据输入地址
	m_DMA2D_FGconfig.DMA2D_FGMA			= (uint32_t)textures[index].Texture_addr;
	// 输入颜色模式
	if(textures[index].Texture_type==1){
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_L8;
		// 查找表地址
		m_DMA2D_FGconfig.DMA2D_FGCMAR	= (uint32_t)DMA2D_CLUT_ADRESS;
		// 颜色查找表颜色模式
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_CM = DMA2D_CCMODE_ARGB8888;
		
		// 颜色查找表大小
		m_DMA2D_FGconfig.DMA2D_FG_CLUT_Size =255;		
	} else if(textures[index].Texture_type==2)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB565;
	else if(textures[index].Texture_type==3)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_RGB888;
	else if(textures[index].Texture_type==4)
		m_DMA2D_FGconfig.DMA2D_FGCM			= DMA2D_CMODE_ARGB8888;
	
	// 透明度模式
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Mode		= DMA2D_AM_1;
	// 透明度值
	m_DMA2D_FGconfig.DMA2D_FGPFC_ALPHA_Value	= 255;	
	
	DMA2D_FGConfig(&m_DMA2D_FGconfig);
	DMA2D->FGPFCCR |= 1<<5;
	while((DMA2D->ISR&DMA2D_ISR_CTCIF)!=0x10){
	};
	DMA2D_StartTransfer();	
	
	DMA2D->CR |= (uint32_t)0x0;	
}

