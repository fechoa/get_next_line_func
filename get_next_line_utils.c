/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkelsie <gkelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:26:35 by gkelsie           #+#    #+#             */
/*   Updated: 2021/10/15 21:09:05 by gkelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*result;
	size_t	i;

	i = 0;
	result = (char *) malloc(count * size);
	if (result == NULL)
		return ((void *)(0));
	while (i < count)
	{
		result[i] = '\0';
		i++;
	}
	return ((void *) result);
}

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	i;
	size_t	maxlen;

	maxlen = ft_strlen(s1);
	if (maxlen > 0)
		result = (char *) ft_calloc(maxlen + 1, 1);
	else
	{
		result = (char *) malloc(1);
		result[0] = '\0';
		return (result);
	}
	if (result == NULL)
	{
		errno = ENOMEM;
		return ((void *)(0));
	}
	i = -1;
	while (++i < maxlen)
		result[i] = (char) s1[i];
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *) &s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		result = (char *) malloc(1);
		result[0] = '\0';
		return (result);
	}
	if (ft_strlen(s) - (size_t)start < len)
		result = (char *) malloc((ft_strlen(s) - (size_t)start + 1));
	else
		result = (char *) malloc(len + 1);
	if (result == NULL)
		return (result);
	i = -1;
	while (++i < len && s[start] != '\0')
	{
		result[i] = s[start];
		start++;
	}
	result[i] = '\0';
	return (result);
}
