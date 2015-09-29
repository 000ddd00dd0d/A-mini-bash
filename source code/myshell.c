/***************************************/
/*主函数：一直执行直至quit退出           */
/**************************************/
#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char first[1000];
int jobID = 0;
int main(){ //主函数
	char command[100];
	char *args[1000];
	int size, i;
	char value[1050];
	char shellname[1050];

	//初始化，增加环境变量
	getcwd(first, 999); //获取当前目录
	strcpy(value, "shell=");
	strcpy(shellname, first);
	strcat(shellname, "/myshell");
	strcat(value, shellname);
	putenv(value);

	while(true){
		type_prompt();	//输出命令提示符
		//读取指令
		size = read_command(command, args, stdin);
		//分词并调用指令
		backstage(command, args, size);
		//释放内存
		clear_command(args, size);
	}
}