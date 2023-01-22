/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: songmengrui <songmengrui@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:12:57 by songmengrui       #+#    #+#             */
/*   Updated: 2023/01/17 12:44:09 by songmengrui      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
  int ret;
  static char *save;// chars left

  // if the conditions below are satisfied, return error:
  // 1. fd (file descriptor) is negative
        // https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
        // File descriptor is integer that uniquely identifies an open file of the process.
  // 2. line is null
  // 3. BUFFER_SIZE is equal or less than zero
  // 4. failed to initialize line
  if (fd < 0 || !line || BUFFER_SIZE <= 0 || !(*line = ft_strdup("")))
    return (ERROR); // -1
  ret = CONTINUE_READ; //-2
	// if save is not empty
  if (save)
    ret = join_line_and_save(line, &save);
	// if ret == CONTINUE_READ
  if (ret == CONTINUE_READ)
    ret = read_process(fd, line, &save);
  return (ret);
}

static int	join_line_and_save(char **line, char **save)
{
	char *tmp;
	char *newline_p;

	// check if there is '\n' in *save
	*newline_p = *ft_strrchr(*save, '\n');
	// if there is '\n' in *save
	if (*newline_p)
	{
		tmp = *line;
		// *line = save_before_n
		*line = ft_substr(*save, 0, newline_p - *save);
		free(tmp);
		if (!(*line))
			return (ERROR);
		tmp = *save;
		// *save = save_after_n
		*save = ft_substr(newline_p + 1, 0, ft_strlen(newline_p + 1));
		free(tmp);
		if (!(*save))
			return (ERROR);
		return (SUCCESS);
	}
	// if there is no '\n' in *save
	else
	{
		// *line = *save, *save = NULL
		// return CONTINUE_READ
		tmp = *line;
		*line = *save;
		*save = NULL;
		free(tmp);
		return (CONTINUE_READ);
	}

}

static int	read_process(int fd, char **line, char **save)
{
	ssize_t	read_size;
	int			ret;
	char *buf;

// ret == CONTINUE_READ だったら fdからBUFFER_SIZE分文字を読み込み buf に入れる.
// もし buf の中に改行文字が入っていたら split_by_newline() を呼び出して改行文字までを line と結合し, 残りを save に入れてループを抜ける. (ret == SUCCESS になるから)
// もし buf の中に改行文字が入っていなかったら join_line_and_buf() を呼び出して単純に line と buf を結合する.
// ループ処理終了後, もし ret == CONTINUE_READ && read_size == 0 だったら, これすなわち改行は見つからずにfdがEOFに達したということを意味するので END_OF_FILE を返す.
// read_size == -1 ということは読み込みに失敗しているのでERRORを返す.
// 上記2つのif文の条件を通過したということは正常に終了したかEOFに到達したということなのでそのまま ret を返す.
	ret = CONTINUE_READ;
	while (ret == CONTINUE_READ && read_size = read(fd, buf, BUFFER_SIZE))
	{
		buf[read_size] = '\0';
		if (ft_strrchr(buf, '\n'))
			ret = split_by_newline(line, save, buf);
		else
			ret = join_line_and_buf(line, buf);
	}
	free(buf);
	if (ret == CONTINUE_READ && read_size == 0)
		ret = END_OF_FILE;
	else if (ret == CONTINUE_READ && read_size == -1)
		ret = ERROR
	return (ret);
}

int	split_by_newline(char **line, char **save, char *buf)
{
	char	*new_line_p;
	char	*before_newline;
	char	*after_newline;

	*new_line_p = ft_strrchr(buf, '\n');
	*before_newline = ft_substr(buf, 0, new_line_p - buf);
	*after_newline = ft_substr(buf, new_line_p - buf, ft_strlen(buf));
	*line = ft_strjoin(*line, before_newline);
	*save = ft_strjoin(*save, after_newline);
}