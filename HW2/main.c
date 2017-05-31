#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

bool flag = false;
int cnt = 0;
int status = 0;
//0 for no fish, 1 for catch, 2 for escape

void controlRod(){
	printf("\n\n");
	if(!flag){	//Cast the rod
		flag = true;
		status = 0;
		puts("Cast the fishing rod");
		puts("Bait into water, waiting fish...");
	}
	else{	//Pull the rod
		flag = false;
		puts("Pull the fish rod");
		puts("---------------------------");
		if(status == 0){
			puts("Nothing happen!");
		}
		if(status == 1){
			puts("Catch a Fish!!");
			printf("Totally caught fishes : %d\n", ++cnt);
		}
		else if(status == 2)
			puts("The bait was eaten!!");
		puts("---------------------------");

	}
}

void endGame(){
	printf("\n");
	printf("Totally caught fishes: %d\n",cnt);
	exit(0);
}

void controlFish(){
	if(status == 0){
		puts("Fish eaten!!");
		status = 1;
	}
	else if(status == 1){
		puts("Fish run away!!");
		status = 2;
	}
}

int main(){
	srand(time(NULL));
	signal(SIGINT, controlRod);	//^C
	signal(SIGTSTP, endGame);	//^Z
	signal(SIGALRM, controlFish);	//alarm()
	while(1){
		printf("\n");
		puts("Fishing rod is ready!");
		pause();
		int wait = rand()%3 + 3;	//Random between 3-5 secs
		printf("%d secs\n", wait);
		alarm(wait);	//Wait for fish eat bait
		pause();
		if(status == 0){	//No fish biting
			alarm(0);
			continue;
		}
		else if(status == 1){	//Fish eat, wait for reel pole
			alarm(3);
			pause();
		}
		
		if(status == 1){	//Success catch fish
			alarm(0);
			continue;
		}
		else if(status == 2)	//Fish run away
			pause();
	}
	return 0;
}
