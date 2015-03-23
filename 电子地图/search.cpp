/**************************************************************************************/
/*                                                                                    */
/*         文件名   ：search.cpp                                                      */
/*                                                                                    */
/*         文件说明 ：对已排序的信息进行某关键字检索						    		  */
/*                                                                                    */
/*         作者     ：wxy                                                             */
/*                                                                                    */
/*         日期     ：2014年2月14日                                                   */
/*                                                                                    */
/**************************************************************************************/

#include "header.h"

int *search_num = (int *)malloc(sizeof(int)*65000);  //用来存放检索到的信息下标
int number = 0;  //每检索到一条符合的信息加1

void search(Infor **infor, int N, int KeyType, int SearchType, int key_num);  //检索接口
void Print(Infor **infor);  //将检索到的信息打印输出

void SeqSearch(Infor **infor, int N, int KeyType, int key_num);  //顺序查找
void SeqSearch_LinkID(Infor **infor, int N, int key_num);  //对LinkID进行顺序查找
void SeqSearch_Class(Infor **infor, int N, int key_num);  //对Class进行顺序查找
void SeqSearch_cha(Infor **infor, int N, int key_num);  //对岔路数进行顺序查找
void search_name(Infor **infor);  //对道路名称进行顺序查找

void BinarySearch(Infor **infor, int N, int KeyType, int key_num);  //折半查找
void BinarySearch_LinkID(Infor **infor, int N, int key_num);  //对LinkID进行折半查找
//void BinarySearch_Class(Infor **infor, int N, int key_num);  //对Class进行折半查找
//void BinarySearch_cha(Infor **infor, int N, int key_num);  //对岔路数进行折半查找

/****************************************************/
/*函数名   : search_menu				            */
/*函数功能 : 提供检索功能的操作界面，选择检索关键字	*/
/*			 和检索方式					            */
/****************************************************/

//检索菜单
void search_menu(Infor **infor)
{
	if(NULL == infor)
		return;

	//判断文件是否已经排序
	if(0 == (*infor)->sorted)
	{
		system("cls");
		menu1();
		printf("/*****************************************************************************/");
		printf("\n\t\t     还未进行排序，请先排序文件再进行检索!\n");
		printf("/*****************************************************************************/\n\n");
		return;
	}

	//已经排序则可进行检索
	int choice1 = 0;  //功能选择
	char choice2 = '\0';  //确认选择
	int choice3 = 0;  //功能选择
	while(1)
	{
		printf("\n\t 请选择检索的方式：\n");
		printf("\t\t  1.指定linkID检索\n");
		printf("\t\t  2.指定Class番号检索\n");
		printf("\t\t  3.指定岔路数检索\n");
		printf("\t\t  4.指定道路名称检索\n");
		printf("\t\t  0.返回\n\t 请选择：");
		fflush(stdin);
		scanf("%d",&choice1);

		printf("\n\t 请选择检索方式：\n");
		printf("\t\t  1.顺序检索\n");
		printf("\t\t  2.折半检索\n\t 请选择：");
		fflush(stdin);
		scanf("%d",&choice3);

		if(0 != choice1)  //不选0继续
		{
			if((choice1 > 0) && (choice1 < 4))  //检索番号、岔路数、LinkID
			{
				int key_num = -1;  //存放查询的关键字(番号，岔路数，LinkID)

				printf("\n\t 请输入要查询的关键字:");
				fflush(stdin);
				scanf("%d",&key_num);

				search(infor, (*infor)->num, choice1, choice3, key_num);  //检索接口
				Print(infor);  //打印检索结果

				return;

			}
			else if(4 == choice1)  //检索路名
			{
				search_name(infor);
				Print(infor);
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

//检索接口
void search(Infor **infor, int N, int KeyType, int SearchType, int key_num)
{
	if((NULL == infor) || (N < 0))
		return;

	switch(SearchType)
	{
	case 1:
		SeqSearch(infor, N, KeyType, key_num);  //顺序查找
		break;
	case 2:
		BinarySearch(infor, N, KeyType, key_num);  //折半查找
		break;
	default:
		break;
	}
}

/***********************************************************/
/*函数名   : SeqSearch									   */
/*函数功能 : 使用顺序检索的方法，对LinkID、Class番号、     */
/*			 岔路数进行检索							       */
/***********************************************************/

//顺序检索接口
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

//LinkID的顺序查找
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

//Class番号的顺序查找
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

//岔路数的顺序查找
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
/*函数名   : BinarySearch								   */
/*函数功能 : 使用折半检索的方法，对LinkID、Class番号、     */
/*			 岔路数进行检索							       */
/***********************************************************/

//折半检索接口
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

//LinkID的折半查找
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
/*函数名   : search_name								   */
/*函数功能 : 使用顺序查找对道路名称进行检索				   */
/***********************************************************/

void search_name(Infor **infor)
{
	if(NULL == infor)
		return;

	char key_name[30] = {0};

	printf("请输入要查找的道路名称：");
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
/*函数名   : Print										   */
/*函数功能 : 对检索到的信息进行打印输出，如果条数较少，直接*/
/*			 通过控制台输出，如果较多，则打印到TXT文档中   */
/***********************************************************/

//将查找结果控制台输出或者TXT输出
void Print(Infor **infor)
{
	if(NULL == infor)
		return;

	system("cls");
	menu1();
	printf("/*****************************************************************************/");

	if(0 == number)  //没有检测到信息
	{
		printf("\t\t        没有检索到您要查询的信息!\n");
	}

	else if(number <= 5)  //检测到信息条数<=5
	{
		printf("检索到%d条记录，如下：\n\n",number);
		for(int i=0; i<number; ++i)
		{
			printf("信息大小:%d | linkid:%5d | flag=%d | 岔路数:%d | 番号:%2d | ",
				MC_GET_SHORT(&(*infor)->Road[search_num[i]].Size), 
				MC_GET_LONG(&(*infor)->Road[search_num[i]].LinkID),
				(short) ( MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)>>7 ),
				(short) ( (MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)<<25)>>29 ),
				(short) ( (MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)<<28)>>28 ));

			//如果有道路名
			if(MC_GET_SHORT(&(*infor)->Road[search_num[i]].Size) > 12)
			{
				printf("道路名称:%s\n",(*infor)->Road[search_num[i]].R_name);
			}
			else
				printf("无道路名称!");
		}
	}

	else  //检测到信息条数>5条，用TXT文档输出
	{
		FILE *write_file = NULL; 
		char str[30] = {0};  //存放文件名

		printf("检索到的信息条数大于5条(共%d条)，将信息转存到txt文件中···\n",number);
		printf("/******************************************************************************/\n");
		printf("请输入要存放的txt文件名：");
		fflush(stdin);
		scanf("%s",str);
		strcat(str,".txt");
		printf("转存中···\n");

		write_file = fopen(str,"w");

		for(int i=0; i<number; ++i)
		{
			fprintf(write_file,"第%-4d条 | 信息大小:%d | linkid:%5d | flag=%d | 岔路数:%d | 番号:%2d | ",
				i+1, 
				MC_GET_LONG(&(*infor)->Road[search_num[i]].LinkID),
				MC_GET_LONG(&(*infor)->Road[search_num[i]].LinkID),
				(short) ( MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)>>7 ),
				(short) ( (MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)<<25)>>29 ),
				(short) ( (MC_GET_LONG(&(*infor)->Road[search_num[i]].Entire)<<28)>>28 ));

			//如果有道路名
			if(MC_GET_SHORT(&(*infor)->Road[search_num[i]].Size) > 12)
			{
				fprintf(write_file,"道路名称:%s\n",(*infor)->Road[search_num[i]].R_name);
			}
			else
				fprintf(write_file,"无道路名称!\n");
		}
		fclose(write_file);
		printf("转存成功!信息已经转存到文件“%s”中\n\n",str);
		number = 0;
		return;
	}
	number = 0;
	printf("/*****************************************************************************/\n\n");
}