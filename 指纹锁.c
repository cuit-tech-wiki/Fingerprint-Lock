#include <STC12C5A60S2.H>
#include <string.h>
#include "codetab.h"
#include "LQ12864.h"
#include "24C0x.h"		  //包含24C02函数
#define uchar unsigned char
#define uint unsigned int	 //宏定义
#define buffer1ID  0x01
#define buffer2ID  0x02
sbit k2=P3^3;				//指纹模块
sbit jidianqi=P3^2;	//舵机
uint PageID;     
uchar data querenma=11;
uchar sum[2];
uchar grade[4];
uchar Gradezw;
uchar ID[4];
uchar IDzw;
uchar mimaID[7]={'5','5','5','5','5','5'};
uchar mima[7];
uchar cDuty=5;
int summaf,summas;
void UartInit(void)		//9600bps@11.0592MHz
{
		PCON=0X00;
		TMOD = 0x21;
		SCON = 0x50;	// =0x50;????1,REN=1										(????)
		TL1  = TH1  = -3;	// ???9600bps								(11.0592M??,???960)
		TR1  = 1;		// ??T1
		TH0=-92>>8;
		TL0=-92;
		TR0=1;
		ET0=1;
    EA=1;
}

void delayms(uint z)    /*毫秒延时函数*/
  {
    uint i,j;
		
		for(j=z;j>0;j--)
		{
    for(i=200;i>0;i--);
		for(i=102;i>0;i--);	
		}
	}
void SFG_getimage()			      //录入指纹图像
{
   uchar i;
   SBUF=0xef;
   while(TI==0);
   TI=0;
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0X03;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   summaf=0x05;
   SBUF=summaf;
   while(TI==0);
   TI=0;
        
   for(i=0;i<9;i++)
   {
    while(RI==0);
    RI=0;}
        
   while(RI==0);
   RI=0;
   querenma=SBUF;
		
   while(RI==0);
   RI=0;
   sum[1]=SBUF;
   while(RI==0);
   RI=0;
   sum[0]=SBUF;
   summas=(sum[1]<<8)+sum[0];									 
}
        
void SFG_genchar(uchar bufferID) //生成特征并存于charbuffer1/2  调用后单片机波特率变化@@@
{
   uchar i;
   SBUF=0xef;
   while(TI==0);
   TI=0;
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0X04;
   while(TI==0);
   TI=0;
        
   SBUF=0X02;
   while(TI==0);
   TI=0;
        
   SBUF=bufferID;
   while(TI==0);
   TI=0;
        
   summaf=0x07+bufferID;
//   sum[0]=summaf;
//   sum[1]=summaf>>8;
   SBUF=0x00;
   while(TI==0)
   TI=0;
   SBUF=summaf;
   while(TI==0)
   TI=0;
	 
   for(i=0;i<9;i++)
   {
    while(RI==0);
    RI=0;}
   while(RI==0);
   RI=0;
   querenma=SBUF;
   while(RI==0);
   RI=0;
   sum[1]=SBUF;
   while(RI==0);
   RI=0;
   sum[0]=SBUF;
   summas=(sum[1]<<8)+sum[0];									 
}

void SFG_fastsearch(uchar bufferID)  //搜索指纹返回指纹ID号   sum、pagenum>255都会使程序卡@@@
{
   uchar i,ID1, ID2;
   SBUF=0xef;
   while(TI==0);
   TI=0;
   SBUF=0X01;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0X08;
   while(TI==0);
   TI=0;
        
   SBUF=0X1b;
   while(TI==0);
   TI=0;
        
   SBUF=bufferID;
   while(TI==0);
   TI=0;
        
   SBUF=0x00;
   while(TI==0);
   TI=0;
   SBUF=0x00;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0x0a; 
   while(TI==0);
   TI=0;
        
   summaf=9+0x1b+bufferID+0x0a;
   sum[0]=summaf>>8;
   sum[1]=summaf;

	 SBUF=sum[0];
   while(TI==0);
   TI=0;
   SBUF=sum[1];
   while(TI==0);
   TI=0;
   
   for(i=0;i<9;i++)
   {
    while(RI==0);
    RI=0;}
	        
   while(RI==0);
   RI=0;
   querenma=SBUF;
   while(RI==0);
   RI=0;
   ID1=SBUF;
   while(RI==0);
   RI=0;
   ID2=SBUF;				  //接收到的ID号
   while(RI==0);
   RI=0;
	 grade[1]=SBUF;
	 
   while(RI==0);
   RI=0;
   grade[0]=SBUF;   
	 Gradezw=(grade[1]<<8)+grade[0];
   while(RI==0);
   RI=0;
   sum[1]=SBUF;
   while(RI==0);
   RI=0;
   sum[0]=SBUF;
   summas=(sum[1]<<8)+sum[0];									 
   //PageID=ID1;
   PageID=(ID1<<8)+ID2;
	 
}
        


/*void SFG_enroll()				 //自动注册模板返回存储ID  =录图像+合并生成模板+储存模板
{
   uchar i,ID1,ID2;
   SBUF=0xef;
   while(TI==0);
   TI=0;
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0X03;
   while(TI==0);
   TI=0;
        
   SBUF=0X10;
   while(TI==0);
   TI=0;
           
   SBUF=0X00;
   while(TI==0);
   TI=0;
   summaf=0x14;
   SBUF=summaf;	   //校验和
   while(TI==0);
   TI=0;
        
   for(i=0;i<9;i++)
   {
    while(RI==0);
    RI=0;}
   while(RI==0);
   RI=0;
   querenma=SBUF;
   while(RI==0);
   RI=0;
   ID1=SBUF;
   while(RI==0);
   RI=0;
   ID2=SBUF;
        
   while(RI==0);
   RI=0;
   sum[1]=SBUF;
   while(RI==0);
   RI=0;
   sum[0]=SBUF;
   summas=(sum[1]<<8)+sum[0];									 
   //PageID=ID1;
   PageID=(ID1<<8)+ID2;
}/*/
void SFG_deletchar(uchar page)   //删除指纹		     校验和在2字节的页码处应分高低字节相加
{
   uchar i;
   SBUF=0xef;
   while(TI==0);
   TI=0;
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0X07;
   while(TI==0);
   TI=0;
        
   SBUF=0X0c;
   while(TI==0);
   TI=0;
        
   
   SBUF=0;
   while(TI==0);
   TI=0;
   SBUF=page;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=1;
   while(TI==0);
   TI=0;
        
   summaf=0x15+page;
   sum[0]=summaf;
   sum[1]=summaf>>8;
   SBUF=sum[1];
   while(TI==0);
   TI=0;
   SBUF=sum[0];
   while(TI==0);
   TI=0;
  
   for(i=0;i<9;i++)
   {
    while(RI==0);
    RI=0;}
   while(RI==0);
   RI=0;
   querenma=SBUF;
   while(RI==0);
   RI=0;
   sum[1]=SBUF;
   while(RI==0);
   RI=0;
   sum[0]=SBUF;
   summas=(sum[1]<<8)+sum[0];									 
}
    
void SFG_identify()				//自动验证指纹     录图像+生成特征+搜索
{
   uchar i,ID1,ID2; 
   SBUF=0xef;
   while(TI==0);
   TI=0;
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0X03;
   while(TI==0);
   TI=0;
        
   SBUF=0X11;
   while(TI==0);
   TI=0;
           
   SBUF=0X00;
   while(TI==0);
   TI=0;
   summaf=0x15;
   SBUF=summaf;	   //校验和
   while(TI==0);
   TI=0;
        
   for(i=0;i<9;i++)
   {
    while(RI==0);
    RI=0;}
   while(RI==0);
   RI=0;
   querenma=SBUF;
   while(RI==0);
   RI=0;
   ID1=SBUF;
   while(RI==0);
   RI=0;
   ID2=SBUF;
        
   while(RI==0);
   RI=0;
	 grade[1]=SBUF;
	 
   while(RI==0);
   RI=0;
   grade[0]=SBUF;   
	 Gradezw=(grade[1]<<8)+grade[0];
        
   while(RI==0);
   RI=0;
   sum[1]=SBUF;
   while(RI==0);
   RI=0;
   sum[0]=SBUF;
   summas=(sum[1]>>8)+sum[0];									 
//   PageID=ID1;
   PageID=(ID1>>8)+ID2;
}
void PS_Match()			      
{
   uchar i;
   SBUF=0xef;
   while(TI==0);
   TI=0;
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0X03;
   while(TI==0);
   TI=0;
        
   SBUF=0X03;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   summaf=0x07;
   SBUF=summaf;
   while(TI==0);
   TI=0;
        
   for(i=0;i<9;i++)
   {
    while(RI==0);
    RI=0;}
        
   while(RI==0);
   RI=0;
   querenma=SBUF;
		 while(RI==0);
   RI=0;
		 while(RI==0);
   RI=0;
		 while(RI==0);
   RI=0;
		 while(RI==0);
   RI=0;
 								 
}


void PS_RegModel()
{
   uchar i;
   SBUF=0xef;
   while(TI==0);
   TI=0;
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0X03;
   while(TI==0);
   TI=0;
        
   SBUF=0X05;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   summaf=0x09;
   SBUF=summaf;
   while(TI==0);
   TI=0;
        
   for(i=0;i<9;i++)
   {
    while(RI==0);
    RI=0;}
        
   while(RI==0);
   RI=0;
   querenma=SBUF;
		 while(RI==0);
   RI=0;
		 while(RI==0);
   RI=0;
 								 
}

void PS_Empty()
{
   uchar i;
   SBUF=0xef;
   while(TI==0);
   TI=0;
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0X03;
   while(TI==0);
   TI=0;
        
   SBUF=0X0d;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   
   SBUF=0x11;
   while(TI==0);
   TI=0;
        
   for(i=0;i<9;i++)
   {
    while(RI==0);
    RI=0;}
        
   while(RI==0);
   RI=0;
   querenma=SBUF;
		 while(RI==0);
   RI=0;
		 while(RI==0);
   RI=0;
 								 
}
void PS_StoreChar( uchar BufferID, uchar PageID)
{
	  uchar i;
   SBUF=0xef;
   while(TI==0);
   TI=0;
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
   SBUF=0XFF;
   while(TI==0);
   TI=0;
        
   SBUF=0X01;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   SBUF=0X06;
   while(TI==0);
   TI=0;
	 
    SBUF=0X06;
   while(TI==0);
   TI=0;
	 
   SBUF=BufferID;
   while(TI==0);
   TI=0;
        
   SBUF=0X00;
   while(TI==0);
   TI=0;
   
   SBUF=PageID;
   while(TI==0);
   TI=0;
	 
   summaf=0x01+0x06+0x06+BufferID+PageID;
   SBUF=0x00;
	 while(TI==0);
   TI=0; 
	 
	 SBUF=summaf;
	 while(TI==0);
   TI=0; 
	 
   for(i=0;i<9;i++)
   {
    while(RI==0);
    RI=0;}
        
   while(RI==0);
   RI=0;
   querenma=SBUF;
		 while(RI==0);
   RI=0;
		 while(RI==0);
   RI=0;
}

uchar  KEY_Value(void)				
{
	uchar Keyvalue;
	P0 = 0xf0;
	if(P0 != 0xf0)
	{
		delayms(10);
		if(P0 != 0xf0)
		{
			switch(P0)
			{
				case 0x70: Keyvalue=0;break;
				case 0xb0: Keyvalue=1;break;
				case 0xd0: Keyvalue=2;break;
				case 0xe0: Keyvalue=3;break;
			}
		}
		else
		{
			return 0xff;
		}
	}
	else
	{
		return 0xff;
	}
	P0 = 0x0f;
	{
		if(P0 != 0x0f)
		{
			delayms(10);
			if(P0 != 0x0f)
			{
				switch(P0)
				{
					case 0x0e: Keyvalue+=0;break;
					case 0x0d: Keyvalue+=4;break;
					case 0x0b: Keyvalue+=8;break;
					case 0x07: Keyvalue+=12;break;
				}
				while(P0!=0x0f);
				delayms(10);
				while(P0!=0x0f);
			}
		}
	}
	return Keyvalue;
}
uchar GET_NUM(void)
{
	uchar num=0;
	uchar key_num;
	uchar bb[4];
	bb[3]='\0';
	while(1)
	{
		key_num = KEY_Value();
		if(key_num!=0xff)
		{
			if(key_num==0)num=num*10;//‘0’键	
			if(key_num>0&&key_num<10)//‘1-9’键(限制输入3位数)
			num =num*10+key_num;	
			if(key_num==14)num =num/10;//‘DEL’键
			if(key_num==15)return num;  //‘Enter’键
		}
		bb[0]='0';
		bb[1]=num/10+'0';
		bb[2]=num%10+'0';
		OLED_P8x16Str(0,6,"ID:");
		OLED_P8x16Str(24,6,bb);
	}

}
void GET_MIMA(void)
{
	uchar i=0;
	uchar key_num;
	while(1)
	{
		key_num = KEY_Value();
		if(key_num!=0xff)
		{
			if(key_num>=0&&key_num<10 && i<6)//‘1-9’键(限制输入3位数)
			{
				mima[i]=key_num+'0';
				if(i!=5)i++;
			}
			if(key_num==14)
			{
				mima[i]='0';
				if(i) i--;
			}//‘DEL’键
			if(key_num==15) return;  //‘Enter’键
		}
		OLED_P8x16Str(0,6,"MIMA:");
		OLED_P8x16Str(40,6,mima);
	}

}
void addfinger(void)
{
	uchar i=0, processnum=0;
	while(1)
	{
	switch(processnum)
	{
		case 0:
			i++;
			OLED_CLS();
			OLED_P8x16Str(0,0,"put your fingers");
			while(!k2);
			SFG_getimage();
		 if(querenma==0)
		 {
			SFG_genchar(buffer1ID);
			UartInit();
			 if(querenma==0)
			 {
				OLED_P8x16Str(0,2,"the fingerprint is normal");
				i=0;
				SFG_fastsearch(buffer1ID);
				if(querenma==0)
				{
					OLED_CLS();
					OLED_P8x16Str(0,0,"The fingerprint has been stored");
					i=5;
				}
				else if(querenma==9)
				{
					OLED_CLS();
					i=0;
					processnum=1;
					OLED_P8x16Str(0,0,"please loosen your fingers");
					while(k2==1);
				}
			 }
			 else
			 {
				 OLED_P8x16Str(0,2,"error");
				 delayms(1000);
			 }
		 }
		 else
		 {
			 OLED_P8x16Str(0,2,"error");
			 delayms(2000);
		 }
		 break;

			
		case 1:
			i++;
			OLED_CLS();
			OLED_P8x16Str(0,2,"heavy press fingers");
			while(!k2);
			SFG_getimage();
			SFG_genchar(buffer2ID);
			UartInit();
			if(querenma==0)
			{
				OLED_CLS();
				OLED_P8x16Str(0,4,"the fingerprint is normal");
				i=0;
				processnum=2;
			}
			else
			{
				OLED_CLS();
				OLED_P8x16Str(0,4,"error");
				delayms(1000);
			}
   		break;
			
		case 2:
			OLED_CLS();
			OLED_P8x16Str(0,0,"compare the two fingerprints");
			PS_Match();
			if(querenma==0x00) 
			{
				OLED_CLS();
				OLED_P8x16Str(0,0,"compare the successful");
				processnum=3;//跳到第四步
				delayms(1000);
			}
			else 
				{
					OLED_CLS();
					OLED_P8x16Str(0,0,"compare the failure,heavy press fingers");
					i=0;
					processnum=0;//跳回第一步		
				}
				delayms(2000);
				break;
			
		case 3:
				OLED_CLS();
				OLED_P8x16Str(0,0,"generate fingerprint module");
				PS_RegModel();
				if(querenma==0x00) 
				{
					
					OLED_P8x16Str(0,4,"fingerprint module is OK");
					processnum=4;//跳到第五步
					delayms(1000);
				}
				else 
				{
					processnum=0;
					OLED_CLS();
					OLED_P8x16Str(0,0,"fingerprint module is OK");
					delayms(2000);
				}
				break;
				
		case 4:	
				OLED_CLS();
				OLED_P8x16Str(0,0,"please enter the save ID(0=< ID <=9)");
				
				do
					IDzw=GET_NUM();
					
				while(!(IDzw<10));//输入ID必须小于模块容量最大的数值
				UartInit();
				if(IDzw==11) return;  //返回主页面
				PS_StoreChar(buffer2ID,IDzw);//储存模板
				if(querenma==0x00) 
				{
					OLED_CLS();				
					OLED_P8x16Str(0,0,"fingerprint input successful");
					delayms(1000);
					return ;
				}
				else 
				{
					processnum=0;
					OLED_CLS();
					OLED_P8x16Str(0,0,"error");
				}					
				break;				
		}
		delayms(400);
		if(i==5)//超过5次没有按手指则退出
		{
			OLED_CLS();
			break;
		}
	}
}


void press_FR(void)
{
		SFG_identify();
		if(querenma==0)
		{
			if(Gradezw>100)
			{
			OLED_CLS();
			switch(PageID)
			{
				case 0:
					OLED_P8x16Str(0,0,"welcome YTG home");
				break;
				case 1:
					OLED_P8x16Str(0,0,"welcome JYJ home");
				break;
				case 2:
					OLED_P8x16Str(0,0,"welcome LJQ home");
				break;
				case 3:
					OLED_P8x16Str(0,0,"welcome WSY home");
				break;
				case 4:
					OLED_P8x16Str(0,0,"welcome RJX home");
				break;
				case 5:
					OLED_P8x16Str(0,0,"welcome LP home");
				break;
			}
			grade[0]=Gradezw/100+'0';
			grade[1]=Gradezw/10%10+'0';
			grade[2]=Gradezw%10+'0';
			grade[3]='\0';
			OLED_P8x16Str(0,2,"grade:");
			OLED_P8x16Str(48,2,grade);
			OLED_P8x16Str(0,4,"open the door");
			cDuty=25;
			delayms(5000);
			cDuty=5;
			while(k2);
			}
			else
			{
				OLED_CLS();
				OLED_P8x16Str(0,0,"too low match");
				grade[0]=Gradezw/100+'0';
				grade[1]=Gradezw/10%10+'0';
				grade[2]=Gradezw%10+'0';
				grade[3]='\0';
				OLED_P8x16Str(0,2,"grade:");
				OLED_P8x16Str(48,2,grade);
				OLED_P8x16Str(0,4,"please loosen your fingers");
				delayms(1000);
				while(k2==1);
			}
		}
		else
		{
			OLED_CLS();
			OLED_P8x16Str(0,2,"please loosen your fingers");
			delayms(1000);
			while(k2==1);
			OLED_CLS();
			OLED_P8x16Str(0,2,"heavy press fingers");
		}
}
	
void deletfinger()      //删除用户指纹
{
	uchar Del_ID;
	OLED_CLS();
	OLED_P8x16Str(0,0,"Enter the deleted ID");
	delayms(50);
	do
					Del_ID=GET_NUM();
					
				while(!(Del_ID<12));//输入ID必须小于模块容量最大的数值
	if(Del_ID==11) return;
	else if(Del_ID==10)
	{
		PS_Empty();
		if(querenma==0)
		{
			OLED_CLS();
			OLED_P8x16Str(0,0,"empty fingerprints");
			delayms(2000);
		}
		else
		{
			OLED_CLS();
			OLED_P8x16Str(0,0,"error");
		}
	}
	else if(Del_ID<10)
	{
	SFG_deletchar(Del_ID);
	if(querenma==0)
	{
		OLED_CLS();
		OLED_P8x16Str(0,0,"the fingerprint has been deleted"); 
	}
	else
	{
		OLED_CLS();
		OLED_P8x16Str(0,0,"delete failed");  
		
	}
	OLED_P8x16Str(2,0,"press any key to continue"); 
	while(KEY_Value()==0);
	OLED_CLS();
	}
}

void guanliyuan()       //管理员
{
	uchar K;
	uchar i;
 	uchar Right_flag;
  OLED_CLS();
	OLED_P8x16Str(0,0,"please enter the password");	
	mima[6]='\0';
	for(i=0;i<6;i++)mima[i]='0';
	GET_MIMA();
	if(strcmp(mimaID, mima)==0)
	{
		Right_flag=1;
	}
	else Right_flag=0;
  OLED_CLS();
	
	if(Right_flag)
	{
	K=KEY_Value();
  while(K!=15)
   {
		OLED_P8x16Str(0,0,"key1: add a fingerprint"); 
		OLED_P8x16Str(0,4,"key2: delete a fingerprint");
		K=KEY_Value();  
	    switch(K)
	    {
	     case 1:    addfinger();     break;
	     case 2:    deletfinger();   break;
	     default: break;
	    }
   }
	}
  else
  {
		OLED_P8x16Str(0,0,"password mistake");
		OLED_P8x16Str(0,2,"press any key to continue"); 
	  while(KEY_Value()==0xff);
  }
  OLED_CLS();
}

void MENU()
{
	uchar KEY;
	OLED_P8x16Str(0,0,"welcome to 4022");
	OLED_P8x16Str(0,2,"press your finger to enter");
  KEY=KEY_Value();
if(k2==1)		//指纹刷机
  {
  OLED_CLS();
	press_FR();
	OLED_CLS();
  }
  if(KEY==15)			//管理员操作
  {
	OLED_CLS();
	guanliyuan();
  OLED_CLS();
  }

}	
void main()
{	

	 UartInit();	   //串口初始化
	 OLED_Init();
	 OLED_CLS();
	 while(1)
	 {
			MENU();	  
	 }

}

void Timer0() interrupt 1
{
	static int i;
	TH0=-92>>8;
	TL0=-92;
	i++;
	if(i<=cDuty)
	{
		jidianqi=1;
	}
	else
	{
		jidianqi=0;
	}
	if(i>=200) i = 0;
	
}