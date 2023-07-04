#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int rand_num(void)
{
	int tmp_file;
	int rand;
	int pid;

	pid = fork();
	if (pid == 0)
	{
		tmp_file = open("/tmp/s-hell", O_CREAT | O_WRONLY | O_TRUNC, 0777);
		dup2(tmp_file, STDOUT_FILENO);
		close(tmp_file);
		execve("/usr/bin/jot", (char *[]){"jot", "-r", "1", "0", "9", 0}, 0);
		return (0);
	}
	else
	{
		waitpid(pid, 0, 0);
		tmp_file = open("/tmp/s-hell", O_RDONLY);
		char c;
		read(tmp_file, &c, sizeof(c));
		rand = (c - '0') + 1;
		close(tmp_file);
		unlink("/tmp/s-hell");
		return (rand);
	}
}

void metal_injection(void)
{
	int group_num;
	int i;
	char *group;
	int fd;

	i = 0;
	group_num = rand_num();
	fd = open("/Users/tcharanc/code/minishell/mandatory/shell-on-earth.txt", O_RDONLY);
	while(i < group_num)
	{
		group = get_next_line(fd);
		i++;
	}
	printf("%s",group);
}
