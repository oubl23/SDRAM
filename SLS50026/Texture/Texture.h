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
	纹理信息头文件
 ******************************************************************************
 */
 

#define TEXTURE_N	10

#define	TEXTURE_TYPE_8BIT	1	
// 16位彩色纹理RGB565，每像素2字节
#define	TEXTURE_TYPE_16BIT	2
// 16位彩色纹理RGB888，每像素3字节
#define	TEXTURE_TYPE_24BIT	3
// 32位彩色纹理A8R8G8B8，带8位alpha通道，每像素4字节
#define	TEXTURE_TYPE_32BIT	4
// 纹理数组定义
extern const unsigned char texture_Test_data[50*50*3];
extern const unsigned char texture_Test_data1[100*50];
extern const unsigned char texture_Test_data2[50*50*2];


//  
extern const unsigned int	texture_size[TEXTURE_N];
extern const unsigned char*	texture[TEXTURE_N];
extern const unsigned int 	texture_type[TEXTURE_N];


