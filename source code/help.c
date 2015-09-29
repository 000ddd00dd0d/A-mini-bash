/********************************************/
/*          该函数完成help功能               */
/********************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern char first[1000]; //readme所在目录

int help(char *args[], int size){
	pid_t pid;
	char readme[1050];
	strcpy(readme, first);
	strcat(readme, "/readme");
	pid = fork();
	if(pid < 0){
		printf("打开文件失败\n");
		return 0;
	}else if(pid == 0){
		if(size == 0){
			//显示整个文件
			char *argv[] = {"more", readme, 0};
			execvp("more", argv);
		}else if(size == 1){
			//查找到第一个出现args[0]的地方
			char pattern[100] = "+/";
			char *argv[] = {"more", 0, readme, 0};
			strcat(pattern, args[0]);
			argv[1] = pattern;
			execvp("more", argv);
		}else{
			//只接受一个参数
			printf("参数太多\n");
		}
		exit(0);
	}else{
		//等待子进程完成后返回
		int *status;
		wait(status);
		return 1;
	}
}