#include "math.h"

bool is_newline(char c)
{
	return ((unsigned)c - '\t' < 5);
}

bool is_spc(char c)
{
	return (c == ' ' || (unsigned)c - '\t' < 5);
}

bool is_operator(char c)
{
	return (
	c == '+' || \
	c == '-' || \
	c == '!' || \
	c == '~' || \
	c == '*' || \
	c == '/' || \
	c == '%' || \
	c == '<' || \
	c == '>' || \
	c == '=' || \
	c == '&' || \
	c == '^' || \
	c == '|' || \
	c == '?' || \
	c == ','
	);
}

bool is_alpha(char c)
{
	return ((c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z'));
}

bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
