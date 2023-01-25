/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: songmengrui <songmengrui@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:13:54 by songmengrui       #+#    #+#             */
/*   Updated: 2023/01/25 18:07:01 by songmengrui      ###   ########.fr       */
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

char	*ft_strdup(const char*s1)
{
	char	*str;
	size_t	s1_size;
	size_t	i;

	s1_size = ft_strlen(s1) + 1;
	str = malloc (sizeof(char) * s1_size);
	if (!str)
		return (NULL);
	else
	{
		i = 0;
		while (i < s1_size - 1 && s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	s = src;
	if (s < d)
	{
		i = 0;
		while (i++ <= n)
			d[n - i] = s[n - i];
	}
	else
	{
		i = -1;
		while (i++ < n)
			d[i] = s[i];
	}
	return ((void *)d);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start + len > s_len)
		len = s_len - start;
	if (start >= s_len || len == 0)
		return (ft_strdup(""));
	str = malloc (sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_memmove (str, s + start, len);
	str[len] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (i++ < ft_strlen(s1) && s1[i])
	{
		str[i] = s1[i];
	}
	while (i++ < (ft_strlen(s1) + ft_strlen(s2) - ft_strlen(str)) && s2[i])
	{
		str[i + ft_strlen(s2)] = s2[i];
	}
	str[i] = '\0';
	return (str);
}
