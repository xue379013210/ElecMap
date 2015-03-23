/**************************************************************************************/
/*                                                                                    */
/*         �ļ���   ��search.cpp                                                      */
/*                                                                                    */
/*         �ļ�˵�� �������������Ϣ����ĳ�ؼ��ּ���						    		  */
/*                                                                                    */
/*         ����     ��wxy                                                             */
/*                                                                                    */
/*         ����     ��2014��2��14��                                                   */
/*                                                                                    */
/**************************************************************************************/

#include "header.h"

int *search_num = (int *)malloc(sizeof(int)*65000);  //������ż���������Ϣ�±�
int number = 0;  //ÿ������һ�����ϵ���Ϣ��1

void search(Infor **infor, int N, int KeyType, int SearchType, int key_num);  //�����ӿ�
void Print(Infor **infor);  //������������Ϣ��ӡ���

void SeqSearch(Infor **infor, int N, int KeyType, int key_num);  //˳�����
void SeqSearch_LinkID(Infor **infor, int N, int key_num);  //��LinkID����˳�����
void SeqSearch_Class(Infor **infor, int N, int key_num);  //��Class����˳�����
void SeqSearch_cha(Infor **infor, int N, int key_num);  //�Բ�·������˳�����
void search_name(Infor **infor);  //�Ե�·���ƽ���˳�����

void BinarySearch(Infor **infor, int N, int KeyType, int key_num);  //�۰����
void BinarySearch_LinkID(Infor **infor, int N, int key_num);  //��LinkID�����۰����
//void BinarySearch_Class(Infor **infor, int N, int key_num);  //��Class�����۰����
//void BinarySearch_cha(Infor **infor, int N, int key_num);  //�Բ�·�������۰����

/****************************************************/
/*������   : search_menu				            */
/*�������� : �ṩ�������ܵĲ������棬ѡ������ؼ���	*/
/*			 �ͼ�����ʽ					            */
/****************************************************/

//�����˵�
void search_menu(Infor **infor)
{
	if(NULL == infor)
		return;

	//�ж��ļ��Ƿ��Ѿ�����
	if(0 == (*infor)->sorted)
	{
		system("cls");
		menu1();
		printf("/*****************************************************************************/");
		printf("\n\t\t     ��δ�����������������ļ��ٽ��м���!\n");
		printf("/*****************************************************************************/\n\n");
		return;
	}

	//�Ѿ�������ɽ��м���
	int choice1 = 0;  //����ѡ��
	char choice2 = '\0';  //ȷ��ѡ��
	int choice3 = 0;  //����ѡ��
	while(1)
	{
		printf("\n\t ��ѡ������ķ�ʽ��\n");
		printf("\t\t  1.ָ��linkID����\n");
		printf("\t\t  2.ָ��Class���ż���\n");
		printf("\t\t  3.ָ����·������\n");
		printf("\t\t  4.ָ����·���Ƽ���\n");
		printf("\t\t  0.����\n\t ��ѡ��");
		fflush(stdin);
		scanf("%d",&choice1);

		printf("\n\t ��ѡ�������ʽ��\n");
		printf("\t\t  1.˳�����\n");
		printf("\t\t  2.�۰����\n\t ��ѡ��");
		fflush(stdin);
		scanf("%d",&choice3);

		if(0 != choice1)  //��ѡ0����
		{
			if((choice1 > 0) && (choice1 < 4))  //�������š���·����LinkID
			{
				int key_num = -1;  //��Ų�ѯ�Ĺؼ���(���ţ���·����LinkID)

				printf("\n\t ������Ҫ��ѯ�Ĺؼ���:");
				fflush(stdin);
				scanf("%d",&key_num);

				search(infor, (*infor)->num, choice1, choice3, key_num);  //�����ӿ�
				Print(infor);  //��ӡ�������

				return;

			}
			else if(4 == choice1)  //����·��
			{
				search_name(infor);
				Print(infor);
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

//�����ӿ�
void search(Infor **infor, int N, int KeyType, int SearchType, int key_num)
{
	if((NULL == infor) || (N < 0))
		return;

	switch(SearchType)
	{
	case 1:
		SeqSearch(infor, N, KeyType, key_num);  //˳�����
		break;
	case 2:
		BinarySearch(infor, N, KeyType, key_num);  //�۰����
		break;
	default:
		break;
	}
}

/***********************************************************/
/*������   : SeqSearch									   */
/*�������� : ʹ��˳������ķ�������LinkID��Class���š�     */
/*			 ��·�����м���							       */
/***********************************************************/

//˳������ӿ�
void SeqSearch(Infor **infor, int N, int KeyType, int key_num)
{
	if((NULL == infor) || (N < 0) || (key_num < 0) || (KeyType < 0))
		return;

	switch(KeyType)
	{
	case 1:
		SeqSearch_LinkID(infor, N, key_num);
		break;
	case 2:
		SeqSearch_Class(infor, N, key_num);
		break;
	case 3:
		SeqSearch_cha(infor, N, key_num);
		break;
	default:
		break;
	}
}

//LinkID��˳�����
void SeqSearch_LinkID(Infor **infor, int N, int key_num)
{
	if((NULL == infor) || (N < 0) || (key_num < 0))
		return;

	for(int i=0; i<N; ++i)
	{
		if(key_num == MC_GET_LONG(&(*infor)->Road[i].LinkID))
		{
			search_num[number] = i;
			number++;
		}
	}
}

//Class���ŵ�˳�����
void SeqSearch_Class(Infor **infor, int N, int key_num)
{
	if((NULL == infor) || (N < 0) || (key_num < 0))
		return;

	for(int i=0; i<N; ++i)
	{
		if(key_num == (short)((MC_GET_LONG(&(*infor)->Road[i].Entire)<<28)>>28))
		{
			search_num[number] = i;
			number++;
		}
	}
}

//��·����˳�����
void SeqSearch_cha(Infor **infor, int N, int key_num)
{
	if((NULL == infor) || (N < 0) || (key_num < 0))
		return;

	for(int i=0; i<N; ++i)
	{
		if(key_num == (short)((MC_GET_LONG(&(*infor)->Road[i].Entire)<<25)>>29))
		{
			search_num[number] = i;
			number++;
		}	
	}
}

/***********************************************************/
/*������   : BinarySearch								   */
/*�������� : ʹ���۰�����ķ�������LinkID��Class���š�     */
/*			 ��·�����м���							       */
/***********************************************************/

//�۰�����ӿ�
void BinarySearch(Infor **infor, int N, int KeyType, int key_num)
{
	if((NULL == infor) || (N < 0) || (key_num < 0) || (KeyType < 0))
		return;

	switch(KeyType)
	{
	case 1:
		BinarySearch_LinkID(infor, N, key_num);
		break;
	case 2:
		SeqSearch_Class(infor, N, key_num);
		break;
	case 3:
		SeqSearch_cha(infor, N, key_num);
		break;
	default:
		break;
	}
}

//LinkID���۰����
void BinarySearch_LinkID(Infor **infor, int N, int key_num)
{
	if((NULL == infor) || (N < 0) || (key_num < 0))
		return;

	int low = 0;
	int high = N-1;
	int mid = 0;

	while(low <= high)
	{
		mid = (low + high)/2;

		if(key_num == MC_GET_LONG(&(*infor)->Road[mid].LinkID))
		{
			search_num[number] = mid;
			number++;
			return;
		}
		else if(key_num >  MC_GET_LONG(&(*infor)->Road[mid].LinkID))
			low = mid + 1;
		else 
			high = mid - 1;
	}
}

/***********************************************************/
/*������   : search_name								   */
/*�������� : ʹ��˳����ҶԵ�·���ƽ��м���				   */
/***********************************************************/

void search_name(Infor **infor)
{
	if(NULL == infor)
		return;

	char key_name[30] = {0};

	printf("������Ҫ���ҵĵ�·���ƣ�");
	fflush(stdin);
	scanf("%s",key_name);

	for(int i=0; i<(*infor)->num; ++i)
	{
		if(12 == MC_GET_SHORT(&(*infor)->Road[i].Size))
			continue;
		else
		{
			if(!strcmp(key_name, (*infor)->Road[i].R_name))
			{
				search_num[number] = i;
				number++;
			}
		}
	}
}

/***********************************************************/
/*������   : Print										   */
/*�������� : �Լ���������Ϣ���д�ӡ���������������٣�ֱ��*/
/*			 ͨ������̨���������϶࣬���ӡ��TXT�ĵ���   */
/***********************************************************/

//�����ҽ������̨�������TXT���
void Print(Infor **infor)
{
	if(NULL == infor)
		return;

	system("cls");
	menu1();
	printf("/*****************************************************************************/");

	if(0 == number)  //û�м�⵽��Ϣ
	{
		printf("\t\t        û�м�������Ҫ��ѯ����Ϣ!\n");
	}

	else if(number <= 5)  //��⵽��Ϣ����<=5
	{
		printf("������%d����¼�����£�\n\n",number);
		for(int i=0; i<number; ++i)
		{
			printf("��Ϣ��С:%d | linkid:%5d | flag=%d | ��·��:%d | ����:%2d | ",
				MC_GET_SHORT(&(*infor)->Road[search_num[i]].Size), 
				MC_GET_LONG(&(*infor)->Road[search_num[i]].LinkID),
				(short) ( MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)>>7 ),
				(short) ( (MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)<<25)>>29 ),
				(short) ( (MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)<<28)>>28 ));

			//����е�·��
			if(MC_GET_SHORT(&(*infor)->Road[search_num[i]].Size) > 12)
			{
				printf("��·����:%s\n",(*infor)->Road[search_num[i]].R_name);
			}
			else
				printf("�޵�·����!");
		}
	}

	else  //��⵽��Ϣ����>5������TXT�ĵ����
	{
		FILE *write_file = NULL; 
		char str[30] = {0};  //����ļ���

		printf("����������Ϣ��������5��(��%d��)������Ϣת�浽txt�ļ��С�����\n",number);
		printf("/******************************************************************************/\n");
		printf("������Ҫ��ŵ�txt�ļ�����");
		fflush(stdin);
		scanf("%s",str);
		strcat(str,".txt");
		printf("ת���С�����\n");

		write_file = fopen(str,"w");

		for(int i=0; i<number; ++i)
		{
			fprintf(write_file,"��%-4d�� | ��Ϣ��С:%d | linkid:%5d | flag=%d | ��·��:%d | ����:%2d | ",
				i+1, 
				MC_GET_LONG(&(*infor)->Road[search_num[i]].LinkID),
				MC_GET_LONG(&(*infor)->Road[search_num[i]].LinkID),
				(short) ( MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)>>7 ),
				(short) ( (MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)<<25)>>29 ),
				(short) ( (MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)<<28)>>28 ));

			//����е�·��
			if(MC_GET_SHORT(&(*infor)->Road[search_num[i]].Size) > 12)
			{
				fprintf(write_file,"��·����:%s\n",(*infor)->Road[search_num[i]].R_name);
			}
			else
				fprintf(write_file,"�޵�·����!\n");
		}
		fclose(write_file);
		printf("ת��ɹ�!��Ϣ�Ѿ�ת�浽�ļ���%s����\n\n",str);
		number = 0;
		return;
	}
	number = 0;
	printf("/*****************************************************************************/\n\n");
}