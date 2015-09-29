#define true 1
#define false 0
#define MAX_LINE 80
#include <stdio.h>

void type_prompt(); //输出当前用户及当前目录
int read_command(char *command, char *args[], FILE *stream); //读取指令
void clear_command(char *args[], int size);	//释放内存
void judge_utility(char *command, char *args[], int size); //判断当前指令的作用并调用函数
int cd(char *args[], int size); //改变目录
int echo(char *args[], int size); //输出结果
int dir(char *args[], int size); //查看当前目录
void redirection(char *command, char *args[], int size);//输入、输出重定向
int showenviron(char *args[], int size); //显示环境变量
int myshell(char *args[], int size); //从文件中提取命令
int help(char *args[], int size);	//获取帮助