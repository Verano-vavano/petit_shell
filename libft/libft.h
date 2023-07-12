/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:13:50 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/12 12:20:44 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*free_buffers(char *buf1, ...);
int		ft_strchr_int(const char *s, int c);
char	*ft_itoa(int n);
char	*get_next_line(int fd);
long	ft_atol(const char *s);
int		ft_atoi(const char *s);
int		is_dgt(char c);
void	free_char_etoile_etoile(char **truc);

#endif
