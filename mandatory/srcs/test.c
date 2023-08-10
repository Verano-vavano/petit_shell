#include <stdio.h>
#include <unistd.h>

int main()
{
	char	lol[1024];
	int		q;

	q = read(0, lol, 1023);
	lol[q] = 0;
	printf("%d\n", *lol);
	return (0);
}
