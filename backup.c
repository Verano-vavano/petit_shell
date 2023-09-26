#include "shellpticflesh.h"

static bool invalid_math(const char *line)
{
	const char *ptr;

	ptr = line;
	while(*ptr)
	{
		while(is_spc(*ptr))
			ptr++;
		if (is_operator(*ptr) && (*ptr != '-' || *ptr != '+'))
		{
			printfd(STDERR_FILENO, "%s: %s:  syntax error: operand expected (error token is \"%s\"\n",PROG_NAME, line, ptr);
			return (true);
		}
		else if (is_alpha(*ptr))
		{
			while(is_varname_char(*ptr))
				ptr++;
			if (!*ptr)
				break ;
		}
		else if (isdigit(*ptr))
		{
			while(is_digit(*ptr))
				ptr++;
			if (!*ptr)
				break ;
			if (!is_spc(*ptr) && !is_operator(*ptr))
			{
				printfd(STDERR_FILENO, "Truc bizaree apres un chiffre");
				return (true);
			}
		}
		else {
			printfd(STDERR_FILENO, "Un signe inconnu au bataillon\n");
			return (true);
		}
		while(is_operator(*ptr) || is_spc(*ptr))
			ptr++;
	}
	return (false);
}

static void expand(char *original, const char *var, const char* val)
{
	int val_len;
	int var_len;
	char *current;
	char *match;
	
	var_len = ft_strlen(var);
	printf("val = %s\n",val);
	if (!*val)
		val_len = 1;
	else
		val_len = ft_strlen(val);
	current = original;
	match = ft_strstr(current, var);
	while (match != NULL)
	{
		size_t before_match_len = match - current;
		size_t after_match = ft_strlen(match + var_len);
		size_t new_len = before_match_len + val_len + after_match + 1;
		char *expanded = malloc(sizeof(char) * new_len);
		strncpy(expanded, current, before_match_len);
		expanded[before_match_len] = '\0';
		if (!*val)
		    strcat(expanded, "0");
		else
			strcat(expanded, val);
		strcat(expanded, match + var_len);
		strcpy(current, expanded);
		free(expanded);
		current = current + before_match_len + val_len;
		match = strstr(current, var);
	}
}

static void expand_vars(char *cmd, t_env *env)
{
	t_env *env_ptr;

	env_ptr = env;
	while(env_ptr)
	{
		char *match = strstr(cmd, env_ptr->key);
		if (match)
			expand(cmd, env_ptr->key, env_ptr->value);
		env_ptr = env_ptr->next;
	}
}
