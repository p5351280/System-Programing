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

int operation(char []);
int recognize(char []);
char* Insert(char []);
char* Proper(char []);
char* Upper(char []);
char* Lower(char []);
char* Reverse(char []);
int check(int [], int);

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
	
	return 0;
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
