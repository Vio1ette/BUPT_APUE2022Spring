#include "apue.h"
#include <sys/wait.h>

//模拟一个shell

int
main(void)
{
	char	buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int		status;

	printf("%% ");	/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {  //从标准输入读取命令到buf，最大读取字节数为MAXLINE
		//如果最后一个字符是换行符，则将它改为0（0作为一个字符串结束符）
		//不直接将最后一个字符变为0的原因是：最后一个字符不一定是换行符，虽然用户输入时一般会输入一个字符串就换行
		//但字符串有可能超长，所以最后一个字符不一定是换行符
		if (buf[strlen(buf) - 1] == '\n') 
			buf[strlen(buf) - 1] = 0; /* replace newline with null */

		//fork()函数创建一个子进程，返回子进程的pid
		//父进程和子进程的代码完全一样
		//创建完成之后，子进程和父进程在调用fork处继续往下执行，只不过父进程的fork返回子进程的pid，子进程的pid返回0
		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) {		/* child */
		//execlp()会从PATH 环境变量所指的目录中查找符合参数file的文件名, 找到后便执行该文件,
		//然后将第二个以后的参数当做该文件的argv[0]、argv[1]……, 最后一个参数必须用空指针(NULL)作结束。
		//返回值：
		//如果执行成功则函数不会返回, 执行失败则直接返回-1, 失败原因存于errno 中。
			execlp(buf, buf, (char *)0); //执行buf中的代码
			err_ret("couldn't execute: %s", buf);  //如果子进程执行失败，就会执行这条语句
			exit(127);
		}

		/* parent */  // 父进程等待子进程执行完毕，status记录执行子进程的返回值
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}
