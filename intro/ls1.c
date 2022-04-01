#include "apue.h"
#include <dirent.h>

int
main(int argc, char *argv[])
{
	DIR				*dp; 		//目录
	struct dirent	*dirp;		//目录项

	if (argc != 2) // 第一个参数是命令本身
		err_quit("usage: ls directory_name");

	if ((dp = opendir(argv[1])) == NULL)
		err_sys("can't open %s", argv[1]);
	while ((dirp = readdir(dp)) != NULL) // 每次读取一个目录项，然后输出它的名字
		printf("%s\n", dirp->d_name);

	closedir(dp);
	exit(0);
}
