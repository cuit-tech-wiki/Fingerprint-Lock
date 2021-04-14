/************************************************************************************
*  Copyright (c), 2013, HelTec Automatic Technology co.,LTD.
*            All rights reserved.
*
* Http:    www.heltec.cn
* Email:   cn.heltec@gmail.com
* WebShop: heltec.taobao.com
*
* File name: OLED12864.c
* Project  : OLED
* Processor: STC89C52
* Compiler : Keil C51 Compiler
* 
* Author : С��
* Version: 1.00
* Date   : 2013.8.8
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description: 128*64����OLEDģ�鹦����ʾ�������������������heltec.taobao.com���۲�Ʒ
*
* Others: none;
*
* Function List:
*
* 1. void delay(unsigned int z) -- �����������ڵ�����ʾЧ������ʱ����,STC89C52 12MHZ z=1ʱ��Լ��ʱ1ms,����Ƶ����Ҫ�Լ�����
* 2. void main(void) -- ������
*
* History: none;
*
*************************************************************************************/

//#include "reg52.h"
#include "intrins.h"
#include "codetab.h"
#include "LQ12864.h"
sbit k1=P3^0;
sbit k2=P3^1;
sbit k3=P3^2;
sbit k4=P3^3;

void main(void)
//{


//	OLED_Init(); //OLED��ʼ��
//	OLED_P8x16Str(0,4,"520");
//	while(1)
//	{
//		OLED_Fill(0xff); //��ȫ��
//		delay(2000);
//		OLED_Fill(0x00); //��ȫ��
//		delay(200);
		//OLED_P16x16Ch(24,0,1);
		//OLED_P16x16Ch(40,0,2);
		//OLED_P16x16Ch(57,0,3);
		//OLED_P16x16Ch(74,0,4);
		//OLED_P16x16Ch(91,0,5);
		/*	for(i=0; i<7; i++)//ͨ��������ʾ���� -- i��ʾ�ֱ������λ��
		{
//			OLED_P16x16Ch(i*16,0,i);
		 	//OLED_P16x16Ch(i*16,2,i+8);
		 	OLED_P16x16Ch(i*16,4,i+16);
		 //	OLED_P16x16Ch(i*16,6,i+24);
		}
		delay(4000);
		OLED_CLS();//����

		/*	OLED_P8x16Str(0,0,"HelTec");//��һ�� -- 8x16����ʾ��Ԫ��ʾASCII��
		OLED_P8x16Str(0,2,"OLED Display");
		OLED_P8x16Str(0,4,"www.heltec.cn");
		OLED_P6x8Str(0,6,"cn.heltec@gmail.com");
		OLED_P6x8Str(0,7,"heltec.taobao.com");
		delay(4000);
		OLED_CLS();	 */
//	
//			if(k1==0)		  //��ⰴ��K1�Ƿ���
//	{	
//		delay(100);   //�������� һ���Լ10ms
//		if(k1==0)	 //�ٴ��жϰ����Ƿ���
//		{
//		   
//    	Draw_BMP(0,0,128,8,BMP1);	  //led״̬ȡ��
//		}
//		while(!k1);	 //��ⰴ���Ƿ��ɿ�
//	}		
//		
//		
//	
//		   			if(k2==0)		  //��ⰴ��K1�Ƿ���
//	{	
//		delay(100);   //�������� һ���Լ10ms
//		if(k2==0)	 //�ٴ��жϰ����Ƿ���
//		{
//		
//    		  
//         Draw_BMP(0,0,128,8,BMP2);	  //led״̬ȡ��
//		}
//		while(!k2);	 //��ⰴ���Ƿ��ɿ�
//	}		
//		
//		
//		   			if(k3==0)		  //��ⰴ��K1�Ƿ���
//	{	
//		delay(100);   //�������� һ���Լ10ms
//		if(k3==0)	 //�ٴ��жϰ����Ƿ���
//		{
//		
//    		
//         Draw_BMP(0,0,128,8,BMP3);	  //led״̬ȡ��
//		}
//		while(!k3);	 //��ⰴ���Ƿ��ɿ�
//	}	
//	  	   			if(k4==0)		  //��ⰴ��K1�Ƿ���
//	{	
//		delay(100);   //�������� һ���Լ10ms
//		if(k4==0)	 //�ٴ��жϰ����Ƿ���
//		{
//		
//    		  
//         Draw_BMP(0,0,128,8,BMP4);	  //led״̬ȡ��
//		}
//		while(!k4);	 //��ⰴ���Ƿ��ɿ�
//	}		
//	
//}

//}
