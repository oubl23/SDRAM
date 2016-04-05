/**
 ******************************************************************************
 * Copyright (c) 2014 Chongqing MySHworks Technology Co., Ltd. 
 * All rights reserved.
 *
 * File		$RCSfile: Texture.h,v $
 * Author	$Author: zhouchenglin $
 * Version	$Revision: 1.3 $
 * Date		$Date: 2015/10/30 14:09:43 $
 * Description	
	������Ϣͷ�ļ�
 ******************************************************************************
 */
 

#define TEXTURE_N	10

#define	TEXTURE_TYPE_8BIT	1	
// 16λ��ɫ����RGB565��ÿ����2�ֽ�
#define	TEXTURE_TYPE_16BIT	2
// 16λ��ɫ����RGB888��ÿ����3�ֽ�
#define	TEXTURE_TYPE_24BIT	3
// 32λ��ɫ����A8R8G8B8����8λalphaͨ����ÿ����4�ֽ�
#define	TEXTURE_TYPE_32BIT	4
// �������鶨��
extern const unsigned char texture_Test_data[50*50*3];
extern const unsigned char texture_Test_data1[100*50];
extern const unsigned char texture_Test_data2[50*50*2];


//  
extern const unsigned int	texture_size[TEXTURE_N];
extern const unsigned char*	texture[TEXTURE_N];
extern const unsigned int 	texture_type[TEXTURE_N];


