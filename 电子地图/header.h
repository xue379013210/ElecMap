/**************************************************************************************/
/*         �ļ���   ��header.h					                                      */
/*                                                                                    */
/*         �ļ�˵�� �����ݸ�ʽת���궨�壬��ؽṹ�嶨�壬��������			              */
/*                                                                                    */
/*         ����     ��wxy															  */
/*                                                                                    */
/*         ����     ��2014��2��12��9:25:00                                             */
/**************************************************************************************/

#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

/**********************************���ݸ�ʽת���궨��**********************************/
typedef unsigned int UINT;
typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
typedef unsigned long  ULONG;

#define MC_GET_CHAR(__data__)   (*((char *)(__data__)))
#define MC_GET_SHORT(__data__)  ((USHORT)((((USHORT)(*((char *)(__data__))))<<8)|(((USHORT)(*((char *)(__data__)+1)))&0x00ff)))
#define MC_GET_LONG(__data__)   ((((ULONG)MC_GET_SHORT((__data__)))<<16 )|(((ULONG)MC_GET_SHORT((char *)(__data__)+2))&0x0000ffff))

/************************************��ؽṹ�嶨��************************************/
#define MAXSIZE 65000

#pragma pack(1) //�����ṹ��߽���룬��һ���ֽڶ���
typedef struct roadInfor
{
	UINT Skip;  //������Ϣ������ļ���ͷ��ƫ����
	USHORT Size;  //������¼��Size
	UINT LinkID;  //��·LinkID
	USHORT R_name_size;  //��·���Ƶ�Size
	UINT Entire;  //��·��������Ϣ(�������š���·��������Flag)
	char *R_name;
}RoadInfor;

#pragma pack(1)
typedef struct infor
{
	RoadInfor Road[MAXSIZE];  //������еĵ�·��Ϣ
	int num;  //��·����
	int sorted;  //Ϊ1��ʾ������Ϊ0��ʾδ����
}Infor;

/************************************��غ�������*************************************/
void menu1();  //�������溯��
void menu2();
void read(Infor **infor);  //��ȡ���ܵĺ�������
void SaveTxt(Infor **infor);  //����Ϣд��TXT�ĵ�
void sort_menu(Infor **infor);  //�����ܵĺ�������
void search_menu(Infor **infor);  //�������ܵĺ�������
void update(Infor **infor);  //���º����ĺ�������

#endif