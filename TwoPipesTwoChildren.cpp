// file: TwoPipesTwoChildren
// author: Nicolette Railsback
// date: 03/04/2015
// purpose: cs3376
// description:
// 	this program executes "ls -ltr | grep 3376", by dividing the two
// 	commands among the child and parent process


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char **argv)
{
	int status;
	int childpid;

	char *cat_args[] = {"ls", "-ltr", NULL};
	char *grep_args[] = {"grep", "3376", NULL};
	char *count_args[] = {"wc", "-l", NULL};

	// create one pipe to send the output of "ls" process to "grep" process
	int pipes[2];
	pipe(pipes);
	// need another pipe to communicate
	int pipe2[2];
	pipe(pipe2);

	//fork the first child (to execute cat)
	if ((childpid = fork()) == -1)
	{
	perror("Error creating a child process");
	exit(1);
	}
	//child 1
	if (childpid == 0)
	{ // replace cat's stdout with writ part of 1st pipe
	dup2(pipes[1], 1);
	//close all pipes; end we're using was safely copied
	close(pipes[0]);
	close(pipes[1]);
	close(pipe2[0]);
	close(pipe2[1]);
	execvp(*cat_args, cat_args);
	exit(0);
	}
	//parrent
	else
	{
		//create a second child
		//fork the first child (to execute cat)
		if ((childpid = fork()) == -1)
		{
		perror("Error creating a child process");
		exit(1);
		}
		//child 2
		if (childpid == 0)
		{ // replace grep's stdout with write part of 2nd pipe
		dup2(pipe2[1], 1);
		//replace grep's stdin with read part of 1st pipe
		dup2(pipes[0], 0);
		//close all pipes; end we're using was safely copied
		close(pipes[0]);
		close(pipes[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		execvp(*grep_args, grep_args);
		exit(0);
		}
		else
		{
		//replase grep's stdin with read end of 2nd pipe
		dup2(pipe2[0], 0);
		//close pipes like we did for child
		close(pipe2[0]);
		close(pipe2[1]);
		close(pipes[0]);
		close(pipes[1]);

		execvp(*count_args, count_args);
		}
	}
	return 0;
}
