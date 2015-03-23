/**************************************************************************************/
/*                                                                                    */
/*         文件名   ：main.cpp                                                        */
/*                                                                                    */
/*         文件说明 ：提供电子地图的主操作界面，供用户进行各种操作                       */
/*																				      */
/*         作者     ：wxy                                                             */
/*                                                                                    */
/*         日期     ：2014年2月12日                                                   */
/*                                                                                    */
/**************************************************************************************/

#include "header.h"

void main()
{
	int choice1 = 0;  //功能选择
	char choice2 = '\0';  //确认选择

	Infor *infor = (Infor *)malloc(sizeof(Infor));
	if(NULL == infor)
		return;
	infor->num = 0;  //道路初始0条
	infor->sorted = 0;  //0表示未排序，1表示已经排序

	menu1();
	while(1)
	{
		menu2();
		fflush(stdin);
		scanf("%d",&choice1);
		while(0 != choice1)
		{
			switch(choice1)
			{
			case 1:
				read(&infor);
				break;
			case 2:
				sort_menu(&infor);
				break;
			case 3:
				search_menu(&infor);
				break;
			case 4:
				update(&infor);
				break;
			default:
				system("cls");
				menu1();
				printf("/*****************************************************************************/");
				printf("\t\t\t        您的输入有误，请重新输入：\n");
				printf("/*****************************************************************************/\n\n");
				break;
			}
			menu2();
			fflush(stdin);
			scanf("%d",&choice1);
		}
		printf("\t 是否确认退出？（y=yes,n=no）:");
		fflush(stdin);
		scanf("%c",&choice2);
		if('y'==choice2)
		{
			free(infor);
			infor = NULL;
			printf("\n\t 感谢您使用本产品!\n\n");
			exit(0);
		}
		else
			printf("\n");
	}
}

void menu1()
{
	printf("/☆☆☆☆☆☆☆☆☆☆☆☆☆---Welcome!---☆☆☆☆☆☆☆☆☆☆☆☆☆/\n");
	printf("/☆☆                                                          ☆☆/\n");
	printf("/☆☆                   电子地图信息统计系统                   ☆☆/\n");
	printf("/☆☆                                                          ☆☆/\n");
	printf("/☆☆                    王小宇 2013年8月5日                   ☆☆/\n");
	printf("/☆☆                                                          ☆☆/\n");
	printf("/☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆/\n\n");
}

void menu2()
{
	printf("请选择服务的种类：\n");
	printf("\t 1.读取文件<“./data/GTBL.dat”>\n");
	printf("\t 2.排序(LinkID)并输出排序结果<“./data/SortGTBL.dat”>\n");
	printf("\t 3.检索\n");
	printf("\t 4.更新（更新前注意对源文件的备份）\n");
	printf("\t 0.退出\n");
	printf("\t 请选择：");
}