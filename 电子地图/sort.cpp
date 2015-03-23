/**************************************************************************************/
/*                                                                                    */
/*         �ļ���   ��sort.cpp                                                        */
/*                                                                                    */
/*         �ļ�˵�� �����Ѷ�ȡ����Ϣ��������					                          */
/*                                                                                    */
/*         ����     ��wxy                                                             */
/*                                                                                    */
/*         ����     ��2014��2��13��                                                   */
/*                                                                                    */
/**************************************************************************************/

#include "header.h"

void sort(Infor **infor, int ArrSize, int SortType);  //����ӿ�

void QuickSort(Infor **infor, int head, int tail);  //��������
void BubbleSort(Infor **infor, int N);  //ð������
void InsertSort(Infor **infor, int N);  //��������
void SelectSort(Infor **infor, int N);  //ѡ������

clock_t start_time, end_time;  //ʱ�亯��������ͳ����������ʱ��

/****************************************************/
/*������   : sort_menu				                */
/*�������� : �ṩ�����ܵĲ������棬ѡ������ؼ���	*/
/*			 ������ʽ					            */
/****************************************************/

//����˵�
void sort_menu(Infor **infor)
{
	if(NULL == infor)
		return;

	//�ж��ļ��Ƿ��Ѿ���ȡ
	if(0 == (*infor)->num)  
	{	
		system("cls");
		menu1();
		printf("/*****************************************************************************/");
		printf("\n\t\t     ��δ��ȡ�ļ������ȶ�ȡ�ļ��ٽ�������!\n");
		printf("/*****************************************************************************/\n\n");
		return;
	}

	//�ж��ļ��Ƿ��Ѿ�����
	if(1 == (*infor)->sorted)
	{
		system("cls");
		menu1();
		printf("/*****************************************************************************/");
		printf("\n\t\t            �ļ��Ѿ�����ɹ�!\n");
		printf("/*****************************************************************************/\n\n");
		return;
	}

	//�Ѿ���ȡ��ɽ�������
	int choice1 = 0;  //����ѡ���
	char choice2 = '\0';  //ȷ�ϼ�
	while(1)
	{
		printf("\n\t ��ѡ�����򷽷�\n");
		printf("\t\t  1.��������\n\t\t  2.ð������\n\t\t  3.��������\n\t\t  4.ѡ������\n\t\t  0.����\n\t\t  ��ѡ��");
		fflush(stdin);
		scanf("%d",&choice1);
		if(0 != choice1)  //��ѡ0����
		{	
			if((choice1 > 0) && (choice1 <= 4))
			{
				printf("�����С�����\n���Եȡ�����\n");

				start_time=clock();  //��ʼ����ʱ��
				sort(infor, (*infor)->num, choice1);  //����ӿ�
				end_time=clock();    //��������ʱ��

				(*infor)->sorted = 1;  //��־�Ѿ�����

				printf("�����С�����\n����ɹ�!\n");
				printf("�˴���������%5.2f��!\n",(double)(end_time-start_time)/1000);
				printf("\n�봴���ļ�(�� Road_Infor,���ü���չ��)��");

				SaveTxt(infor);
				
				return;
			}
			else
			{
				system("cls");
				menu1();
				printf("/*****************************************************************************/");
				printf("\t\t\t        ���������������������룺\n");
				printf("/*****************************************************************************/\n\n");
				menu2();
				printf("\n");
			}
		}
		else  //ѡ0������һ��
		{
			printf("\t ������һ�㣿��y=yes,n=no��:");
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

//����ӿ�
void sort(Infor **infor, int ArrSize, int SortType)
{
	if((NULL == infor) || (ArrSize < 0))
		return;

	switch(SortType)
	{
	case 1:
		QuickSort(infor, 0, ArrSize-1);  //��������
		break;
	case 2:
		BubbleSort(infor, ArrSize);  //ð������
		break;
	case 3:
		InsertSort(infor, ArrSize);  //��������
		break;
	case 4:
		SelectSort(infor, ArrSize);  //ѡ������
		break;
	default:
		break;
	}
}

/***********************************************************/
/*������   : QuickSort��BubbleSort��InsertSort��SelectSort */
/*�������� : �ֱ�ʹ�ÿ��١�ð�ݡ����롢ѡ���������򷽷���  */
/*			 �ؼ���LinkID��������				           */
/***********************************************************/

//��������
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

//ð������
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

//��������
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

//ѡ������
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