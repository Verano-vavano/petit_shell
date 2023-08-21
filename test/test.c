#include <sys/types.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	DIR				*cwd;
	struct dirent	*fl;

	cwd = opendir("..");
	fl = readdir(cwd);
	while (fl)
	{
		if (fl->d_name[0] != '.')
			printf("%s\n", fl->d_name);
		fl = readdir(cwd);
	}
	closedir(cwd);
	return (0);
}
