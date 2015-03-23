/**************************************************************************************/
/*                                                                                    */
/*         �ļ���   ��main.cpp                                                        */
/*                                                                                    */
/*         �ļ�˵�� ���ṩ���ӵ�ͼ�����������棬���û����и��ֲ���                       */
/*																				      */
/*         ����     ��wxy                                                             */
/*                                                                                    */
/*         ����     ��2014��2��12��                                                   */
/*                                                                                    */
/**************************************************************************************/

#include "header.h"

void main()
{
	int choice1 = 0;  //����ѡ��
	char choice2 = '\0';  //ȷ��ѡ��

	Infor *infor = (Infor *)malloc(sizeof(Infor));
	if(NULL == infor)
		return;
	infor->num = 0;  //��·��ʼ0��
	infor->sorted = 0;  //0��ʾδ����1��ʾ�Ѿ�����

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
				printf("\t\t\t        ���������������������룺\n");
				printf("/*****************************************************************************/\n\n");
				break;
			}
			menu2();
			fflush(stdin);
			scanf("%d",&choice1);
		}
		printf("\t �Ƿ�ȷ���˳�����y=yes,n=no��:");
		fflush(stdin);
		scanf("%c",&choice2);
		if('y'==choice2)
		{
			free(infor);
			infor = NULL;
			printf("\n\t ��л��ʹ�ñ���Ʒ!\n\n");
			exit(0);
		}
		else
			printf("\n");
	}
}

void menu1()
{
	printf("/��������������---Welcome!---��������������/\n");
	printf("/���                                                          ���/\n");
	printf("/���                   ���ӵ�ͼ��Ϣͳ��ϵͳ                   ���/\n");
	printf("/���                                                          ���/\n");
	printf("/���                    ��С�� 2013��8��5��                   ���/\n");
	printf("/���                                                          ���/\n");
	printf("/����������������������������������/\n\n");
}

void menu2()
{
	printf("��ѡ���������ࣺ\n");
	printf("\t 1.��ȡ�ļ�<��./data/GTBL.dat��>\n");
	printf("\t 2.����(LinkID)�����������<��./data/SortGTBL.dat��>\n");
	printf("\t 3.����\n");
	printf("\t 4.���£�����ǰע���Դ�ļ��ı��ݣ�\n");
	printf("\t 0.�˳�\n");
	printf("\t ��ѡ��");
}