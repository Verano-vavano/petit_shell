#include "math.h"

static int parsed_len(t_expr_ll	*expr, char *clean)
{
	t_expr_ll *ptr;
	ptr = expr_last(expr);
	int i = ptr->index;
	while(clean[i] && (is_alpha(clean[i]) || is_digit(clean[i]) || clean[i] == '_'))
		i++;
	while(clean[i] && is_spc(clean[i]))
		i++;
	while(clean[i] && is_sign(clean[i]))
		i++;
	return (i);
}

// TODO maybe delete this?
// this is needed by expr_create
static Sign sign_determine(char c)
{
	if (c == '+')
		return(PLUS);
	else if (c == '-')
		return (MINUS);
	else if (c == '/')
		return (DIV);
	else if (c == '*')
		return (MULT);
	return (NO);
}

// Create a new expression link.
// for that parse the string
t_expr_ll *expr_create(int i, char *clean, t_env *env)
{
	(void)env;
	t_expr_ll	*created;
	intmax_t	j;

	created = malloc(sizeof(t_expr_ll));
	if (!created)
		return (NULL);
	*created = (t_expr_ll){ .value = 0, .var_name = NULL, .var_value = NULL,
		.index = 0, .sign = NO, .next = NULL };
	while (is_spc(clean[i]))
		i++;
	if (clean[i])
	{
		printf("STARTING at '%c'\n",clean[i]);
		// TODO handle basic errors first char.
		created->index = i;
		j = i;
		while (is_digit(clean[j]))
			j++;
		created->var_value = malloc(sizeof(char) * (j - i + 1));
		j = 0;
		while(is_digit(clean[i]))
			created->var_value[j++] = clean[i++];
		created->var_value[j] = '\0';
		if (!clean[i])
			return (created);
		while(clean[i] && is_spc(clean[i]))
			i++;
		created->sign = sign_determine(clean[i]);
	}
	return (created);
}
