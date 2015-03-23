/**************************************************************************************/
/*         文件名   ：header.h					                                      */
/*                                                                                    */
/*         文件说明 ：数据格式转换宏定义，相关结构体定义，函数声明			              */
/*                                                                                    */
/*         作者     ：wxy															  */
/*                                                                                    */
/*         日期     ：2014年2月12日9:25:00                                             */
/**************************************************************************************/

#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

/**********************************数据格式转换宏定义**********************************/
typedef unsigned int UINT;
typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
typedef unsigned long  ULONG;

#define MC_GET_CHAR(__data__)   (*((char *)(__data__)))
#define MC_GET_SHORT(__data__)  ((USHORT)((((USHORT)(*((char *)(__data__))))<<8)|(((USHORT)(*((char *)(__data__)+1)))&0x00ff)))
#define MC_GET_LONG(__data__)   ((((ULONG)MC_GET_SHORT((__data__)))<<16 )|(((ULONG)MC_GET_SHORT((char *)(__data__)+2))&0x0000ffff))

/************************************相关结构体定义************************************/
#define MAXSIZE 65000

#pragma pack(1) //调整结构体边界对齐，以一个字节对齐
typedef struct roadInfor
{
	UINT Skip;  //该条信息相对于文件开头的偏移量
	USHORT Size;  //此条记录的Size
	UINT LinkID;  //道路LinkID
	USHORT R_name_size;  //道路名称的Size
	UINT Entire;  //道路的整体信息(包括番号、岔路数、有无Flag)
	char *R_name;
}RoadInfor;

#pragma pack(1)
typedef struct infor
{
	RoadInfor Road[MAXSIZE];  //存放所有的道路信息
	int num;  //道路总数
	int sorted;  //为1表示已排序，为0表示未排序
}Infor;

/************************************相关函数声明*************************************/
void menu1();  //两个界面函数
void menu2();
void read(Infor **infor);  //读取功能的函数声明
void SaveTxt(Infor **infor);  //将信息写入TXT文档
void sort_menu(Infor **infor);  //排序功能的函数声明
void search_menu(Infor **infor);  //检索功能的函数声明
void update(Infor **infor);  //更新函数的函数声明

#endif