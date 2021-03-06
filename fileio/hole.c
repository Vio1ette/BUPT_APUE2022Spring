#include "apue.h"
#include <fcntl.h>

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
	int		fd;

	if ((fd = creat("file.hole", FILE_MODE)) < 0)
		err_sys("creat error");
	//写入10个字节
	if (write(fd, buf1, 10) != 10)
		err_sys("buf1 write error");
	/* offset now = 10 */

	//将文件偏移设定到16384，下次再写时，文件被扩展，中间用'\0'填充
	if (lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("lseek error");
	/* offset now = 16384 */

	if (write(fd, buf2, 10) != 10)
		err_sys("buf2 write error");
	/* offset now = 16394 */

	//最后文件内容：
	// abcdefghij@@@@@@@@@@@.....@@@@@@@ABCDEFGHIJ
	//看别人的博客，中间的@应该是'\0'
	exit(0);
}
