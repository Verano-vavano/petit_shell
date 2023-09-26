#ifndef MATH_H
# define MATH_H

#include "shellpticflesh.h"

typedef enum Operator {
	ADDITION,  // +
	SUBSTRACTION, // -
	MULTIPLICATION, // *
	DIVISION, // /
	// LATER
	REMAINDER, // %
	POST_INCR, // a++
	POST_DECR, // a--
	PRE_INCR,  // ++a
	PRE_DECR,  // --a
	BITWISE_NEG, // ~
	BITWISE_AND, // &
	BITWISE_OR, // ^
	BITSHIFT_LEFT, // <<
	BITSHIFT_RIGHT, // >>
	EXPONENTIAL, // **
	COMP_INF, // <
	COMP_INF_EQ, // <=
	COMP_SUP, // >
	COMP_SUP_EQ, // >=
	LOGIC_NEG, // !
	EQUALITY, // ==
	INEQUALITY, // !=
	LOGIC_AND, // &&
	LOGIC_OR, // ||
	TERNARY, // a ? b : c
	CONDITIONAL, // = *= /= %= += -= <<= >>= &= ^= |=
	ASSIGNEMENTS, // ,
	UNDEF
} Operator;


typedef enum Token_type {
	NUM,
	OPERATOR
} Token_type;

typedef struct s_operations_ll {
	Token_type type;
	Operator op_type;
	int value;
	int index;
	struct s_operations_ll *next;
} t_operations_ll;

// is_math.c
bool	is_math(const char *cmd);
// clean_input.c
char *clean_input(const char *cmd);
// char_checking.c
bool is_newline(char c);
bool is_spc(char c);
bool is_operator(char c);
bool is_alpha(char c);
bool is_digit(char c);
// char_checking2.c
bool is_varname_char(char c);
// operations_ll.c
void operation_add(t_operations_ll *newest, t_operations_ll **ops);
// utils.c
bool print_math_error(char *input, char *error_message, int error_index);
// assign.c
t_operations_ll *assign_digit(const char *cleaned, int *i);
t_operations_ll *assign_operator(const char *cleaned, int *i);
t_operations_ll *assign_var(const char *cleaned, t_env *env, int *i);
// operator.c
Operator find_optype(const char *operator_str);
// TODO delete math_delete.c
void print_ops(t_operations_ll *ops);

#endif
