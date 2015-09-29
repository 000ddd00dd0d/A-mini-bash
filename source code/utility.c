/******************************************/
/* 该文件包含4个函数：
/* backstage判断指令中是否包含&，若有则创建子程序使其后台运行
/* redirection判断指令中是否包含<,>,>>,若有则重定向输入输出流
/* status_right判断重定向符号是否符合输入要求
/* judge_utility读取命令并决定命令功能并调用函数，若为外部指令则创建子进程
/******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "myshell.h"
extern jobID;
void backstage(char *command, char *args[], int size){
	int i = 0, j;
	pid_t pid;
	int cnt = 0;

	//查看是否存在&
	for(i = 0; i < size; i++)
		if(strcmp(args[i], "&") == 0)
			break;

	//若没有，则直接调用judge_utility
	if(i == size){
		redirection(command, args, size);
		return;
	}

	//若有，则创建子进程
	pid = fork();
	while(pid < 0){ //若创建子进程失败，则不断创建
		pid = fork();
		cnt++;
		if(cnt >= 100) break;
	}
	if(cnt >= 100){//创建子进程失败
		printf("创建子进程失败！\n");
		return;
	}
	if(pid == 0){
		jobID++;

		//在子进程中调用功能函数
		printf("[%d]%d\n", jobID, getpid());
		redirection(command, args, i);
		printf("[%d]\tDone\t%s", jobID, command);

		//调用完成
		for(j = 0; j < i; j++)
			printf(" %s", args[j]);
		printf("\n");
		jobID--;

		//子进程完成后结束该进程
		exit(0);
	}else{
		if(i == size - 1) return;
		else{
			//截取字符串后递归调用该函数
			backstage(args[i + 1], args + i + 2, size - i - 2);
			return;
		}
	}

}

int status_right(char *args[], int i, int size){
	if(i == size - 1){
		printf("语法错误：在“换行符”附近\n");
		return false;
	}else if(strcmp(args[i + 1], "<") == 0){
		printf("语法错误：在“<”附近\n");
		return false;
	}else if(strcmp(args[i + 1], ">") == 0){
		printf("语法错误：在“>”附近\n");
		return false;
	}else if(strcmp(args[i + 1], ">>") == 0){
		printf("语法错误：在“>>”附近\n");
		return false;
	}else if(strcmp(args[i + 1], "&") == 0){
		printf("语法错误：在“&”附近\n");
		return false;
	}else if(strcmp(args[i + 1], "|") == 0){
		printf("语法错误：在“|”附近\n");
		return false;
	}
	return true;
}

void redirection(char *command, char *args[], int size){
	int i, j;
	int ret, newsize = size;
	int mark = 0;
	struct stat buf;
	char input[256], output[256];
	FILE *fp;
	char *argv[1000];
	char *ptr;

	//复制args
	for(i = 0; i < size; i++)
		argv[i] = args[i];

	//复制输入文件
	//只读取第一个<
	for(i = 0; i < size; i++)
		if(strcmp(args[i], "<") == 0) break;
	if(i != size && status_right(args, i, size)){
		strcpy(input, args[i + 1]);
		//先查看文件是否存在
		ret = stat(input, &buf);
		if(ret == -1){
			printf("%s：没有这个目录或文件\n", input);
			mark = 1;
		}else if(!S_ISREG(buf.st_mode)){
			printf("%s：不是一个普通文件\n", input);
			mark = 1;
		}else{
			fp = fopen(input, "r");
			ptr = (char *)malloc(sizeof(char) * 100000);

			//若文件字符超过100000则不进行操作
			if(fread(ptr, sizeof(char), 100000, fp) >= 100000){
				printf("文件过大\n");
				fclose(fp);
				return;
			}


			//将重定向的输入替换为其内容
			argv[i] = ptr;
			for(i = i + 1; i + 1 < size; i++)
				argv[i] = argv[i + 1];
			newsize--;
			fclose(fp);
		}
	}

	//重定向输出流（覆盖）
	for(i = 0; i < size; i++)
		if(strcmp(args[i], ">") == 0) break;
	if(i != size && status_right(args, i, size)){
		strcpy(output, args[i + 1]);
		//重定向输入流
		freopen(output, "w+", stdout);
		for(; i + 2 < size; i++)
			argv[i] = argv[i + 2];
		newsize -= 2;
	}

	//重定向输出流（不覆盖）
	for(i = 0; i < size; i++)
		if(strcmp(args[i], ">>") == 0) break;
	if(i != size && status_right(args, i, size)){
		strcpy(output, args[i + 1]);
		//重定向输入流
		freopen(output, "a+", stdout);
		for(; i + 2 < size; i++)
			argv[i] = argv[i + 2];
		newsize -= 2;
	}
	
	//调用功能函数
	if(mark == 0){
		judge_utility(command, argv, newsize);
	}

	//恢复输出流
	freopen("/dev/tty", "w", stdout);

}

void judge_utility(char *command, char *args[], int size){
	pid_t pid;
	int i;
	char *argv[1000];
	char value[1050];
	extern char first[1000];

	if(command[0] == '$'){
		showenviron(&command, 1);
		return;
	}

	//若没有指输入，直接返回
	if(strlen(command) == 0) return;

	//若第一个字符串（即command）查询环境变量，调用查看环境变量的函数
	//根据bash的特点，此时只传入command
	if(command[0] == '$'){
		//show_pathname(command);
		return;
	}

	//cd指令
	if(strcmp(command, "cd") == 0){
		cd(args, size);
		return;
	}

	//quit指令
	if(strcmp(command, "quit") == 0){
		exit(0);
	}

	//echo指令
	if(strcmp(command, "echo") == 0){
		echo(args, size);
		return;
	}

	//clear指令
	if(strcmp(command, "clr") == 0){
		//输出一段转义序列清空屏幕
		printf( "\033[H""\033[2J");
		return;
	}

	//dir指令
	if(strcmp(command, "dir") == 0){
		dir(args, size);
		return;
	}

	//environ指令
	if(strcmp(command, "environ") == 0){
		showenviron(args, size);
		return;
	}

	//myshell命令
	if(strcmp(command, "myshell") == 0){
		myshell(args, size);
		return;
	}

	//help指令
	if(strcmp(command, "help") == 0){
		help(args, size);
		return;
	}

	//初始化execvp的第二个参数
	argv[0] = command;
	for(i = 0; i < size; i++)
		argv[i + 1] = args[i];
	argv[i + 1] = 0;

	pid = fork();
	if(pid < 0){
		printf("创建子进程失败！\n");
		return;
	}
	if(pid == 0){
		int ret;
		//增加parent环境变量
		strcpy(value, "parent=");
		strcat(value, first);
		strcat(value, "/myshell");
		putenv(value);
		//创建子进程调用外部指令
		ret = execvp(command, argv);
		if(ret == -1){
			//找不到指令
			printf("%s: 没有这个命令\n", command);
		}
		exit(0);
	}else{
		//等待子进程完成后返回
		int *status;
		wait(status);
		return;
	}
	
}

void clear_command(char *args[], int size){
	int i;
	for(i = 0; i < size; i++)
		if(args[i] != NULL)
			free(args[i]);
}
