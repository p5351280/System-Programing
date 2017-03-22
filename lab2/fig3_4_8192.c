#include "apue.h"
#include<fcntl.h>
#define	BUFFSIZE	8192

int main(void)
{
		int fd;
		fd=open("/dev/null", O_RDWR);
		
		int		n;
		char	buf[BUFFSIZE];

		while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
				if (write(fd, buf, n) != n)
						err_sys("write error");

		if (n < 0)
				err_sys("read error");

		exit(0);
}

