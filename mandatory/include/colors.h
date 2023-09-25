/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:26:25 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/25 12:09:30 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define START_COLOR "\001\e["
# define END_COLOR "\002"

# define BLACK "30m"
# define RED "31m"
# define GREEN "32m"
# define YELLOW "33m"
# define BLUE "34m"
# define PURPLE "35m"
# define CYAN "36m"
# define WHITE "37m"

# define NORMAL_C "0;"
# define BOLD_C "1;"
# define ITALIC_C "3;"
# define ULINED_C "4;"
# define BLINK_C "5;"
# define INVERT_C "7;"

typedef struct s_color
{
	bool	bold;
	bool	italic;
	bool	underlined;
	bool	blinking;
	bool	inverted;
}				t_color;

#endif
