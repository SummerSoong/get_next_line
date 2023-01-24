/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: songmengrui <songmengrui@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:06:46 by songmengrui       #+#    #+#             */
/*   Updated: 2023/01/24 22:20:43 by songmengrui      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc and free
#include <unistd.h> // read

// if BUFFER_SIZE is not defined, define it as 256
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
# endif

# define ERROR -1
# define CONTINUE_READ -2
# define SUCCESS 1
# define END_OF_FILE 0

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char*s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

int check_newline(char *str);
char *seperate_by_newline(char *source, char **before);
char	*read_buffer(int fd, char **save, char *line);
char	*read_save(int fd, char **save, char *line);
char	*get_next_line(int fd);