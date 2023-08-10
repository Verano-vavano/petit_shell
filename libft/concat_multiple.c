
#include "libft.h"
#include <stdarg.h>
#include <stdio.h>

char 	*ft_strcat(char* dest, const char* src) {
    char* dest_ptr;
    const char* src_ptr;

	src_ptr = src;
	dest_ptr = dest;
    while (*dest_ptr)
        dest_ptr++;
    while (*src_ptr)
	{
        *dest_ptr = *src_ptr;
        dest_ptr++;
        src_ptr++;
    }
    *dest_ptr = '\0';
    return dest;
}

char	*concat_multiple(char **strs)
{
	int i;
	int len;
	char *concat;

	len = 0;
	i = -1;
	while(strs[++i])
		len += ft_strlen(strs[i]);
	concat = (char *)malloc(sizeof(char) * (len + 1));
	concat[0] = '\0';
	i = -1;
	while(strs[++i])
		ft_strcat(concat, strs[i]);
	return (concat);
}
