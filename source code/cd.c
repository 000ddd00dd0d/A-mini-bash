/*****************************************************/
/*               该函数完成cd功能                     */
/*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>

int cd(char *args[], int size){
	int ret;
	struct stat buf;
	struct passwd *user;
	char value[1000];
	char pwd[1000];

	//若没有参数，则跳转至主目录
	if(size == 0){
		//getuid获取当前进程的用户识别码
		//getpwuid获取指定uid的数据
		user = getpwuid(getuid());

		ret = chdir(user->pw_dir);
		if(ret == -1){
			printf("myshell: cd: %s: 打开目录失败\n", user->pw_dir);
			return 0;
		}
		//修改环境变量
		getcwd(pwd, 999);
		strcpy(value, "PWD=");
		strcat(value, pwd);
		putenv(value);
		return 1;
	}

	//判断是否存在
	ret = stat(args[0], &buf);
	if(ret == -1){
		printf("myshell: cd: %s: 没有该目录或文件\n", args[0]);
		return 0;
	}

	//判断是否为目录
	if(!S_ISDIR(buf.st_mode)){
		printf("myshell: cd: %s: 不是一个目录\n", args[0]);
		return 0;
	}

	//能否打开该目录
	ret = chdir(args[0]);
	if(ret == -1){
		printf("myshell: cd: %s: 打开目录失败\n", args[0]);
		return 0;
	}

	//修改环境变量
	getcwd(pwd, 999);
	strcpy(value, "PWD=");
	strcat(value, pwd);
	putenv(value);
	return 1;
}