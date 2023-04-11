/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkayis <tkayis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:41:39 by tkayis            #+#    #+#             */
/*   Updated: 2023/04/06 18:53:51 by tkayis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*lemme_holddat(char *str)
{
	char	*imadiff_kind;
	int		k;
	int		y;

	k = 0;
	while (str[k] && str[k] != '\n')
		k++;
	if (!str[k])
	{
		free(str);
		return (NULL);
	}
	imadiff_kind = (char *)malloc(sizeof(char) * (ft_strlen(str) - k + 1));
	if (!imadiff_kind)
		return (NULL);
	k++;
	y = 0;
	while (str[k])
		imadiff_kind[y++] = str[k++];
	imadiff_kind[y] = 0;
	free(str);
	return (imadiff_kind);
}

char	*gimme_output(char *str)
{
	char	*result;
	int		j;

	j = 0;
	if (!str[j])
		return (NULL);
	while (str[j] && str[j] != '\n')
		j++;
	result = (char *)malloc(sizeof(char) * (j + 2));
	if (!result)
		return (NULL);
	j = 0;
	while (str[j] && str[j] != '\n')
	{
		result[j] = str[j];
		j++;
	}
	if (str[j] == '\n')
	{
		result[j] = str[j];
		j++;
	}
	result[j] = 0;
	return (result);
}

char	*read_da_text(char *str, int fd)
{
	char	*buffer;
	int		i;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	i = 1;
	while (!ft_strchr(str, '\n') && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[i] = 0;
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = read_da_text(str, fd);
	if (!str)
		return (NULL);
	output = gimme_output(str);
	str = lemme_holddat(str);
	return (output);
}
