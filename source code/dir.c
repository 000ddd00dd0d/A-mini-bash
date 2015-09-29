/*****************************************/
/*          该函数完成dir功能             */
/*****************************************/
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//比较字符串函数，用于qsort
int comp(const char* *a, const char* *b){
	if(strcmp(*a, *b) == 0) return 0;
	if(strcmp(*a, *b) > 0) return 1;
	if(strcmp(*a, *b) < 0) return -1; 
}

int dir(char *args[], int size){
	DIR *dir;
	struct dirent *ptr;
	char *directors[10000];
	int i;
	if(size == 0){
		int cnt = 0;
		if((dir = opendir(".")) == NULL){
			printf("打开目录失败\n");
			return 0;
		}
		//读取目录内容
		while((ptr = readdir(dir)) != NULL){
			directors[cnt] = (char *)malloc(sizeof(char) * 1000);
			strcpy(directors[cnt++], ptr->d_name);
		}
		//按字典序排序
		qsort(directors, cnt, sizeof(char*), (int(*)(const void*, const void*))comp);
		for(i = 0; i < cnt; i++){
			//输出内容
			printf("%s", directors[i]);
			if((i + 1) % 5 == 0) printf("\n");
			else printf("\t");
			free(directors[i]); //释放内存
		}
		if(cnt % 5) printf("\n");
	}

	for(i = 0; i < size; i++){
		int cnt = 0;
		int j = 0;
		if(size > 1){
			printf("%s:\n", args[i]);
		}
		//打开目录
		if((dir = opendir(args[i])) == NULL){
			printf("打开目录失败\n");
			return 0;
		}

		//读取目录内容
		while((ptr = readdir(dir)) != NULL){
			directors[cnt] = (char *)malloc(sizeof(char) * 1000);
			strcpy(directors[cnt++], ptr->d_name);
		}
		//按字典序排序
		qsort(directors, cnt, sizeof(char*), (int(*)(const void*, const void*))comp);
		for(j = 0; j < cnt; j++){
			//输出内容
			printf("%s", directors[j]);
			if((j + 1) % 5 == 0) printf("\n");
			else printf("\t");
			free(directors[j]); //释放内存
		}
		if(cnt % 5) printf("\n");
		if(i != size - 1) printf("\n");
	}
	return 1;
}