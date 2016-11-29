#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"func.h"

int main()
{
	Dir *pRootDir;
	Dir *pCurrentDir;
	pRootDir = (Dir *)malloc(sizeof(Dir));
	pCurrentDir = (Dir *)malloc(sizeof(Dir));
	pRootDir -> pNextDir = NULL;
	pRootDir -> pSimilDir = NULL;
	pRootDir -> pPrevDir = NULL;
	strcpy(pRootDir -> name, "ROOT");
	pCurrentDir = pRootDir;
	while(1)
	{
		int INcase=0;
		printf("[");
		MY_PWD(pRootDir,pCurrentDir);
			printf("]");
		printf("$ ");
		USER_INPUT();
		INcase=CLASSIFY_INCASE();
		switch(INcase)
		{
			case 1 : MY_LS(pCurrentDir);break;
			case 2 : MY_CAT();;break;
			case 3 : MY_SHOWFILE();break;
			case 4 : MY_PWD(pRootDir, pCurrentDir);printf("\n");break;
			case 5 : pCurrentDir = MY_CD(pCurrentDir, Usrbuf1);break;
			case 6 : MY_CP();break;
			case 7 : MY_CPTO();break;
			case 8 : MY_CPFROM();break;
			case 9 : MY_MKDIR(pCurrentDir, Usrbuf1);break;
			case 10 : MY_RMDIR(pCurrentDir, Usrbuf1);break;
			case 11 : MY_RM();break;
			case 12 : MY_MV();break;
			case 13 : MY_TOUCH(pCurrentDir,Usrbuf1);break;
			case 14 : MY_SHOWINODE();break;
			case 15 : MY_SHOWBLOCK();break;
			case 16 : MY_STATE();break;
			case 17 : MY_TREE();break;
			case 18 : return 0;
			case 0 : system(Usrinput);break;//nedd patch
		}
		memset(Usrinput,0,100);
		memset(Usrcmd,0,20);
		memset(Usrbuf1,0,10);
		memset(Usrbuf2,0,10);
		memset(Usrbuf3,0,10);
	}
	return 0;
}
