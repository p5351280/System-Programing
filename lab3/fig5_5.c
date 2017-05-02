#include "apue.h"

int main(void)
{
	char buf[MAXLINE];
	int count=0;
	
	setvbuf(stdin, NULL, _IOLBF, 4096);
	
	while( (fgets(buf,MAXLINE,stdin)) != NULL ){
		if(fputs(buf,stdout) == EOF)
			err_sys("output error");
		count++;	
	}
	if(ferror(stdin))
		err_sys("input error");
	printf("%d\n", count);
	exit(0);
}

