/***************************************/
/*    该函数完成myshell提取文件功能      */
/***************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myshell.h"

int myshell(char *args[], int size){
	FILE *fp;
	char command[100];
	char *argv[1000];
	char s[1000];

	if(size == 0){//必须有一个参数
		printf("myshell：没有参数\n");
		return false;
	}

	fp = fopen(args[0], "r");
	if(fp == NULL){
		printf("打开文件失败\n");
		return false;
	}
	while(!feof(fp)){
		//逐行读取指令
		size = read_command(command, argv, fp);
		//判断是否已经读取到文件末尾
		if(size == -1) break;
		//调用指令
		backstage(command, argv, size);
		//释放内存
		clear_command(argv, size);
	}
	fclose(fp);
	return 1;

}