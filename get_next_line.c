/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a1111 <a1111@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:25:58 by gkelsie           #+#    #+#             */
/*   Updated: 2021/12/25 20:14:49 by a1111            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	result = NULL;
	if (s1 == NULL)
		result = ft_strdup(s2);
	else if (s2 == NULL)
		result = ft_strdup(s1);
	else
	{
		result = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (result == NULL)
			return (result);
		while (s1[++i])
			result[i] = s1[i];
		while (s2[j] != '\0')
			result[i++] = s2[j++];
		result[i] = '\0';
	}
	return (result);
}

static char	*ft_line(char *remainder, char **string, size_t index)
{
	char	*result;

	result = NULL;
	while ((remainder[index] != '\n') && (remainder[index++] != '\0'))
		;
	if (remainder[index] == '\n')
	{
		*string = ft_substr(remainder, 0, index + 1);
		result = ft_strdup(&remainder[index + 1]);
	}
	else
		*string = ft_strdup(remainder);
	free(remainder);
	remainder = NULL;
	return (result);
}

static size_t	ft_reading(int fd, char *buff, char **string, char **remainder)
{
	char	*tmp;
	size_t	read_size;

	read_size = 666;
	while (ft_strchr(*remainder, '\n') == 0 && read_size > 0)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		buff[read_size] = '\0';
		tmp = *remainder;
		*remainder = ft_strjoin(tmp, buff);
		free(tmp);
		tmp = NULL;
	}
	free(buff);
	buff = NULL;
	*remainder = ft_line(*remainder, string, 0);
	if (*string[0] != '\0')
		return (read_size);
	free(*string);
	*string = NULL;
	return (read_size);
}

char	*get_next_line(int fd)
{
	char			*buff;
	char			*string;
	static char		*remainder;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	if (read(fd, buff, 0) < 0)
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	if (remainder == NULL)
		remainder = ft_strdup("");
	if (ft_reading(fd, buff, &string, &remainder) == 0 && string == NULL)
		return (NULL);
	return (string);
}
