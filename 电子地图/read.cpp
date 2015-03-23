/**************************************************************************************/
/*                                                                                    */
/*         文件名   ：read.cpp                                                        */
/*                                                                                    */
/*         文件说明 ：1.对文件进行读取(从.dat文件中读出，放入已定义好的结构体中)	     */
/*                    2.然后将二进制文件转换成TXT文件						             */
/*                                                                                    */
/*         作者     ：wxy                                                             */
/*                                                                                    */
/*         日期     ：2014年2月12日                                                   */
/*                                                                                    */
/**************************************************************************************/

#include "header.h"

//读取信息存入结构体
void read(Infor **infor)
{
	if(NULL == infor)
		return;
	
	//打开源文件
	FILE *read_file = fopen("GTBL.dat", "rb");  

	printf("读取文件···\n读取中···\n");
	
	//若默认路径下无原始文件,则手动输入路径
	char path[50] = {0};  
	if(NULL == read_file)  
	{
		printf("文件读取失败!\n请重新手动输入文件名(含路径):");
		fflush(stdin);
		scanf("%s", path);
		read_file = fopen(path, "rb");
	}

	//循环读取每条信息
	long int i = 0;  //循环++，为道路信息的条数
	UINT skip = 0;  //该条信息相对于文件头的偏移量
	while(1)
	{
		(*infor)->Road[i].Skip = skip;  //此条距头偏移量
		fread(&(*infor)->Road[i].Size, 2, 1, read_file);  //此条Size
		if(feof(read_file))    /*读完文件则跳出循环*/
			break;
		skip += MC_GET_SHORT(&(*infor)->Road[i].Size);  //偏移量记录
		fread(&(*infor)->Road[i].LinkID, 4, 1, read_file);  //LinkID
		fread(&(*infor)->Road[i].R_name_size, 2, 1, read_file);  //路名Size
		fread(&(*infor)->Road[i].Entire, 4, 1, read_file);  //整体信息(包括番号、岔路数、有无Flag)

		//如果信息长度大于12，则有道路名称
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
	printf("文件读取成功!\n共有%d条记录!\n\n请创建文件(如 Road_Infor,不用加拓展名)：",i);

	SaveTxt(infor);
}

//循环将每条信息写入TXT文档
void SaveTxt(Infor **infor)
{
	FILE *write_file = NULL;

	char str[30] = {0};  //用来放文件名
	fflush(stdin);
	scanf("%s",str);
	strcat(str,".txt");

	system("cls");
	menu1();
	printf("/*****************************************************************************/");
	printf("创建文件中···\n创建完毕!\n这些记录已经储存到同目录下的“%s”文件中!\n",str);
	printf("/*****************************************************************************/\n\n");

	short Flag = -1;  
	short Branch = 0;
	short Class = 0;
	write_file = fopen(str,"w");   /*打开目标文件*/
	for(int i=0; i<(*infor)->num; ++i)
	{
		Flag = (short) ( MC_GET_LONG(&(*infor)->Road[i].Entire)>>7 );  //flag
		Branch = (short) ( (MC_GET_LONG(&(*infor)->Road[i].Entire)<<25)>>29 );  //岔路数
		Class = (short) ( (MC_GET_LONG(&(*infor)->Road[i].Entire)<<28)>>28 );   //番号

		fprintf(write_file, "第%-4d条 | 信息大小:%d | linkid:%5d | flag=%d | 岔路数:%d | 番号:%2d | ",
			i+1, MC_GET_SHORT(&(*infor)->Road[i].Size), MC_GET_LONG(&(*infor)->Road[i].LinkID), Flag, Branch, Class);

		//如果有道路名
		if(MC_GET_SHORT(&(*infor)->Road[i].Size) > 12)
		{
			fprintf(write_file,"道路名称:%s\n",(*infor)->Road[i].R_name);
		}
		else
			fprintf(write_file,"无道路名称!\n");
	}

	fclose(write_file);
}