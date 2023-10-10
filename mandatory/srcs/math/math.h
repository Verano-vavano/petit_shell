#ifndef MATH_H
#define MATH_H

#include "shellpticflesh.h"
#include <stdint.h>
#include "stdbool.h"

#define MAX_INT_LEN 32

typedef enum {
	NO, // NOTHING
	PLUS, // +
	MINUS, // -
	DIV, // /
	MULT, // *
} Sign;

// Expression is the context of an operation
// (left number + sign)
typedef struct s_expr_ll {
	long long value;
	char* var_name;
	char* var_value;
	size_t index;
	Sign sign;
	struct s_expr_ll *next;
} t_expr_ll;

//--------CHAR_CHECKING-------//
bool		is_spc(char c);
bool		is_alpha(char c);
bool		is_digit(char c);
bool	 	is_sign(char c);
//--------CLEAN_INPUT-------//
char *clean_input(const char *input);
//--------EXPR_LL-------//
t_expr_ll	*expr_last(t_expr_ll *expr_ll);
t_expr_ll	*expr_create(int i, char *clean, t_env *env);
bool		expr_add(t_expr_ll *newest, t_expr_ll **expr);
void		free_expr(t_expr_ll *expr_ll);
void		free_expr_ll(t_expr_ll *expr_ll);
//--------EXPR_LL-------//
long long calculate(t_expr_ll *expr_ll);
//--------FT_ATOIII-------//
// un vraiment gros atoi
intmax_t	ft_atoiii(const char *str);
//--------FT_ATOIII-------//
// une vraiment grosse string! (peut etre)
char	*ft_iiitoa(long long n);
//--------TO_DELETE_UTILS-------//
// de la poubelle qu'il va falloir supprimer
void	print_sign_enum(t_expr_ll *expr);
void	print_expr(t_expr_ll *expr);
void	print_all_exprs(t_expr_ll *expr);

#endif
