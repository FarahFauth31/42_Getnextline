/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:09:28 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/01/07 13:54:16 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int				count_str;

	count_str = 0;
	while (s[count_str] != '\0')
	{
		if (s[count_str] == (unsigned char)c)
			return ((char *) &s[count_str]);
		count_str++;
	}
	if ((unsigned char)c == 0)
		return ((char *) &s[count_str]);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s = (s + 1);
	}
	return (count);
}

static char	*ft_strconcat(char const *s1, char const *s2, char *strjoin)
{
	int	count;
	int	src_count;

	count = 0;
	src_count = 0;
	while (s1[src_count] != '\0')
	{
		strjoin[count] = s1[src_count];
		src_count++;
		count++;
	}
	src_count = 0;
	while (s2[src_count] != '\0')
	{
		strjoin[count] = s2[src_count];
		src_count++;
		count++;
	}
	strjoin[count] = '\0';
	return (strjoin);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*strjoin;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strjoin = (char *) malloc ((len1 + len2 + 1) * sizeof(char));
	if (!(strjoin))
		return (NULL);
	strjoin = ft_strconcat(s1, s2, strjoin);
	return (strjoin);
}

char	*ft_read_error(char *str, char *buffer)
{
	if (str != NULL)
		free(str);
	if (buffer != NULL)
	{
		buffer[0] = '\0';
		free(buffer);
	}
	return (NULL);
}
