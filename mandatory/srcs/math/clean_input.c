#include "libft.h"
#include "math.h"
#include "shellpticflesh.h"
#include <stddef.h>


static bool is_ignore_char(char c)
{
	return (c == '\n' || c == '"' || c == '$');
}

char *clean_input(const char *input)
{
	size_t len;
	size_t i;
	size_t j;
	char *clean;

	len = ft_strlen(input) - 5;
	i = 2;
	j = 0;
	while(input[++i])
		if (is_ignore_char(input[i]))
			len--;
	clean = malloc(sizeof(char) * (len - 1));
	if (!clean)
		return (NULL);
	i = 2;
	while (input[++i] && j < len)
		if (!is_ignore_char(input[i]))
			clean[j++] = input[i];
	clean[j] = '\0';
	return (clean);
}
