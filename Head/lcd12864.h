# ifndef __LCD12864_H__
# define __LCD12864_H__

#include "stc15f2k60s2.h"

//LCD12864����λ����
//LCD12864����λ����
#define   	LCD_PORT    P0
sbit 		RS			=P1^2;		 //�Ĵ���ѡ�� 0:ָ��Ĵ��� 1:���ݼĴ���
sbit 		RW			=P2^0;		 //��д���� 0��д  1����
sbit 		CE			=P2^1;		 //��д����ʹ��   0��ֹͣ 1������

//����˿ڲ���
#define SET  			1		//�ø�
#define CLR 			0		//�õ�

#define RS_Set()		{RS=SET;}		//�˿��ø�
#define RS_Clr()		{RS=CLR;}		//�˿��õ�

#define RW_Set()		{RW=SET;}		//�˿��ø�
#define RW_Clr()		{RW=CLR;}		//�˿��õ�

#define CE_Set()		{CE=SET;}		//�˿��ø�
#define CE_Clr()		{CE=CLR;}		//�˿��õ�

//12864�п�ʼ��ַ
#define 	LINE1 		0x80		 //��һ�е�ַ
#define 	LINE2 		0x90		 //�ڶ��е�ַ
#define 	LINE3 		0x88		 //�����е�ַ
#define 	LINE4 		0x98		 //�����е�ַ

//��������
void LCD12864_WriteCMD(unsigned char cmd);
void LCD12864_WriteDAT(unsigned char dat);
void LCD12864_CheckBusy(void);
void LCD12864_Init(void) ;
void LCD12864_Display(unsigned char addr,unsigned char* pointer);
void LCD12864_Display1(unsigned char addr,unsigned char* pointer);
void  App_FormatDec (unsigned char *pstr, unsigned char value);
void LCD12864_Clear_Line(unsigned char line);

# endif