/***********************************/
/*       该函数完成echo功能         */
/***********************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int echo(char *args[], int size){
	int i;
	char *value;
	if(size == 0){ //若无参数则输出空行
		puts("");
		return 1;
	}
	for(i = 0; i < size; i++){
		if(args[i][0] == '$'){//转义环境变量
			value = getenv(args[i] + 1);
			printf("%s", value);
		}else
			printf("%s", args[i]);
		if(i != size - 1)
			printf(" ");
		else printf("\n");
	}
	return 1;
}