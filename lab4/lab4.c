#include <stdio.h>
#include "apue.h"

void accumulation(int d_sum);

//1730004
//1726231
//1726691
//1721363
//1729058
int main()
{
	FILE *sum, *input;
	int total_sum=0;
	pid_t child[5];
	int year=5, week=52, day=7;
	char filename[1000];
	int i, j, k, temp, total=0;
	sum = fopen("sum.txt", "w");
	fprintf(sum, "%d\n", 0);
	fclose(sum);
	TELL_WAIT();
	child[0] = fork();
	if(child[0] == 0){
		for(k=1; k<=week; k++){
			total=0;
			sprintf(filename, "1-%02d.txt", k);
			input = fopen(filename, "r");
			for(i=0; i<day; i++){
				total=0;
				for(j=0; j<96; j++){
					fscanf(input, "%d", &temp);
					total += temp;
				}
				accumulation(total);
			}
		}
		TELL_PARENT(getppid());
		exit(0);
	}

	WAIT_CHILD();
	child[1] = fork();

	if(child[1]==0){
		for(k=1; k<=week; k++){
			total=0;
			sprintf(filename, "2-%02d.txt", k);
			input = fopen(filename, "r");
			for(i=0; i<day; i++){
				total=0;
				for(j=0; j<96; j++){
					fscanf(input, "%d", &temp);
					total += temp;
				}
				accumulation(total);
			}
		}
		TELL_PARENT(getppid());
		exit(0);
	}

	WAIT_CHILD();
	child[2] = fork();

	if(child[2]==0){
		for(k=1; k<=week; k++){
			total=0;
			sprintf(filename, "3-%02d.txt", k);
			input = fopen(filename, "r");
			for(i=0; i<day; i++){
				total=0;
				for(j=0; j<96; j++){
					fscanf(input, "%d", &temp);
					total += temp;
				}
				accumulation(total);
			}
		}
		TELL_PARENT(getppid());
		exit(0);
	}

	WAIT_CHILD();
	child[3] = fork();

	if(child[3]==0){
		for(k=1; k<=week; k++){
			total=0;
			sprintf(filename, "4-%02d.txt", k);
			input = fopen(filename, "r");
			for(i=0; i<day; i++){
				total=0;
				for(j=0; j<96; j++){
					fscanf(input, "%d", &temp);
					total += temp;
				}
				accumulation(total);
			}
		}
		TELL_PARENT(getppid());
		exit(0);
	}

	WAIT_CHILD();
	child[4] = fork();

	if(child[4]==0){
		for(k=1; k<=week; k++){
			total=0;
			sprintf(filename, "5-%02d.txt", k);
			input = fopen(filename, "r");
			for(i=0; i<day; i++){
				total=0;
				for(j=0; j<96; j++){
					fscanf(input, "%d", &temp);
					total += temp;
				}
				accumulation(total);
			}
		}
		TELL_PARENT(getppid());
		exit(0);
	}

	WAIT_CHILD();
	sum = fopen("sum.txt", "r");
	fscanf(sum, "%d", &total_sum);
	//printf("%s, %d\n", filename, total_sum);
	printf("Day_Average = %d\n",total_sum/(year*week*day));

	fclose(sum);
	return 0;
}

void accumulation(int d_sum)    //Accumulating the daily sum to "sum.txt".
{
	FILE* sum;
	int tmp=0;

	sum = fopen("sum.txt", "r+");
	fscanf(sum, "%d", &tmp);
	tmp += d_sum;

	rewind(sum);
	fprintf(sum, "%d", tmp);
	fclose(sum);

	return;
}
