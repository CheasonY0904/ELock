#include "lcd12864.h"
//������ͷ�ļ���ʹ��_nop_()����
#include <intrins.h>

/***********************************************
�������ƣ�LCD12864_Delay1ms
��    �ܣ�STC 1T��Ƭ��1ms��ʱ����
��ڲ�����ms:��ʱ�ĺ�����
�� �� ֵ����	
��    ע��ʾ����ʵ��1.05ms ʱ��11.0592MHz
************************************************/
void LCD12864_Delay1ms(unsigned int ms)
{
  unsigned int i;
  while( (ms--) != 0)
  {
    for(i = 0; i < 845; i++); 
  }             
}
/*************************************
* �� �� ��: LCD12864_WriteCMD
* ��������: ��lcd12864дָ��
* ��ڲ���: cmd��ָ��
* ��    ��: ��
**************************************/
void LCD12864_WriteCMD(unsigned char cmd)
{
  LCD12864_CheckBusy();
  RS_Clr();
  RW_Clr();
  CE_Set();
  LCD_PORT=cmd;
	_nop_();
	_nop_();
  CE_Clr();
}
/***********************************************
�������ƣ�LCD12864_WriteDAT
��    �ܣ���lcd12864д����
��ڲ�����dat������
�� �� ֵ����	
��    ע����
************************************************/
void LCD12864_WriteDAT(unsigned char dat)
{
  LCD12864_CheckBusy();
  RS_Set();
  RW_Clr();
  CE_Set();
  LCD_PORT=dat;
	_nop_();
	_nop_();
  CE_Clr();
}
/***********************************************
�������ƣ�LCD12864_CheckBusy
��    �ܣ����LCD12864æ�ź�
��ڲ�������
�� �� ֵ����	
��    ע����
************************************************/
void LCD12864_CheckBusy(void)
{
  unsigned char temp=0;
	LCD_PORT=0xff;	 //���������ø�,51ϵ�е�Ƭ����֮ǰ��Ҫ�ø�
  do
	{        
    RS_Clr();
    RW_Set();
    CE_Set();
		_nop_();
		_nop_();
    temp=LCD_PORT;
    CE_Clr();
  }
	while((temp&0x80)!=0);//��λæ��־BF��BF=1��ʾ��æ
}
 /***********************************************
�������ƣ�LCD12864_Init
��    �ܣ�LCD12864��ʼ������
��ڲ�������
�� �� ֵ����	
��    ע������ģʽ
************************************************/
void LCD12864_Init(void)  
{
	//��ʼ��P0��Ϊ׼˫���
	P0M1 =0x00;  
	P0M0 =0x00; 
	
	//��ʼ��P41,P42��Ϊ׼˫���
	P4M1 &=~( (1<<1) | (1<<2) );  
	P4M0 &=~( (1<<1) | (1<<2) ); 
	
	//��ʼ��P37��Ϊ׼˫���
	P3M1 &=~(1<<7);  
	P3M0 &=~(1<<7);  
	
	LCD12864_Delay1ms(100);      		//�ϵ���ʱ100ms
	LCD12864_WriteCMD(0x01);//����
	LCD12864_Delay1ms(10);
	LCD12864_Display(LINE1+1,"�๦�ܵ�����" );		//��һ����ʾ�ַ�
	LCD12864_Display(LINE2+1,"�Զ�������" );		//�ڶ�����ʾ�ַ�
	LCD12864_Display(LINE3+1,"���");		//��������ʾ�ַ�
	LCD12864_Display(LINE4+1,"����");			//��������ʾ�ַ�	
}
/***********************************************
�������ƣ�LCD12864_Clear_Line
��    �ܣ�lcd12864����к���
��ڲ�����line���е�ַ
�� �� ֵ����	
��    ע����
************************************************/
void LCD12864_Clear_Line(unsigned char line)
{
	unsigned char i;
	
	if( (line&LINE4)==LINE4 )	  //�ж��е�ַ���������������
	{
		line=LINE4;	
	}
	else if( (line&LINE3)==LINE3 )
	{
		line=LINE3;	
	}
	else if( (line&LINE2)==LINE2 )
	{
		line=LINE2;	
	}
	else if( (line&LINE1)==LINE1 )
	{
		line=LINE1;	
	}

  LCD12864_WriteCMD(0x30);    //�����趨����λ���䣬����ָ�
  LCD12864_Delay1ms(1);
  LCD12864_WriteCMD(0x0c);	  //��ʾ״̬��������ʾ
  LCD12864_Delay1ms(1);
  LCD12864_WriteCMD(0x06);	  //������趨
  LCD12864_Delay1ms(1);
  LCD12864_WriteCMD(line);	  //�趨DDRAM��ַ
	for(i=0;i<16;i++)
	{
		LCD12864_WriteDAT(' ');	
	}	
}
/***********************************************
�������ƣ�LCD12864_Display
��    �ܣ�д���ֽ��ַ�
��ڲ�����addr����ʼ��ַ��pointerָ���ַ
�� �� ֵ����	
��    ע����ϸ�ĵ�ַ������������ֲ�
************************************************/
void LCD12864_Display(unsigned char addr,unsigned char* pointer)
{
	LCD12864_Clear_Line(addr);	  //�������
	LCD12864_Delay1ms(1);

  LCD12864_WriteCMD(0x30);      //�����趨����λ���䣬����ָ�
  LCD12864_Delay1ms(1);
  LCD12864_WriteCMD(0x0c);	  //��ʾ״̬��������ʾ
  LCD12864_Delay1ms(1);
  LCD12864_WriteCMD(0x06);	  //������趨
  LCD12864_Delay1ms(1);
  LCD12864_WriteCMD(addr);	  //�趨DDRAM��ַ
  while(*pointer!='\0')	      //δ���ַ���ĩβ
  {
  	LCD12864_WriteDAT(*pointer);
	  pointer++;
  }
}
void LCD12864_Display1(unsigned char addr,unsigned char* pointer)
{
	LCD12864_Clear_Line(addr);	  //�������

  LCD12864_WriteCMD(0x30);      //�����趨����λ���䣬����ָ�
  LCD12864_WriteCMD(0x0c);	  //��ʾ״̬��������ʾ
  LCD12864_WriteCMD(0x06);	  //������趨
  LCD12864_WriteCMD(addr);	  //�趨DDRAM��ַ
  while(*pointer!='\0')	      //δ���ַ���ĩβ
  {
  	LCD12864_WriteDAT(*pointer);
	  pointer++;
  }
}
/***********************************************
�������ƣ�App_FormatDec
��    �ܣ���������ת�ַ�������
��ڲ�����value:��������
�� �� ֵ��pstr��ָ���ַ�����ָ�롣	
��    ע����
************************************************/
void  App_FormatDec (unsigned char *pstr, unsigned char value)
{
  unsigned char   i;
  unsigned int   mult; 
  unsigned int   nbr;

  mult  = 1;
	//��Ϊ����Ҫ�����value�����ʽΪ��λ��������123
	//�ʳ�ʼ��mult=100
  for (i = 0; i < 2; i++) 
	{
    mult *= 10;
  }

	i=0;
  while (mult > 0) 
	{
		i++; 
		//��һ����������ȡ���λ���ݣ�����123/100=1
		//����λ����
    nbr = value / mult;
		//����õ������ݲ���0
    if (nbr != 0) 
	  {
			//��������+'0'�����Զ�ת�����ַ����ݣ�����1+'0'������ַ�'1'
      *pstr = nbr + '0';
    } 
	  else
		{   
			//���������0����ֱ��ת�����ַ�'0'           
      *pstr = '0';               
    }
		//�ƶ�ָ�룬��������λ���ݴ���
    pstr++;
    value %= mult;
    mult  /= 10;
  }
}
