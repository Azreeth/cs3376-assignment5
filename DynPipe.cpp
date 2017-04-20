// file: DynPipe
// author: Nicolette Railbsack
// date: 4/4/2017
// purpose: cs3376
// description:
// 	this program will read in commands and send them to child processes
//

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>

using namespace std;

int main(int argc, char **argv)
{
// need maximum of 4 children
int childpid1;
int childpid2;
int childpid3;
int childpid4;
// max of 5 arguments passed in

char *allArgs[5];

//make sure there are at least 2 string args
if (argc <= 2)
{
printf("error");
printf("\n");
exit(0);
}


int i=0;
//should seperate all the arguments into a new array
for (argc--, argv++, i=0; argc>0; argc--, argv++, i++)
{
allArgs[i] = *argv;
}
//second variable to keep track of things
int x = i;
char *arg1[25];
char *arg2[25];
char *arg3[25];
char *arg4[25];
char *arg5[25];
//seperate out the elements into args
if (i>0)
{
//seperate the first part of all into the 2 parts
// need to tokenize the input and put it in arg11 and arg12
char *token;
int j = 0;
token = strtok(allArgs[0], " ");
arg1[j] = token;
j++;
while(token != NULL)
{
token = strtok(NULL, " ");
arg1[j] = token;
j++;
}
}
i--;
if (i>0)
{
int j;
//do it again for arg2
char *token2 = strtok(allArgs[1], " ");
j = 0;
arg2[j] = token2;
j++;
while(token2 != NULL)
{
token2 = strtok(NULL, " ");
arg2[j] = token2;
j++;
}
}
i--;
if (i>0)
{
int j;
//and again
char *token3 = strtok(allArgs[2], " ");
j = 0;
arg3[j] = token3;
j++;
while (token3 != NULL)
{
token3 = strtok(NULL, " ");
arg3[j] = token3;
j++;
}
}
i--;
if (i>0)
{
int j;
// again for arg4
char *token4 = strtok(allArgs[3], " ");
j = 0;
arg4[j] = token4;
j++;
while(token4 != NULL)
{
token4 = strtok(NULL, " ");
arg4[j] = token4;
j++;
}
}
i--;
if (i>0)
{
int j;
// last tiem
char *token5 = strtok(allArgs[4], " ");
j = 0;
arg5[j] = token5;
j++;
while(token5 != NULL)
{
token5 = strtok(NULL, " ");
arg5[4] = token5;
j++;
}
}
switch(x)
{
int pipe1[2];
int pipe2[2];
int pipe3[2];
int pipe4[2];
case 2:
// 2 commands
// 1 child
// 1 pipe
//int pipe1[2];
pipe(pipe1);
if ((childpid1 = fork()) == -1)
{
//print error
perror("Error creating a child process");
exit(1);
}
else if (childpid1 == 0)
{
//child precess
//mess wutg pipes and do first statement
 dup2(pipe1[1], 1);
 close(pipe1[0]);
 close(pipe1[1]);
 //execute the first argument
 execvp(*arg1, arg1);
 exit(0);
}
else
{
//parent
//do final statement, which is the 2nd one
dup2(pipe1[0], 0);
close(pipe1[0]);
close(pipe1[1]);
//mess with pipes
execvp(*arg2, arg2);
exit(0);
}
break;

case 3:
// 3 commands
// 2 children
// 2 pipes
//int pipe1[2];
pipe(pipe1);
if ((childpid1 = fork()) == -1)
{
//print error
perror("Error creating a child process");
exit(1);
}
else if (childpid1 == 0)
{
//int pipe2[2];
pipe(pipe2);
	//second child
	if((childpid2 = fork()) == -1)
	{
	perror("Error creating a child process");
	exit(1);
	}
	else if(childpid2 == 0)
	{
	dup2(pipe2[1], 1);
	close(pipe2[0]);
	close(pipe2[1]);
	close(pipe1[0]);
	close(pipe1[1]);
	// do statement
	execvp(*arg1, arg1);
	exit(0);
	}
	else{
	//child precess
	//mess wutg pipes and do first statement
 	dup2(pipe1[1], 1);
 	close(pipe1[0]);
 	close(pipe1[1]);
 	dup2(pipe2[0], 0);
 	close(pipe2[0]);
 	close(pipe2[1]);
 	//execute the first argument
 	execvp(*arg2, arg2);
 	exit(0);
 }
}
else
{
//parent
//do final statement, which is the 2nd one
dup2(pipe1[0], 0);
close(pipe1[0]);
close(pipe1[1]);
//mess with pipes
execvp(*arg3, arg3);
exit(0);
}
break;

case 4:
// 4 commands
// 3 children
// 3 pipes
//int pipe1[2];
pipe(pipe1);
if ((childpid1 = fork()) == -1)
{
//print error
perror("Error creating a child process");
exit(1);
}
else if (childpid1 == 0)
{
//int pipe2[2];
pipe(pipe2);
	//second child
	if((childpid2 = fork()) == -1)
	{
	perror("Error creating a child process");
	exit(1);
	}
	else if(childpid2 == 0)
	{
	//int pipe3[2];
	pipe(pipe3);
		//child 3
		if((childpid3 = fork()) == -1)
		{
		perror("Error creating a child process");
		exit(1);
		}
		else if(childpid3 == 0)
		{
		dup2(pipe3[1], 1);
		close(pipe3[0]);
		close(pipe3[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		close(pipe1[0]);
		close(pipe1[1]);
		// do statement
		execvp(*arg1, arg1);
		exit(0);
		}
		else
		{
		dup2(pipe2[1], 1);
		close(pipe2[0]);
		close(pipe2[1]);
		close(pipe1[0]);
		close(pipe1[1]);
		dup2(pipe3[0], 0);
		close(pipe3[0]);
		close(pipe3[1]);
		// do statement
		execvp(*arg2, arg2);
		exit(0);
		}
	}
	else{
	//child precess
	//mess wutg pipes and do first statement
 	dup2(pipe1[1], 1);
 	close(pipe1[0]);
 	close(pipe1[1]);
 	dup2(pipe2[0], 0);
 	close(pipe2[0]);
 	close(pipe2[1]);
 	//execute the first argument
 	execvp(*arg3, arg3);
 	exit(0);
 }
}
else
{
//parent
//do final statement, which is the 2nd one
dup2(pipe1[0], 0);
close(pipe1[0]);
close(pipe1[1]);
//mess with pipes
execvp(*arg4, arg4);
exit(0);
}
break;

case 5:
// 5 commands
// 4 children
// 4 pipes
//int pipe1[2];
pipe(pipe1);
if ((childpid1 = fork()) == -1)
{
//print error
perror("Error creating a child process");
exit(1);
}
else if (childpid1 == 0)
{
//int pipe2[2];
pipe(pipe2);
	//second child
	if((childpid2 = fork()) == -1)
	{
	perror("Error creating a child process");
	exit(1);
	}
	else if(childpid2 == 0)
	{
	//int pipe3[2];
	pipe(pipe3);
		//child 3
		if((childpid3 = fork()) == -1)
		{
		perror("Error creating a child process");
		exit(1);
		}
		else if(childpid3 == 0)
		{
		//int pipe4[2];
		pipe(pipe4);
			// child 4
			if ((childpid4 = fork()) == -1)
			{
			perror("Error creating a child process");
			exit(1);
			}
			else if(childpid4 == 0)
			{
			dup2(pipe4[1], 1);
			close(pipe4[0]);
			close(pipe4[1]);
			close(pipe3[0]);
			close(pipe3[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			close(pipe1[0]);
			close(pipe1[1]);
			// do first statement
			execvp(*arg1, arg1);
			exit(0);
			}
			else
			{
			dup2(pipe3[1], 1);
			dup2(pipe4[0], 0);
			close(pipe4[0]);
			close(pipe4[1]);
			close(pipe3[0]);
			close(pipe3[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			close(pipe1[0]);
			close(pipe1[1]);
			// do second statement
			execvp(*arg2, arg2);
			exit(0);
			}
		}
		else
		{
		dup2(pipe2[1], 1);
		close(pipe2[0]);
		close(pipe2[1]);
		close(pipe1[0]);
		close(pipe1[1]);
		dup2(pipe3[0], 0);
		close(pipe3[0]);
		close(pipe3[1]);
		// do statement
		execvp(*arg2, arg2);
		exit(0);
		}
	}
	else{
	//child precess
	//mess wutg pipes and do first statement
 	dup2(pipe1[1], 1);
 	close(pipe1[0]);
 	close(pipe1[1]);
 	dup2(pipe2[0], 0);
 	close(pipe2[0]);
 	close(pipe2[1]);
 	//execute the first argument
 	execvp(*arg3, arg3);
 	exit(0);
 }
}
else
{
//parent
//do final statement, which is the 2nd one
dup2(pipe1[0], 0);
close(pipe1[0]);
close(pipe1[1]);
//mess with pipes
execvp(*arg4, arg4);
exit(0);
}
break;

}

// look at assignment 4 to see how to cycle through the argv stuff
// that would be a good way to go through the arguments and send them to pipes
//
// may also want to make 4 pipes between the processes
// using the same format from part 1 of this project
// 1 way to do this might be to make children and then grandchildren
// on and on, with each child making a new pipe so there arent a ton of
// extra pipes running arround
// the youngest grandchild will execute the first part of the code?
// the commands need to be split before any forking happens
//
// i believe each command only has 2 parts
//
// will need to seperate out the command string into 2 parts
// the command, and the options
// then pass those into the execvp function
//
// may be able to do this in a loop with a single child and parent
// easiest was is going to be a long set of if statements
//
// most likely going to want to draw pictures of the tables and pipes for the 
// children
//
//

return 0;
}
