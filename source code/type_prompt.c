/*********************************/
/*  该函数显示命令提示符           */
/*********************************/
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>


//显示提示符，包括当前用户、当前目录
void type_prompt(){ 
	struct passwd *user;
	char host[256];
	char pwd[1000];
	char path[1000];
	char prompt;

	//getuid获取当前进程的用户识别码
	//getpwuid获取指定uid的数据
	user = getpwuid(getuid());
	
	//gethostname将当前主机名写入到host中，读取成功则返回0
	//getcwd获取当前工作目录，长度多于1000或读取失败返回NULL
	if(user == NULL || gethostname(host, 255) || !getcwd(pwd, 999)){
		printf("获取用户信息失败！\n");
		return;
	}

	//paht保存主目录
	strcpy(path, user->pw_dir);

	//strncasecmp比较字符串的前n个字符
	if(strncasecmp(path, pwd, strlen(path)) == 0){//若包含主目录则替换为~
		sprintf(path, "~%s", pwd + strlen(path));
	}else{
		strcpy(path, pwd);
	}

	//若为root，提示符为#，反之为$
	if(strcmp(user->pw_name, "root") == 0)
		prompt = '#';
	else
		prompt = '$';

	//输出命令提示符
	printf("[myshell]%s@%s:%s%c ", user->pw_name, host, path, prompt);
}