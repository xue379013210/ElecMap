/**************************************************************************************/
/*                                                                                    */
/*         文件名   ：sort.cpp                                                        */
/*                                                                                    */
/*         文件说明 ：对已读取的信息进行排序					                          */
/*                                                                                    */
/*         作者     ：wxy                                                             */
/*                                                                                    */
/*         日期     ：2014年2月13日                                                   */
/*                                                                                    */
/**************************************************************************************/

#include "header.h"

void sort(Infor **infor, int ArrSize, int SortType);  //排序接口

void QuickSort(Infor **infor, int head, int tail);  //快速排序
void BubbleSort(Infor **infor, int N);  //冒泡排序
void InsertSort(Infor **infor, int N);  //插入排序
void SelectSort(Infor **infor, int N);  //选择排序

clock_t start_time, end_time;  //时间函数，用来统计排序所用时间

/****************************************************/
/*函数名   : sort_menu				                */
/*函数功能 : 提供排序功能的操作界面，选择排序关键字	*/
/*			 和排序方式					            */
/****************************************************/

//排序菜单
void sort_menu(Infor **infor)
{
	if(NULL == infor)
		return;

	//判断文件是否已经读取
	if(0 == (*infor)->num)  
	{	
		system("cls");
		menu1();
		printf("/*****************************************************************************/");
		printf("\n\t\t     还未读取文件，请先读取文件再进行排序!\n");
		printf("/*****************************************************************************/\n\n");
		return;
	}

	//判断文件是否已经排序
	if(1 == (*infor)->sorted)
	{
		system("cls");
		menu1();
		printf("/*****************************************************************************/");
		printf("\n\t\t            文件已经排序成功!\n");
		printf("/*****************************************************************************/\n\n");
		return;
	}

	//已经读取则可进行排序
	int choice1 = 0;  //功能选择键
	char choice2 = '\0';  //确认键
	while(1)
	{
		printf("\n\t 请选择排序方法\n");
		printf("\t\t  1.快速排序\n\t\t  2.冒泡排序\n\t\t  3.插入排序\n\t\t  4.选择排序\n\t\t  0.返回\n\t\t  请选择：");
		fflush(stdin);
		scanf("%d",&choice1);
		if(0 != choice1)  //不选0继续
		{	
			if((choice1 > 0) && (choice1 <= 4))
			{
				printf("排序中···\n请稍等···\n");

				start_time=clock();  //开始排序时间
				sort(infor, (*infor)->num, choice1);  //排序接口
				end_time=clock();    //结束排序时间

				(*infor)->sorted = 1;  //标志已经排序

				printf("排序中···\n排序成功!\n");
				printf("此次排序共用了%5.2f秒!\n",(double)(end_time-start_time)/1000);
				printf("\n请创建文件(如 Road_Infor,不用加拓展名)：");

				SaveTxt(infor);
				
				return;
			}
			else
			{
				system("cls");
				menu1();
				printf("/*****************************************************************************/");
				printf("\t\t\t        您的输入有误，请重新输入：\n");
				printf("/*****************************************************************************/\n\n");
				menu2();
				printf("\n");
			}
		}
		else  //选0返回上一层
		{
			printf("\t 返回上一层？（y=yes,n=no）:");
			fflush(stdin);
			scanf("%c",&choice2);
			if('y'==choice2)
			{
				system("cls");
				menu1();
				break;
			}
		}
	}
}

//排序接口
void sort(Infor **infor, int ArrSize, int SortType)
{
	if((NULL == infor) || (ArrSize < 0))
		return;

	switch(SortType)
	{
	case 1:
		QuickSort(infor, 0, ArrSize-1);  //快速排序
		break;
	case 2:
		BubbleSort(infor, ArrSize);  //冒泡排序
		break;
	case 3:
		InsertSort(infor, ArrSize);  //插入排序
		break;
	case 4:
		SelectSort(infor, ArrSize);  //选择排序
		break;
	default:
		break;
	}
}

/***********************************************************/
/*函数名   : QuickSort，BubbleSort，InsertSort，SelectSort */
/*函数功能 : 分别使用快速、冒泡、插入、选择四种排序方法对  */
/*			 关键字LinkID进行排序				           */
/***********************************************************/

//快速排序
void QuickSort(Infor **infor, int head, int tail)
{
	if(NULL == infor)
		return;

	RoadInfor temp = {0};
	int h = head;
	int t = tail;
	if(head < tail)
	{
		temp = (*infor)->Road[head];
		while(head < tail)
		{
			while((head < tail) && (MC_GET_LONG(&temp.LinkID) < MC_GET_LONG(&(*infor)->Road[tail].LinkID)))
				tail--;
			(*infor)->Road[head] = (*infor)->Road[tail];
			while((head < tail) && (MC_GET_LONG(&temp.LinkID) > MC_GET_LONG(&(*infor)->Road[head].LinkID)))
				head++;
			(*infor)->Road[tail] = (*infor)->Road[head];
		}
		(*infor)->Road[head] = temp;
		QuickSort(infor, h, head-1);
		QuickSort(infor, head+1, t);
	}
}

//冒泡排序
void BubbleSort(Infor **infor, int N)
{
	if(NULL == infor)
		return;

	RoadInfor temp = {0};
	for(int i=1; i<N; ++i)
	{
		for(int j=0; j<N-i; ++j)
		{
			if(MC_GET_LONG(&(*infor)->Road[j].LinkID) > MC_GET_LONG(&(*infor)->Road[j+1].LinkID))
			{
				temp = (*infor)->Road[j];
				(*infor)->Road[j] = (*infor)->Road[j+1];
				(*infor)->Road[j+1] = temp;
			}
		}
	}
}

//插入排序
void InsertSort(Infor **infor, int N)
{
	if(NULL == infor)
		return;

	RoadInfor temp = {0};
	int j = 0;
	for(int i=1; i<N; ++i)
	{
		temp = (*infor)->Road[i];
		j = i-1;
		while((j >= 0) && (MC_GET_LONG(&temp.LinkID) < MC_GET_LONG(&(*infor)->Road[j].LinkID)))
		{
			(*infor)->Road[j+1] = (*infor)->Road[j];
			j--;
		}
		(*infor)->Road[j+1] = temp;
	}
}

//选择排序
void SelectSort(Infor **infor, int N)
{
	if(NULL == infor)
		return;

	RoadInfor temp = {0};
	for(int i=0; i<N-1; ++i)
	{
		for(int j=i+1; j<N; ++j)
		{
			if(MC_GET_LONG(&(*infor)->Road[i].LinkID) > MC_GET_LONG(&(*infor)->Road[j].LinkID))
			{
				temp = (*infor)->Road[j];
				(*infor)->Road[j] = (*infor)->Road[i];
				(*infor)->Road[i] = temp;
			}
		}
	}
}