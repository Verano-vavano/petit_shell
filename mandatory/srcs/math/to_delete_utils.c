#include "math.h"
#include <unistd.h>

// print to stdout the given Sign enum
void	print_sign_enum(t_expr_ll *expr)
{
	char *arr[] = {
		"NO",
		"PLUS",
		"MINUS",
		"DIV",
		"MULT"
	};
	printf("%s\n",arr[expr->sign]);
}

// Print the whole expression
void print_expr(t_expr_ll *expr)
{
    printf("value = %lld\n", expr->value);
    if (expr->var_name != NULL)
        printf("var_name = %s\n", expr->var_name);
    if (expr->var_value != NULL)
        printf("var_value = %s\n", expr->var_value);
    printf("given sign = %d\n", expr->sign);
    printf("index = %ld\n", expr->index);
    printf("Sign = ");
    print_sign_enum(expr);
}

void print_all_exprs(t_expr_ll *expr)
{
	if (!expr)
		return ;
	t_expr_ll *ptr = expr;
	int i = 0;
	while(1)
	{
		printfd(STDOUT_FILENO, "---elem %d---\n", i);
		print_expr(ptr);
		printfd(STDOUT_FILENO, "------\n");
		printfd(STDOUT_FILENO, "------\n");
		if (ptr->next == NULL)
			break ;
		ptr = ptr->next;
		i++;
	}
}
