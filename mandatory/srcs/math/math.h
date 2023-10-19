/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 10:50:41 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/19 17:39:45 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include "shellpticflesh.h"
# include <stdint.h>
# include "stdbool.h"

# define MAX_INT_LEN 32

typedef enum sign {
	NO,
	PLUS,
	MINUS,
	DIV,
	MULT,
}	t_sign;

// Expression is the context of an operation
// (left number + sign)
typedef struct s_expr_ll {
	long long			value;
	char				*var_name;
	char				*var_value;
	size_t				index;
	t_sign				sign;
	struct s_expr_ll	*next;
}	t_expr_ll;

//--------CHAR_CHECKING-------//
bool		is_spc(char c);
bool		is_alpha(char c);
bool		is_digit(char c);
bool		is_sign(char c);
//--------CLEAN_INPUT-------//
char		*clean_input(const char *input);
//--------EXPR_LAST-------//
t_expr_ll	*expr_last(t_expr_ll *expr_ll);
//--------EXPR_LL-------//
t_expr_ll	*expr_create(int i, char *clean, t_env *env);
//--------EXPR_ADD-------//
bool		expr_add(t_expr_ll *newest, t_expr_ll **expr);
//--------FREE_EXPR-------//
void		free_expr(t_expr_ll *expr_ll);
void		free_expr_ll(t_expr_ll *expr_ll);
//--------CALCULATE-------//
long long	calculate(t_expr_ll *expr_ll);
//--------FT_ATOIII-------//
// un vraiment gros atoi
intmax_t	ft_atoiii(const char *str);
//--------FT_ATOIII-------//
// une vraiment grosse string! (peut etre)
char		*ft_iiitoa(long long n);
//--------CHECK_ERROR-------//
int			math_errors(t_expr_ll *expr_ll, char *clean);
//--------PRINT_MATH_ERROR-------//
int			print_math_error(char *error_msg, char *clean, int i);
//--------TO_DELETE_UTILS-------//
// de la poubelle qu'il va falloir supprimer
void		print_sign_enum(t_expr_ll *expr);
void		print_expr(t_expr_ll *expr);
void		print_all_exprs(t_expr_ll *expr);

#endif
