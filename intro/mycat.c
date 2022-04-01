#include "apue.h" //apue书作者自己写的头文件

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) //从标准输入读入BUFFSIZE个字节到buf中
//将buf中的内容写入标准输出，用n而不用BUFFSIZE的原因是：读进来的不一定就是BUFFSIZE个字节，写的时候看实际read进来的字节数
		if (write(STDOUT_FILENO, buf, n) != n)   
			err_sys("write error");

	if (n < 0)
		err_sys("read error");

	exit(0);
}
