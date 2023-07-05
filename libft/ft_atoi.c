#include <stdio.h>

int is_spc(char c)
{
	return (c == ' ' || (unsigned)c - '\t' < 5);
}

int is_dgt(char c)
{
	return ((unsigned)c - '0' < 10);
}

long ft_atol(const char *s)
{
	int n;
	int neg;

	n = 0;
	while(is_spc(*s))
		s++;
	if (*s == '-') 
		neg = 1;
	else if (*s == '+')
		s++;
	while(is_dgt(*s))
		n = n * 10 - (*s++ - '0');
	if (neg)
		return (-n);
	return (n);
}
