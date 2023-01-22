# include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	if (dstsize == 0)
		return (ft_strlen(src) + dstsize);
	dst_len = ft_strlen (dst);
	src_len = ft_strlen (src);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	ft_strlcpy(dst + dst_len, src, dstsize - dst_len);
	return (dst_len + src_len);
}

char	*ft_strdup(const char*s1)
{
	char	*str;
	size_t	s1_size;

	s1_size = ft_strlen(s1) + 1;
	str = malloc (sizeof(char) * s1_size);
	if (!str)
		return (NULL);
	else
		ft_strlcpy (str, s1, s1_size);
	return (str);
}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((void *)d);
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
	i = 1;
	if (s < d)
	{
		while (i <= n)
		{
			d[n - i] = s[n - i];
			i++;
		}
		return ((void *)d);
	}
	else
		ft_memcpy(dst, src, n);
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
	size_t	s1_size;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	s1_size = ft_strlen(s1);
	size = s1_size + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1_size + 1);
	ft_strlcat(str, s2, size);
	return (str);
}