/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_char_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:32:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/05 13:33:30 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	convert_to_closing(char c)
{
	if (c == '(')
		return (')');
	else if (c == '{')
		return ('}');
	return (c);
}
