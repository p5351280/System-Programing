#include "apue.h"
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

static void	sig_int(int);		/* our signal-catching function */
int main(void){
	char buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int status;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	printf("## ");	/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] =0;
		int count = 0;
		char *argv[100];
		char *temp, *token = " ";
		temp = strtok(buf, token);	
		
		while(temp != NULL){
			argv[count++] = temp;
			temp = strtok(NULL, token);
		}
		argv[count] = (char*)0;
		if(strcmp(argv[0], "cd") == 0){
//			execvp(argv[0], argv);
			chdir(argv[1]);
		}
		else{
			if ((pid = fork()) < 0) {
				err_sys("fork error");
			} 
			else if (pid == 0) {		/* child */
				//execlp(buf, buf, (char*)0);
				execvp(argv[0], argv);
				err_ret("couldn't execute: %s", buf);
				exit(127);
			}
			/* parent */
			if ((pid = waitpid(pid, &status, 0)) < 0)
				err_sys("waitpid error");
		}
		printf("## ");
	}
	exit(0);
}

void sig_int(int signo){
	printf("interrupt\n## ");
}

char* cut(char input[]){

}
