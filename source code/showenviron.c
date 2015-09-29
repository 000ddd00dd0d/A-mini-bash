/**********************************/
/*   该函数完成environ功能         */
/**********************************/
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int showenviron(char *args[], int size){
	char **env;
	char *value;
	if(size == 0){//若没有参数则显示所有变量
		env = environ;
		while(*env){
			printf("%s\n", *env);
			env++;
		}
	}else{//查询并显示该变量
		int i;
		for(i = 0; i < size; i++){
			value = getenv(args[i] + 1);
			if(!value){
				printf("%s：没有该变量\n", args[i]);
			}else{
				printf("%s=%s\n", args[i] + 1, value);
			}
		}
	}
	return 1;
}