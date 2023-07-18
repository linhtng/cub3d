/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:56:41 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/21 16:56:48 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
size_t	ft_gnl_strlen(const char *str);
char	*ft_gnl_strjoin(char *s1, char const *s2, int len);
void	*ft_gnl_memmove(void *dst, const void *src, size_t len);
char	*ft_gnl_strdup(const char *src);
char	*ft_gnl_substr(char const *s, unsigned int start, size_t len);

#endif
