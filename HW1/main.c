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

char* operation(char []);
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
	int line = 0;
	char oneLine[SIZE];
	while(fgets(oneLine, SIZE, stdin)){
		line++;
		len = strlen(oneLine);
		if(oneLine[len-1] == '\n')
			oneLine[len-1] = 0;
		if(strstr(operation(oneLine), "ERROR"))
			printf("%s (in %s file line %d)\n", operation(oneLine), argv[1], line);
		else
			puts(operation(oneLine));
	}
	//puts(operation("Wow<Insert char = '!' num = '3'> That's a good idea!"));
	//puts(operation("This is line 1. <Newline>This is line 2."));
	//puts(operation("Wow!!! That's a <Reverse>DOOG</Reverse> idea!"));

	return 0;
}

char* operation(char input[]){
	char *start, *end,  *ptr[SIZE], stkInput[SIZE][SIZE]={{0}};
	int top=0, final=0, stk[SIZE]={0};
	static char result[SIZE];
	memset(result, 0, sizeof(result));
	int i, len = strlen(input);
	start = strchr(input, '<');
	if(start){
		strncpy(stkInput[top], input, start-input);

		while(start){	
			int kind = recognize(start);
			if(kind < 0){
				return "ERROR: wrong tags";
			}
			else if(kind == INSERT){
				end = strchr(start, '>');
				char temp[SIZE]={0};
				strncpy(temp, start, end-start+1);
				strcpy(stkInput[top]+strlen(stkInput[top]), Insert(temp));
				start = strchr(end+1, '<');
			}
			else if(kind == NEWLINE){
				strcpy(stkInput[top]+strlen(stkInput[top]), "\n");
				end = strchr(start, '>');
				start = strchr(start+1, '<');
			}
			else if(kind < ENDPROPER){
				stk[++top] = kind;
				end = strchr(start, '>');
				if(!strncmp(end+1, "<", 1)){
					start = end+1;
					continue;
				}
				else{
					start = strchr(end, '<');
					strncpy(stkInput[top], end+1, start-end-1);
				}
				final = top;
			}
			else{
				if(stk[top] != kind-4)
					return "ERROR: Pairs of tags are interleaved!";
				else{
					int choose = stk[top];
					switch(choose){
						case PROPER:
							for(i=top; i<=final; i++)
								strcpy(stkInput[i], Proper(stkInput[i]));
							break;
						case UPPER:
							for(i=top; i<=final; i++)
								strcpy(stkInput[i], Upper(stkInput[i]));
							break;
						case LOWER:
							for(i=top; i<=final; i++)
								strcpy(stkInput[i], Lower(stkInput[i]));
							break;
						case REVERSE:
							for(i=top; i<=final; i++)
								strcpy(stkInput[i], Reverse(stkInput[i]));
							break;
					}
					top--;
				}
				end = strchr(start, '>');
				start = strchr(start+1, '<');
			}
		}
		if(top!=0)
			return "ERROR: The tag is not a pair.";

		for(i=0; i<=final; i++){
			strcpy(result+strlen(result), stkInput[i]);
			//	puts(stkInput);
		}
		strcpy(result+strlen(result), end+1);
	}
	else
		strcpy(result, input);
	return result;
}

int recognize(char input[]){
	input += 1;
	if(!strncmp(input, "Insert", 6)){
		int count=0;
		char *end = strchr(input, '>');
		if(end){
			for(int i=0; i<=end-input; i++)
				if(input[i] == '\'')	count++;
			if(count!=4)	return -1;
		}
		else
			return -1;
		return INSERT;
	}
	else if(!strncmp(input, "Newline>", 8))
		return NEWLINE;
	else if(!strncmp(input, "Proper>", 7))
		return PROPER;
	else if(!strncmp(input, "Upper>", 6))
		return UPPER;
	else if(!strncmp(input, "Lower>", 6))
		return LOWER;
	else if(!strncmp(input, "Reverse>", 8))
		return REVERSE;
	else{
		input += 1;
		if(!strncmp(input, "Proper>", 7))
			return ENDPROPER;
		else if(!strncmp(input, "Upper>", 6))
			return ENDUPPER;
		else if(!strncmp(input, "Lower>", 6))
			return ENDLOWER;
		else if(!strncmp(input, "Reverse>", 8))
			return ENDREVERSE;
		else
			return -1;
	}
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

	/* find for the end */

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

