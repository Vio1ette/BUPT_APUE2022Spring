#include "apue.h"
#include <fcntl.h>

/*

$ ./fileflags 0 < /dev/tty
>>> fcntl的第一个参数为0，表示标准输入，一个单独的 '<' 是'1<'的简写 表示重定向标准输入，即'0'被重定向为了设备文件/dev/tty

$ ./fileflags 1 > temp.foo
>>> fcntl的第一个参数为1，标准输出，'>'是'1>'的简写，标准输出重定向到temp.foo

$ ./fileflags 2 2>> temp.foo
>>> 对大于1的文件描述符的重定向不能省略文件描述符
fcntl的第一个参数为2，将标准错误输出重定向到 temp.foo，且为追加重定向（每次都会从文件尾开始写入数据，不会覆盖）

$ ./fileflags 5 5<> temp.foo
>>> '5<>'被shell解释为：将输出和输入都重定向为文件temp.foo，注意<>之间不能有空格，'5<>'被放到一起解析，中间不能有空格



*/


int
main(int argc, char *argv[])
{
	int		val;

	if (argc != 2)
		err_quit("usage: a.out <descriptor#>");
		//获取文件描述符为(atoi(argv[1]))的文件的file status flags，赋给val，第三个参数为0表示无额外参数
	if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
		err_sys("fcntl error for fd %d", atoi(argv[1]));

	switch (val & O_ACCMODE) {
	case O_RDONLY:
		printf("read only");
		break;

	case O_WRONLY:
		printf("write only");
		break;

	case O_RDWR:
		printf("read write");
		break;

	default:
		err_dump("unknown access mode");
	}

	if (val & O_APPEND)
		printf(", append");
	if (val & O_NONBLOCK)
		printf(", nonblocking");
	if (val & O_SYNC)
		printf(", synchronous writes");

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if (val & O_FSYNC)
		printf(", synchronous writes");
#endif

	putchar('\n');
	exit(0);
}
