#include "apue.h"

int
main(void)
{
	//getpid() 查看当前进程的pid（每次执行都可能不一样）
	//getppid()查看父进程的pid
	printf("hello world from process ID %ld\n", (long)getpid()); 
	exit(0);
}
