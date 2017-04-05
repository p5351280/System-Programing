#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1000
#define INSERT 1
#define NEWLINE 2
#define PROPER 3
#define UPPER 4
#define LOWER 5
#define REVERSE 6
#define ENDPROPER 7
#define ENDUPPER 8
#define ENDLOWER 9
#define ENDREVERSE 10

int operation(char []);
int recognize(char []);
char* Insert(char []);
char* Proper(char []);
char* Upper(char []);
char* Lower(char []);
char* Reverse(char []);
int check(int [], int);

int stk[SIZE], top;

int main(int argc, char* argv[]){
	if(freopen(argv[1], "r", stdin) == NULL){
		printf("ERROR: File Not Found!\n");
		return -1;
	}
	int len = strlen(argv[1]);
	char out[SIZE];
	strncpy(out, argv[1], len-3);
	strcpy(out+len-3, "output");
	puts(out);
	if(freopen(out, "w", stdout)==NULL){
		printf("ERROR: Can't Create File\n");
		return -1;
	}
	int line = 0;
	char oneLine[SIZE];
	while(fgets(oneLine, SIZE, stdin)){
		len = strlen(oneLine);
		if(oneLine[len-1] == '\n')
			oneLine[len-1] = 0;
		operation(oneLine);
	}
	return 0;
}

int operation(char input[]){
	char *temp;
	while((temp = strchr(input, '<'))){
		
	}
}

int recognize(char input[]){
	
}

char* Insert(char input[]){
	static char result[SIZE];
	memset(result, 0, sizeof(result));
	char *temp_1, *temp_2, ch[SIZE]={0}, nu[SIZE]={0};

	/* find for word */
	temp_1 = strchr(input, '\'');
	temp_2 = strchr(temp_1+1, '\'');
	strncpy(ch, temp_1+1, temp_2-temp_1-1);
	
	/* find for num */
	temp_1 = strchr(temp_2+1, '\'');
	temp_2 = strchr(temp_1+1, '\'');
	strncpy(nu, temp_1+1, temp_2-temp_1-1);
	int num = atoi(nu);

	for(int i=0; i<num; i++)
		strcpy(result+strlen(result), ch);
	return result;
}

char* Proper(char input[]){
	static char result[SIZE];
	memset(result, 0, sizeof(result));
	int len = strlen(input);
	for(int i=0; i<len; i++){
		if(i==0 || input[i-1]==' ')
			result[i] = toupper(input[i]);
		else
			result[i] = tolower(input[i]);
	}
	return result;
}

char* Upper(char input[]){
	static char result[SIZE];
	memset(result, 0, sizeof(result));
	int len = strlen(input);
	for(int i=0; i<len; i++)
		result[i] = toupper(input[i]);
	return result;
}

char* Lower(char input[]){
	static char result[SIZE];
	memset(result, 0, sizeof(result));
	int len = strlen(input);
	for(int i=0; i<len; i++)
		result[i] = tolower(input[i]);
	return result;
}

char* Reverse(char input[]){
	static char result[SIZE];
	memset(result, 0, sizeof(result));
	int len = strlen(input);
	for(int i=0, j=len-1; i<len; i++, j--)
		result[j] = input[i];
	return result;
}

