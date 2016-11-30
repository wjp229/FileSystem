#include <stdio.h>
void main(void)
{
	FILE *ifp=fopen("mymkfs.bin", "r");


	if(ifp==NULL)                                      // 파일시스템이 이미 존재하는지 확인
	{
		ifp=fopen("mymkfs.bin", "wb");


		// 아이노드 시간

		struct time{
			int year;
			short month;
			short date;
			short hour;
			short min;
			short sec;
		};


		// 아이노드

		struct inode{
			_Bool ForD;                          // 파일 종류 
			struct time time;                    // 파일 생성 시간     
			long long File_size;                 // 파일 크기           
			short direct;                        // 다이렉트 블록        
			short single;                        // 싱글 인다이렉트 블록  
			short double_indirect;               // 더블 인다이렉트 블록   
		};                                                


		// 파일 데이터

		union file_data{
			unsigned long long sb_inode[8];            // 슈퍼블록 아이노드 리스트
			unsigned long long sb_block[16];           // 슈퍼블록 데이터블록
			struct inode Inode[4];                     // 아이노드 리스트
			unsigned long long indirectinode[16];      // 인다이렉트 아이노드
			char data[128];                            // 일반 데이터
			_Bool i_d;                                 // 인다이렉트 아이노드 or 일반 데이터
		};

		union file_data file[1024]={0};                // 데이터블록 [0]       : 부트블록
		                                               //            [1,2]     : 슈퍼블록
		                                               //            [3~130]    : 아이노드 리스트
		                                               //            [131~1023] : 데이터블록


		//// 데이터블록 : 파일 시스템 정보 이진파일 출력

		// 부트블록 : 0

		fwrite(file[0].data, sizeof(char), sizeof(file[0].data), ifp);


		// 슈퍼블록 : 1 ~ 2

		fwrite(file[1].sb_inode, sizeof(unsigned long long), 8, ifp);         // 슈퍼블록의 아이노드 사용여부 : 1

		fwrite(file[2].sb_block, sizeof(unsigned long long), 16, ifp);         // 슈퍼블록의 데이터블록 사용여부 : 2


		// 아이노드 리스트 : 3 ~ 130

		for(int i=3; i<131; i++)
			fwrite(file[i].Inode, sizeof(struct inode), 4, ifp);



		// 일반 데이터 : 131 ~ 1023 

		for(int i=131; i<1024; i++)
		{
			if(file[i].i_d)
				fwrite(file[i].data, sizeof(char), sizeof(file[i].data), ifp); //파일에 대한 정보 저장
			else
				fwrite(file[i].indirectinode, sizeof(unsigned long long), 16, ifp); //인다렉트 블록일 경우 블록의 주소 저장
		}


		fclose(ifp);
	}
	else
		printf("파일시스템이 이미 존재합니다.");


	return;
}
