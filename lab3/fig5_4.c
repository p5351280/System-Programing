#include "apue.h"

int main(void)
{

	int c, count=0;
	
	while( (c = getc(stdin)) != EOF ){
		if(putc(c,stdout) == EOF)
			err_sys("output error");
		count++;
	}
		
	if(ferror(stdin))
		err_sys("input error");
	printf("%d\n", count);
	exit(0);
}

