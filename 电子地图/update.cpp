/**************************************************************************************/
/*                                                                                    */
/*         文件名   ：update.cpp                                                      */
/*                                                                                    */
/*         文件说明 ：将整理好的数据(已经读取并排序好)存放在新生成的.dat文件下  		  */
/*                                                                                    */
/*         作者     ：wxy                                                             */
/*                                                                                    */
/*         日期     ：2014年2月14日                                                   */
/*                                                                                    */
/**************************************************************************************/

#include "header.h"

void update(Infor **infor)
{

	if(NULL == infor)
		return;

	if(0 == (*infor)->sorted)  //若数据未处理，返回上一层
	{
		system("cls");
		menu1();
		printf("/*****************************************************************************/");
		printf("\t\t           数据还未进行处理!  请先进行读取、排序!\n");
		printf("/*****************************************************************************/\n\n");
		return;
	}

	FILE *new_file = NULL;

	system("cls");
	menu1();
	printf("/*****************************************************************************/");
	printf("更新中···\n创建文件中···\n创建完毕并进行转存!\n转存中···\n");
	new_file = fopen("SortGTBL.dat","wb"); 

	for(int i=0; i<(*infor)->num; ++i)
	{
		fwrite(&(*infor)->Road[i].Size, 2, 1, new_file);
		fwrite(&(*infor)->Road[i].LinkID, 4, 1, new_file);
		fwrite(&(*infor)->Road[i].R_name_size, 2, 1, new_file);
		fwrite(&(*infor)->Road[i].Entire, 4, 1, new_file);

		//如果信息长度大于12，则有道路名称
		if(MC_GET_SHORT(&(*infor)->Road[i].Size) > 12)
		{
			fwrite((*infor)->Road[i].R_name, MC_GET_SHORT(&(*infor)->Road[i].Size) - 12, 1, new_file);
		}
	}

	printf("排序好的信息已经转存到同目录下的“SortGTBL.dat”文件中!\n");
	printf("更新成功!\n");
	printf("/*****************************************************************************/\n\n");
	fclose(new_file);
}