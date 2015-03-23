/**************************************************************************************/
/*                                                                                    */
/*         �ļ���   ��read.cpp                                                        */
/*                                                                                    */
/*         �ļ�˵�� ��1.���ļ����ж�ȡ(��.dat�ļ��ж����������Ѷ���õĽṹ����)	     */
/*                    2.Ȼ�󽫶������ļ�ת����TXT�ļ�						             */
/*                                                                                    */
/*         ����     ��wxy                                                             */
/*                                                                                    */
/*         ����     ��2014��2��12��                                                   */
/*                                                                                    */
/**************************************************************************************/

#include "header.h"

//��ȡ��Ϣ����ṹ��
void read(Infor **infor)
{
	if(NULL == infor)
		return;
	
	//��Դ�ļ�
	FILE *read_file = fopen("GTBL.dat", "rb");  

	printf("��ȡ�ļ�������\n��ȡ�С�����\n");
	
	//��Ĭ��·������ԭʼ�ļ�,���ֶ�����·��
	char path[50] = {0};  
	if(NULL == read_file)  
	{
		printf("�ļ���ȡʧ��!\n�������ֶ������ļ���(��·��):");
		fflush(stdin);
		scanf("%s", path);
		read_file = fopen(path, "rb");
	}

	//ѭ����ȡÿ����Ϣ
	long int i = 0;  //ѭ��++��Ϊ��·��Ϣ������
	UINT skip = 0;  //������Ϣ������ļ�ͷ��ƫ����
	while(1)
	{
		(*infor)->Road[i].Skip = skip;  //������ͷƫ����
		fread(&(*infor)->Road[i].Size, 2, 1, read_file);  //����Size
		if(feof(read_file))    /*�����ļ�������ѭ��*/
			break;
		skip += MC_GET_SHORT(&(*infor)->Road[i].Size);  //ƫ������¼
		fread(&(*infor)->Road[i].LinkID, 4, 1, read_file);  //LinkID
		fread(&(*infor)->Road[i].R_name_size, 2, 1, read_file);  //·��Size
		fread(&(*infor)->Road[i].Entire, 4, 1, read_file);  //������Ϣ(�������š���·��������Flag)

		//�����Ϣ���ȴ���12�����е�·����
		if(MC_GET_SHORT(&(*infor)->Road[i].Size) > 12)
		{
			(*infor)->Road[i].R_name = (char *)malloc((*infor)->Road[i].Size - 12);
			if(NULL == (*infor)->Road[i].R_name)
				return;
			fread((*infor)->Road[i].R_name, MC_GET_SHORT(&(*infor)->Road[i].Size) - 12, 1, read_file);
		}
		else
		{
			(*infor)->Road[i].R_name = NULL;
		}
		
		fseek(read_file, skip, 0);
		i++;
	}

	fclose(read_file);
	(*infor)->num = i;
	printf("�ļ���ȡ�ɹ�!\n����%d����¼!\n\n�봴���ļ�(�� Road_Infor,���ü���չ��)��",i);

	SaveTxt(infor);
}

//ѭ����ÿ����Ϣд��TXT�ĵ�
void SaveTxt(Infor **infor)
{
	FILE *write_file = NULL;

	char str[30] = {0};  //�������ļ���
	fflush(stdin);
	scanf("%s",str);
	strcat(str,".txt");

	system("cls");
	menu1();
	printf("/*****************************************************************************/");
	printf("�����ļ��С�����\n�������!\n��Щ��¼�Ѿ����浽ͬĿ¼�µġ�%s���ļ���!\n",str);
	printf("/*****************************************************************************/\n\n");

	short Flag = -1;  
	short Branch = 0;
	short Class = 0;
	write_file = fopen(str,"w");   /*��Ŀ���ļ�*/
	for(int i=0; i<(*infor)->num; ++i)
	{
		Flag = (short) ( MC_GET_LONG(&(*infor)->Road[i].Entire)>>7 );  //flag
		Branch = (short) ( (MC_GET_LONG(&(*infor)->Road[i].Entire)<<25)>>29 );  //��·��
		Class = (short) ( (MC_GET_LONG(&(*infor)->Road[i].Entire)<<28)>>28 );   //����

		fprintf(write_file, "��%-4d�� | ��Ϣ��С:%d | linkid:%5d | flag=%d | ��·��:%d | ����:%2d | ",
			i+1, MC_GET_SHORT(&(*infor)->Road[i].Size), MC_GET_LONG(&(*infor)->Road[i].LinkID), Flag, Branch, Class);

		//����е�·��
		if(MC_GET_SHORT(&(*infor)->Road[i].Size) > 12)
		{
			fprintf(write_file,"��·����:%s\n",(*infor)->Road[i].R_name);
		}
		else
			fprintf(write_file,"�޵�·����!\n");
	}

	fclose(write_file);
}