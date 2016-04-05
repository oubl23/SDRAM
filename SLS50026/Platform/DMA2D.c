/**
 ******************************************************************************
 * Copyright (c) 2015 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: DMA2D.c,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.1 $
 * Date		$Date: 2015/10/30 14:09:52 $
 * Description	
	PT1003 DMA2D
 ******************************************************************************
 */

#include "DMA2D.h"



 /*DESCRIPTION
 *      DMA2D初始化配置
 *ARGUMENTS
 * 	m_DMA2D_config	基本配置参数结构体
 *RETURN
 *NOTES
 *    
 */
void DMA2D_Config(DMA2D_config* m_DMA2D_config)
{	
	uint32_t ORed	= 0;
	uint32_t OGreen	= 0;
	uint32_t OAlpha	= 0;	
		
	//使能DMA2D时钟
	RCC->AHB1ENR |= RCC_AHB1RSTR_DMA2DRST;
	
	//DMA2D操作模式mode	
	DMA2D->CR &= (uint32_t)DMA2D_CR_MASK;
	DMA2D->CR |= m_DMA2D_config->DMA2D_Mode;
	
	//DMA2D输出的颜色模式
	DMA2D->OPFCCR |= m_DMA2D_config->DMA2D_CMode;
	//DAM2D 输出颜色寄存器，表示输出的颜色
	if(m_DMA2D_config->DMA2D_CMode==DMA2D_CMODE_ARGB8888){
		OGreen	= m_DMA2D_config->DMA2D_Green<<8;
		ORed	= m_DMA2D_config->DMA2D_Red<<16;
		OAlpha	= m_DMA2D_config->DMA2D_Alpha<<24;		
	} else if(m_DMA2D_config->DMA2D_CMode==DMA2D_CMODE_RGB888){
		OGreen	= m_DMA2D_config->DMA2D_Green<<8;
		ORed	= m_DMA2D_config->DMA2D_Red<<16;
		OAlpha	= (uint32_t)0x00000000;		
	} else if(m_DMA2D_config->DMA2D_CMode==DMA2D_CMODE_RGB565){
		OGreen	= m_DMA2D_config->DMA2D_Green<<5;
		ORed	= m_DMA2D_config->DMA2D_Red<<11;
		OAlpha	= (uint32_t)0x00000000;		
	} else if(m_DMA2D_config->DMA2D_CMode==DMA2D_CMODE_ARGB1555){
		OGreen	= m_DMA2D_config->DMA2D_Green<<5;
		ORed	= m_DMA2D_config->DMA2D_Red<<10;
		OAlpha	= m_DMA2D_config->DMA2D_Alpha<<15;	
	} else if(m_DMA2D_config->DMA2D_CMode==DMA2D_CMODE_ARGB4444){
		OGreen	= m_DMA2D_config->DMA2D_Green<<4;
		ORed	= m_DMA2D_config->DMA2D_Red<<8;
		OAlpha	= m_DMA2D_config->DMA2D_Alpha<<12;	
	}
	
	// 输出颜色配置
	DMA2D->OCOLR |= m_DMA2D_config->DMA2D_Blue| OAlpha| OGreen|ORed;
	
	// 输出数据地址
	DMA2D->OMAR = m_DMA2D_config->DMA2D_OMAdd;
	
	// 输出行偏移
	DMA2D->OOR &= ~(uint32_t)DMA2D_OOR_LO;
	DMA2D->OOR |= m_DMA2D_config->DMA2D_OLineOffset;
	// 配置每行像素数和行数	
	DMA2D->NLR &= ~(DMA2D_NLR_NL | DMA2D_NLR_PL);
	DMA2D->NLR |= (m_DMA2D_config->DMA2D_PixelPerLine<<16)|m_DMA2D_config->DMA2D_NumberLine;

	DMA2D->IFCR |=0x38;
}
 /*DESCRIPTION
 *      前景层结构体初始化
 *ARGUMENTS
 * 	m_DMA2D_FGconfig	前景层参数结构体
 *RETURN 
 *NOTES
 *    
 */
void DMA2D_FG_StructInit(DMA2D_FGconfig* m_DMA2D_FGconfig)
{ 
	m_DMA2D_FGconfig->DMA2D_FGMA = 0x00;
	m_DMA2D_FGconfig->DMA2D_FGO = 0x00; 
	m_DMA2D_FGconfig->DMA2D_FGCM = DMA2D_CMODE_ARGB8888;
	m_DMA2D_FGconfig->DMA2D_FG_CLUT_CM = DMA2D_CCMODE_ARGB8888;
	m_DMA2D_FGconfig->DMA2D_FG_CLUT_Size = 0x00;
	m_DMA2D_FGconfig->DMA2D_FGPFC_ALPHA_Mode = DMA2D_AM_0;
	m_DMA2D_FGconfig->DMA2D_FGPFC_ALPHA_Value = 0xFF;
	m_DMA2D_FGconfig->DMA2D_FGC_Blue = 0x00;
	m_DMA2D_FGconfig->DMA2D_FGC_Green = 0x00;
	m_DMA2D_FGconfig->DMA2D_FGC_Red = 0x00;
	m_DMA2D_FGconfig->DMA2D_FGCMAR = 0x00;
}

 /*DESCRIPTION
 *      前景层结构体初始化
 *ARGUMENTS
 * 	m_DMA2D_FGconfig	前景层参数结构体
 *RETURN 
 *NOTES
 *    
 */
void DMA2D_BG_StructInit(DMA2D_BGconfig* m_DMA2D_BGconfig)
{ 
	m_DMA2D_BGconfig->DMA2D_BGMA = 0x00;
	m_DMA2D_BGconfig->DMA2D_BGO = 0x00; 
	m_DMA2D_BGconfig->DMA2D_BGCM = DMA2D_CMODE_ARGB8888;
	m_DMA2D_BGconfig->DMA2D_BG_CLUT_CM = DMA2D_CCMODE_ARGB8888;
	m_DMA2D_BGconfig->DMA2D_BG_CLUT_Size = 0x00;
	m_DMA2D_BGconfig->DMA2D_BGPFC_ALPHA_Mode = DMA2D_AM_0;
	m_DMA2D_BGconfig->DMA2D_BGPFC_ALPHA_Value = 0xFF;
	m_DMA2D_BGconfig->DMA2D_BGC_Blue = 0x00;
	m_DMA2D_BGconfig->DMA2D_BGC_Green = 0x00;
	m_DMA2D_BGconfig->DMA2D_BGC_Red = 0x00;
	m_DMA2D_BGconfig->DMA2D_BGCMAR = 0x00;
}
/*DESCRIPTION
 *      DMA2D前景层FG配置
 *ARGUMENTS
 * 	m_DMA2D_FGconfig	前景层参数结构体
 *RETURN 
 *NOTES
 *    
 */


void DMA2D_FGConfig(DMA2D_FGconfig *m_DMA2D_FGconfig)
{

	// 配置FG的数据内存地址
	DMA2D->FGMAR = (m_DMA2D_FGconfig->DMA2D_FGMA);

	//  配置行偏移量
	DMA2D->FGOR &= ~(uint32_t)DMA2D_FGOR_LO;
	DMA2D->FGOR |= (m_DMA2D_FGconfig->DMA2D_FGO);

	// 配置前景颜色输入格式
	DMA2D->FGPFCCR &= (uint32_t)PFCCR_MASK;
	DMA2D->FGPFCCR |= (m_DMA2D_FGconfig->DMA2D_FGCM | (m_DMA2D_FGconfig->DMA2D_FG_CLUT_CM << 4) | (m_DMA2D_FGconfig->DMA2D_FG_CLUT_Size << 8) | (m_DMA2D_FGconfig->DMA2D_FGPFC_ALPHA_Mode << 16)| (m_DMA2D_FGconfig->DMA2D_FGPFC_ALPHA_Value << 24));

	// 配置FG颜色
	DMA2D->FGCOLR &= ~(DMA2D_FGCOLR_BLUE | DMA2D_FGCOLR_GREEN | DMA2D_FGCOLR_RED);
	DMA2D->FGCOLR |= (m_DMA2D_FGconfig->DMA2D_FGC_Blue | (m_DMA2D_FGconfig->DMA2D_FGC_Green << 8) | (m_DMA2D_FGconfig->DMA2D_FGC_Red << 16));

	// 配置 FG CLCU 内存地址
	DMA2D->FGCMAR = m_DMA2D_FGconfig->DMA2D_FGCMAR;	
}
/*DESCRIPTION
 *      DMA2D前景层FG配置
 *ARGUMENTS
 * 	m_DMA2D_FGconfig	前景层参数结构体
 *RETURN 
 *NOTES
 *    
 */
void DMA2D_BGConfig(DMA2D_BGconfig *m_DMA2D_BGconfig)
{

	// 配置BG的数据内存地址
	DMA2D->BGMAR = (m_DMA2D_BGconfig->DMA2D_BGMA);

	//  配置BG行偏移量
	DMA2D->BGOR &= ~(uint32_t)DMA2D_BGOR_LO;
	DMA2D->BGOR |= (m_DMA2D_BGconfig->DMA2D_BGO);

	// 配置背景颜色输入格式
	DMA2D->BGPFCCR &= (uint32_t)PFCCR_MASK;
	DMA2D->BGPFCCR |= (m_DMA2D_BGconfig->DMA2D_BGCM | (m_DMA2D_BGconfig->DMA2D_BG_CLUT_CM << 4) | (m_DMA2D_BGconfig->DMA2D_BG_CLUT_Size << 8) | (m_DMA2D_BGconfig->DMA2D_BGPFC_ALPHA_Mode << 16)| (m_DMA2D_BGconfig->DMA2D_BGPFC_ALPHA_Value << 24));

	// 配置BG颜色
	DMA2D->BGCOLR &= ~(DMA2D_BGCOLR_BLUE | DMA2D_BGCOLR_GREEN | DMA2D_BGCOLR_RED);
	DMA2D->BGCOLR |= (m_DMA2D_BGconfig->DMA2D_BGC_Blue | (m_DMA2D_BGconfig->DMA2D_BGC_Green << 8) | (m_DMA2D_BGconfig->DMA2D_BGC_Red << 16));

	// 配置 BG CLCU 内存地址
	DMA2D->BGCMAR = m_DMA2D_BGconfig->DMA2D_BGCMAR;	
}
 /*DESCRIPTION
 *      DMA2D开始数据传输
 *ARGUMENTS
 * 	NULL
 *RETURN 
 *NOTES
 *    
 */
void DMA2D_StartTransfer(void)
{
   
    DMA2D->CR |= (uint32_t)DMA2D_CR_START;
}
 /*DESCRIPTION
 *      DMA2D中止数据传输
 *ARGUMENTS
 * 	NULL
 *RETURN 
 *NOTES
 *    
 */
void DMA2D_AbortTransfer(void)
{
      DMA2D->CR |= (uint32_t)DMA2D_CR_ABORT;
}

 
 uint32_t CLUT_COLOR[256]={
	0xFF000000, 0xFF010101, 0xFF020202, 0xFF030303, 0xFF040404, 0xFF050505, 0xFF060606, 0xFF070707, 0xFF080808, 0xFF090909, 0xFF0A0A0A, 0xFF0B0B0B, 
	0xFF0C0C0C, 0xFF0D0D0D, 0xFF0E0E0E, 0xFF0F0F0F, 0xFF101010, 0xFF111111, 0xFF121212, 0xFF131313, 0xFF141414, 0xFF151515, 0xFF161616, 0xFF171717,
	0xFF181818, 0xFF191919, 0xFF1A1A1A, 0xFF1B1B1B, 0xFF1C1C1C, 0xFF1D1D1D, 0xFF1E1E1E, 0xFF1F1F1F, 0xFF202020, 0xFF212121, 0xFF222222, 0xFF232323, 
	0xFF242424, 0xFF252525, 0xFF262626, 0xFF272727, 0xFF282828, 0xFF292929, 0xFF2A2A2A, 0xFF2B2B2B, 0xFF2C2C2C, 0xFF2D2D2D, 0xFF2E2E2E, 0xFF2F2F2F, 
	0xFF303030, 0xFF313131, 0xFF323232, 0xFF333333, 0xFF343434, 0xFF353535, 0xFF363636, 0xFF373737, 0xFF383838, 0xFF393939, 0xFF3A3A3A, 0xFF3B3B3B,
	0xFF3C3C3C, 0xFF3D3D3D, 0xFF3E3E3E, 0xFF3F3F3F, 0xFF404040, 0xFF414141, 0xFF424242, 0xFF434343, 0xFF444444, 0xFF454545, 0xFF464646, 0xFF474747,
	0xFF484848, 0xFF494949, 0xFF4A4A4A, 0xFF4B4B4B, 0xFF4C4C4C, 0xFF4D4D4D, 0xFF4E4E4E, 0xFF4F4F4F, 0xFF505050, 0xFF515151, 0xFF525252, 0xFF535353,
	0xFF545454, 0xFF555555, 0xFF565656, 0xFF575757, 0xFF585858, 0xFF595959, 0xFF5A5A5A, 0xFF5B5B5B, 0xFF5C5C5C, 0xFF5D5D5D, 0xFF5E5E5E, 0xFF5F5F5F,
	0xFF606060, 0xFF616161, 0xFF626262, 0xFF636363, 0xFF646464, 0xFF656565, 0xFF666666, 0xFF676767, 0xFF686868, 0xFF696969, 0xFF6A6A6A, 0xFF6B6B6B, 
	0xFF6C6C6C, 0xFF6D6D6D, 0xFF6E6E6E, 0xFF6F6F6F, 0xFF707070, 0xFF717171, 0xFF727272, 0xFF737373, 0xFF747474, 0xFF757575, 0xFF767676, 0xFF777777, 
	0xFF787878, 0xFF797979, 0xFF7A7A7A, 0xFF7B7B7B, 0xFF7C7C7C, 0xFF7D7D7D, 0xFF7E7E7E, 0xFF7F7F7F, 0xFF808080, 0xFF818181, 0xFF828282, 0xFF838383,
	0xFF848484, 0xFF858585, 0xFF868686, 0xFF878787, 0xFF888888, 0xFF898989, 0xFF8A8A8A, 0xFF8B8B8B, 0xFF8C8C8C, 0xFF8D8D8D, 0xFF8E8E8E, 0xFF8F8F8F,
	0xFF909090, 0xFF919191, 0xFF929292, 0xFF939393, 0xFF949494, 0xFF959595, 0xFF969696, 0xFF979797, 0xFF989898, 0xFF999999, 0xFF9A9A9A, 0xFF9B9B9B,
	0xFF9C9C9C, 0xFF9D9D9D, 0xFF9E9E9E, 0xFF9F9F9F, 0xFFA0A0A0, 0xFFA1A1A1, 0xFFA2A2A2, 0xFFA3A3A3, 0xFFA4A4A4, 0xFFA5A5A5, 0xFFA6A6A6, 0xFFA7A7A7, 
	0xFFA8A8A8, 0xFFA9A9A9, 0xFFAAAAAA, 0xFFABABAB, 0xFFACACAC, 0xFFADADAD, 0xFFAEAEAE, 0xFFAFAFAF, 0xFFB0B0B0, 0xFFB1B1B1, 0xFFB2B2B2, 0xFFB3B3B3, 
	0xFFB4B4B4, 0xFFB5B5B5, 0xFFB6B6B6, 0xFFB7B7B7, 0xFFB8B8B8, 0xFFB9B9B9, 0xFFBABABA, 0xFFBBBBBB, 0xFFBCBCBC, 0xFFBDBDBD, 0xFFBEBEBE, 0xFFBFBFBF,
	0xFFC0C0C0, 0xFFC1C1C1, 0xFFC2C2C2, 0xFFC3C3C3, 0xFFC4C4C4, 0xFFC5C5C5, 0xFFC6C6C6, 0xFFC7C7C7, 0xFFC8C8C8, 0xFFC9C9C9, 0xFFCACACA, 0xFFCBCBCB,
	0xFFCCCCCC, 0xFFCDCDCD, 0xFFCECECE, 0xFFCFCFCF, 0xFFD0D0D0, 0xFFD1D1D1, 0xFFD2D2D2, 0xFFD3D3D3, 0xFFD4D4D4, 0xFFD5D5D5, 0xFFD6D6D6, 0xFFD7D7D7,
	0xFFD8D8D8, 0xFFD9D9D9, 0xFFDADADA, 0xFFDBDBDB, 0xFFDCDCDC, 0xFFDDDDDD, 0xFFDEDEDE, 0xFFDFDFDF, 0xFFE0E0E0, 0xFFE1E1E1, 0xFFE2E2E2, 0xFFE3E3E3,
	0xFFE4E4E4, 0xFFE5E5E5, 0xFFE6E6E6, 0xFFE7E7E7, 0xFFE8E8E8, 0xFFE9E9E9, 0xFFEAEAEA, 0xFFEBEBEB, 0xFFECECEC, 0xFFEDEDED, 0xFFEEEEEE, 0xFFEFEFEF,
	0xFFF0F0F0, 0xFFF1F1F1, 0xFFF2F2F2, 0xFFF3F3F3, 0xFFF4F4F4, 0xFFF5F5F5, 0xFFF6F6F6, 0xFFF7F7F7, 0xFFF8F8F8, 0xFFF9F9F9, 0xFFFAFAFA, 0xFFFBFBFB,
	0xFFFCFCFC, 0xFFFDFDFD, 0xFFFEFEFE, 0xFFFFFFFF, 
};

