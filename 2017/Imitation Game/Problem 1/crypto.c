#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_CHAR 65536 // on my machine
#define ZERO 48

char encryptChar(char ch, int shift);

int encode(char* msg, char* key)
{
	char* code = "";
	long len_msg = strlen(msg), len_key = strlen(key), i_msg = 0, i_key = 0;
	while(i_msg < len_msg)
	{
		if(i_key == len_key)
			i_key = 0;
		char* temp = calloc(strlen(code) + 1, sizeof(char));
		strcpy(temp, code);
		code = (char * ) calloc(strlen(code) + 2, sizeof(char));
		sprintf(code, "%s%c", temp, encryptChar(msg[i_msg], key[i_key] - ZERO));
		i_msg++;
		i_key++;
	}
	puts(code);
}
int decode(char* msg, char* key)
{
	char* code = "";
	long len_msg = strlen(msg), len_key = strlen(key), i_msg = 0, i_key = 0;
	while(i_msg < len_msg)
	{
		if(i_key == len_key)
			i_key = 0;
		char* temp = calloc(strlen(code) + 1, sizeof(char));
		strcpy(temp, code);
		code = (char * ) calloc(strlen(code) + 2, sizeof(char));
		sprintf(code, "%s%c", temp, encryptChar(msg[i_msg], -(key[i_key] - ZERO)));
		i_msg++;
		i_key++;
	}
	puts(code);
}
char encryptChar(char ch, int shift)
{
	ch += shift;
	return ch;
}
void print_err()
{
	printf("Please enter the commands in the following manner:-\ncrypto [encode/decode] [--msg] <message here within single quotes> [--key] <key here in single quotes>\n");

}
int main(int argc, char** args)
{
	char* msg;
	char* key;
	if(argc > 6 || argc < 4)
		print_err();
	else
	{
		if(strncmp(args[2], "--msg", 5) == 0)
		{				
			msg = args[3];
			if(strncmp(args[4], "--key", 5) == 0)
				key = args[5];
			else
				key = args[4];
		}
		else if(strncmp(args[2], "--key", 5) == 0)
		{
			key = args[3];
			if(strncmp(args[4], "--msg", 5) == 0)
				msg = args[5];
			else
				msg = args[4];	
		}
		else
		{
			msg = args[2];
			key = args[3];
		}
		
		// Call functions
		
		if(strcmp(args[1], "encode") == 0)
			encode(msg, key);
		else if(strcmp(args[1], "decode") == 0)
			decode(msg, key);
		else
			print_err();
	}
	// puts(msg);
	// puts(key);
}
