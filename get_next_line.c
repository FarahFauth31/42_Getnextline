/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:57:32 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/01/05 13:56:44 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *str)
{
	int		i;
	int		j;
	char	*line;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_get_rest(char *str, char *line)
{
	char	*rest;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = ft_strlen(line);
	j = 0;
	while (str[i + j] != '\0')
		j++;
	rest = (char *)malloc((j + 1) * sizeof(char));
	if (!rest)
	{
		free (str);
		return (NULL);
	}
	j = 0;
	while (str[i + j] != '\0')
	{
		rest[j] = str[i + j];
		j++;
	}
	rest[j] = '\0';
	free (str);
	return (rest);
}

char	*ft_join_and_free(char *str, char *buffer, int bytes_read)
{
	char	*temp;

	if (bytes_read == -1)
		return (ft_read_error(str, buffer));
	buffer[bytes_read] = '\0';
	if (!str)
	{
		if (buffer[0] != '\0')
			return (buffer);
		free (buffer);
		return (NULL);
	}
	if (buffer[0] == '\0' && str[0] == '\0')
	{
		free(buffer);
		free(str);
		return (NULL);
	}
	temp = ft_strjoin(str, buffer);
	free(str);
	free(buffer);
	return (temp);
}

char	*ft_get_text(int fd, char *str)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
		{
			if (str != NULL)
				free(str);
			return (NULL);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		str = ft_join_and_free(str, buffer, bytes_read);
		if (!str)
			return (NULL);
		if (ft_strchr(str, '\n') != NULL || bytes_read != BUFFER_SIZE)
			return (str);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fd >= 0 && BUFFER_SIZE > 0)
	{
		if (str != NULL)
		{
			if (ft_strchr(str, '\n') != NULL)
			{
				line = ft_get_line(str);
				str = ft_get_rest(str, line);
				return (line);
			}
		}
		str = ft_get_text(fd, str);
		line = ft_get_line(str);
		str = ft_get_rest(str, line);
		return (line);
	}
	return (NULL);
}
