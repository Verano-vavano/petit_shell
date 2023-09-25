/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:27:21 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/25 12:20:53 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "colors.h"

static char	*change_color(char c)
{
	c = (c * (c <= 'z' && c >= 'a')) + ((c + ('a' - 'A')) * (c <= 'Z' && c>= 'A'));
	if (c == 'n')
		return (ft_strdup(BLACK));
	else if (c == 'r')
		return (ft_strdup(RED));
	else if (c == 'g')
		return (ft_strdup(GREEN));
	else if (c == 'y')
		return (ft_strdup(YELLOW));
	else if (c == 'b')
		return (ft_strdup(BLUE));
	else if (c == 'p')
		return (ft_strdup(PURPLE));
	else if (c == 'c')
		return (ft_strdup(CYAN));
	else
		return (ft_strdup(WHITE));
}

static bool	color_param(char c, t_color *colors)
{
	if (c == 'i' || c == '2')
		colors->italic = true;
	else if (c == 's' || c == '3')
		colors->underlined = true;
	else if (c == 'd' || c == '4')
		colors->blinking = true;
	else if (c == 'I' || c == '5')
		colors->inverted = true;
	else if (c == '1')
		colors->bold = true;
	else if (c == '0')
		return (0);
	else
		return (1);
	return (0);
}

static char	*clean_strjoin(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}

static char	*add_params(t_color *colors)
{
	char	*ret;

	ret = ft_strdup(START_COLOR);
	if (ret && colors->bold)
		ret = clean_strjoin(ret, BOLD_C);
	if (ret && colors->italic)
		ret = clean_strjoin(ret, ITALIC_C);
	if (ret && colors->underlined)
		ret = clean_strjoin(ret, ULINED_C);
	if (ret && colors->blinking)
		ret = clean_strjoin(ret, BLINK_C);
	if (ret && colors->inverted)
		ret = clean_strjoin(ret, INVERT_C);
	if (ret && ft_strcmp(ret, START_COLOR) == 0)
		ret = clean_strjoin(ret, NORMAL_C);
	return (ret);
}

char	*prompt_color(char *s, int *to_repl)
{
	t_color	*colors;
	bool	num;
	char	*to_ret;
	char	*color_code;

	(*to_repl)++;
	colors = ft_calloc(1, sizeof (t_color));
	num = is_num(*s);
	while (*s && ((num && is_num(*s)) || (!num && !is_num(*s))))
	{
		if (color_param(*s, colors))
			break ;
		(*to_repl)++;
		s++;
	}
	if (!colors->bold)
		colors->bold = (*s <= 'Z' && *s >= 'A');
	to_ret = add_params(colors);
	if (colors)
		free(colors);
	if (!to_ret)
		return (0);
	color_code = change_color(s[0]);
	if (!color_code)
	{
		free(to_ret);
		return (0);
	}
	to_ret = clean_strjoin(to_ret, color_code);
	free(color_code);
	if (!to_ret)
		return (0);
	color_code = clean_strjoin(to_ret, END_COLOR);
	return (color_code);
}
