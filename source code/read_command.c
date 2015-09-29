/*************************************/
/*      该函数读取指令并分词           */
/*************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//读取指令和参数并作分割
int read_command(char *command, char *args[], FILE *stream){
	char cmdline[1000];	//储存一行指令
	int i, j = 0, k = 0;
	char *ret;
	int cnt = 0;	//记录参数个数
	char temp[1000];
	
	//读入一行指令
	ret = fgets(cmdline, 1000, stream);
	if(ret == 0) return -1;

	//读取指令名
	sscanf(cmdline, "%s", command);

	//获取指令名
	i = 0;
	while(cmdline[i] == ' ' || cmdline[i] == '\t') i++;
	while(cmdline[i] != '\0' && cmdline[i] != '\n' && cmdline[i] != ' ' && cmdline[i] != '\t')
		command[k++] = cmdline[i++];
	command[k] = '\0';

	//从第一个参数的起始位置
	while(cmdline[i] != '\0' && cmdline[i] != '\n'){
		k = 0;
		//跳过空格
		while(cmdline[i] == ' ' || cmdline[i] == '\t') i++;
		//复制内容
		while(cmdline[i] != ' ' && cmdline[i] != '\t' && cmdline[i] != '\0' && cmdline[i] != '\n')
			temp[k++] = cmdline[i++];
		temp[k] = '\0';
		//保存参数
		if(strlen(temp)){
			args[j] = (char *)malloc(sizeof(temp));
			strcpy(args[j++], temp);
			cnt++;
		}
	}
	return cnt; //返回参数个数
}

