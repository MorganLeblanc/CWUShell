#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int nextInput()
{
	//Declare information for buffer that will be
	char *inputBuffer;
	size_t bufferSize = 64;
	size_t inputCharacters;

	//Allocate 64 bytes of space for the character buffer
	inputBuffer = (char *)malloc(bufferSize * sizeof(char));

	//If space isn't available, generate error and exit
	if(inputBuffer == NULL)
	{
		perror("Memory allocation error: Memory unavailable to allocate!");
		exit(1);
	}

	//Print prompt for user input
	printf("cwushell>");

	//Use getline() to get users input command
	inputCharacters = getline(&inputBuffer, &bufferSize, stdin);

	//Declare information to tokenize the string
	char **tokenizedStrings = malloc(bufferSize * sizeof(char));
	char *tempToken;
	int counter = 0;

	//If space isn't available, generate error and exit
	if(tokenizedStrings == NULL)
	{
		perror("Memory allocation error: Memory unavailable to allocate!");
		exit(1);
	}

	//Use strtok to tokenize the Strings
	tempToken = strtok(inputBuffer, " \n\r");

	//Loop through each token, moving it into the tokenized strings array 
	while(tempToken != NULL)
	{
		tokenizedStrings[counter] = tempToken;
		counter = counter + 1;

		//Check if we need to increase the buffer size
		if(counter >= bufferSize)
		{
			//Increase buffer size before reallocationg memory
			bufferSize = bufferSize + 64;
			tokenizedStrings = realloc(tokenizedStrings, bufferSize * sizeof(char));

			//Check if memory isn't available, throwing an error if it is not
			if(tokenizedStrings == NULL)
			{
				perror("Memory allocation error: Memory unavailable to allocate!");
				exit(1);
			}
		}

		//Get next token and repeat
		tempToken = strtok(NULL, " \n\r");
	}
	//Null terminate the tokens
	tokenizedStrings[counter] = NULL;

	if(strcmp(tokenizedStrings[0], "exit") == 0)
	{
		return 0;
	}
	else if(strcmp(tokenizedStrings[0], "mv") == 0)
	{
		rename(tokenizedStrings[1], tokenizedStrings[2]);
		return 1;
	}
	else if(strcmp(tokenizedStrings[0], "ls") == 0)
	{
		//Create a status int fot the parent to watch
		int status;
		int forkValue;
		//Generate fork and check for errors
		pid_t pid;
		pid = fork();

		//create if statment for child process to use
		if(pid == 0)
		{
			//Try to run ls, sending an error if it does not work
			if(execvp(tokenizedStrings[0], tokenizedStrings) == -1)
			{
				perror("command call error, try again or check system files");
				exit(1);
			}
		}
		//check if there was an error forking the program
		else if(pid < 0)
		{
			perror("error forking, try again or check system files");
			exit(1);
		}
		//run parent process otherwise
		else
		{
			wait(&status);
		}
		return 1;
	}
	else if(strcmp(tokenizedStrings[0], "cmp") == 0)
	{
		//Create a status int fot the parent to watch
		int status;
		int forkValue;
		//Generate fork and check for errors
		pid_t pid;
		pid = fork();

		//create if statment for child process to use
		if(pid == 0)
		{
			//Try to run cmp, sending an error if it does not work
			if(execvp(tokenizedStrings[0], tokenizedStrings) == -1)
			{
				perror("command call error, try again or check system files");
				exit(1);
			}
		}
		//check if there was an error forking the program
		else if(pid < 0)
		{
			perror("error forking, try again or check system files");
			exit(1);
		}
		//run parent process otherwise
		else
		{
			wait(&status);
		}
		return 1;
	}
	else if(strcmp(tokenizedStrings[0], "tail") == 0)
	{
				//Create a status int fot the parent to watch
		int status;
		int forkValue;
		//Generate fork and check for errors
		pid_t pid;
		pid = fork();

		//create if statment for child process to use
		if(pid == 0)
		{
			//Try to run tail, sending an error if it does not work
			if(execvp(tokenizedStrings[0], tokenizedStrings) == -1)
			{
				perror("command call error, try again or check system files");
				exit(1);
			}
		}
		//check if there was an error forking the program
		else if(pid < 0)
		{
			perror("error forking, try again or check system files");
			exit(1);
		}
		//run parent process otherwise
		else
		{
			wait(&status);
		}
		return 1;
	}
	else if(strcmp(tokenizedStrings[0], "cat") == 0)
	{
				//Create a status int fot the parent to watch
		int status;
		int forkValue;
		//Generate fork and check for errors
		pid_t pid;
		pid = fork();

		//create if statment for child process to use
		if(pid == 0)
		{
			//Try to run cat, sending an error if it does not work
			if(execvp(tokenizedStrings[0], tokenizedStrings) == -1)
			{
				perror("command call error, try again or check system files");
				exit(1);
			}
		}
		//check if there was an error forking the program
		else if(pid < 0)
		{
			perror("error forking, try again or check system files");
			exit(1);
		}
		//run parent process otherwise
		else
		{
			wait(&status);
		}
		return 1;
	}
	else if(strcmp(tokenizedStrings[0], "help") == 0)
	{
		printf("Welcome to cwushell! The all in one linux shell program!\n");
		printf("Created by Morgan Leblanc, 2018\n");
		printf("\nBelow you will find a list of commands that work when using this shell. They are case sensitive and should be entered exactly.\n");
		printf("\n- exit : closes the shell.");
		printf("\n- mv <filename1> <filename2> : moves filename1 to the location of filename2.");
		printf("\n- ls : lists the content of the current directory.");
		printf("\n- cmp <filename1> <filename2> : compares two files, returning the first different byte if found.");
		printf("\n- tail -n[i] <filename1> : will print the last i lines, otherwise will print last 10");
		printf("\n- cat <filename1> : will print contents of filename1\n");
		return 1;
	}
	else
	{
		printf("Not a recognized cwushell command.\n");
		return 1;
	}

}

int main()
{
	printf("Type 'help' for list of commands.\n");
	int isRunning = 1;
	while(isRunning)
	{
		isRunning = nextInput();
	}
	return 0;
}