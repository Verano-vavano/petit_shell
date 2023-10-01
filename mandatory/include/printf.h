/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:18:17 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/30 15:19:41 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

typedef struct s_printf_flags
{
	bool	sharp;
	bool	zero;
	bool	minus;
	bool	space;
	int		field_length;
	int		accuracy;
	char	format;
}				t_printf_flags;

#endif
