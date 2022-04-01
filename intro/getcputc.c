#include "apue.h"

int
main(void)
{
	int		c;
	// int getc ( FILE * stream ); 
	// int putc(int char, FILE *stream) int char 表示一个字a符的ASCII码
	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
			err_sys("output error");

	if (ferror(stdin))
		err_sys("input error");

	exit(0);
}
