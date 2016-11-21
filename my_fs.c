#include<stdio.h>
#include<time.h>

void INPUT_TIME(char *current);

typedef struct Block;

union type 
{
	 Block *indirectnode[16];
	 char file[128];
};

typedef struct Block{
	 union type;
}Block;
typedef struct File{

}File;
typedef struct Dir{
	Dir *pPrevDir; //상위 디렉토리
	Dir *pSimilDir;//동위 디렉토리
	Dir *pNextDir;//하위 디렉토리

	File *pFileData;	 
}Dir;
typedef struct{
	 _Bool ForD;
	 char time[20];
	 int File_size;
	 Block *direct;
	 Block *indirect;
	 Block *double_indirect;
}Inode;
int main()
{

}

void INPUT_TIME(char *current){
	struct tm *t;
	time_t timer;
	int len;
	timer = time(NULL);
	t = localtime(&timer);

	len = sprintf(current, "%d",t -> tm_year + 1900);
	*(current + len) = '/';
	len++;
	len += sprintf(current + len, "%d", t -> tm_mon + 1);
	*(current + len) = '/';
	len++;
	len += sprintf(current + len, "%d", t -> tm_mday);
	*(current + len) = ' ';
	len++;
	len += sprintf(current + len, "%d", t -> tm_hour);
	*(current + len) = ':';
	len++;
	len += sprintf(current + len, "%d", t -> tm_min);
	*(current + len) = ':';
	len++;
	len += sprintf(current + len, "%d", t -> tm_sec);
}
