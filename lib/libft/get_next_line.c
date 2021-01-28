/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:55:35 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/28 17:32:39 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_check_buffer_nl(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char		*ftm_strjoin(char *s1, char const *s2)
{
	char	*joined;
	size_t	size;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	while (s1 && s1[i])
		i++;
	size = i;
	i = 0;
	while (s2 && s2[i])
		i++;
	size += i;
	joined = malloc(sizeof(char) * (size + 1));
	if (joined == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		*joined++ = s1[i++];
	while (s2 && *s2)
		*joined++ = *s2++;
	*joined = 0;
	free(s1);
	return (joined - size);
}

static char		*prep_line(char *buff, char *line_result, int len)
{
	char	*line_end;
	int		i;

	i = 0;
	line_end = malloc(sizeof(char) * (len + 1));
	if (line_end == NULL)
		return (NULL);
	len = 0;
	while (buff[len] != '\n')
	{
		line_end[len] = buff[len];
		len++;
	}
	line_end[len] = 0;
	while (buff[++len])
	{
		buff[i] = buff[len];
		i++;
	}
	buff[i] = 0;
	if (!(line_result = ftm_strjoin(line_result, line_end)))
		return (NULL);
	free(line_end);
	return (line_result);
}

static int		ft_read_line(int fd, char **line, char *buff, char *line_result)
{
	int len;
	int ret;

	ret = 1;
	while ((len = ft_check_buffer_nl(buff)) == -1 && ret > 0)
	{
		if (!(line_result = ftm_strjoin(line_result, buff)))
			return (-1);
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		buff[ret] = 0;
	}
	if ((len = ft_check_buffer_nl(buff)) != -1)
	{
		if (!(*line = prep_line(buff, line_result, len)))
			return (-1);
		return (1);
	}
	if (!(*line = ftm_strjoin(line_result, buff)))
		return (-1);
	if (ret == 0)
		return (0);
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	static char	buff[256][BUFFER_SIZE + 1];
	char		*line_result;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > 256 || read(fd, 0, 0) < 0 || !line)
		return (-1);
	line_result = malloc(sizeof(char) * 1);
	if (line_result == NULL)
		return (-1);
	line_result[0] = '\0';
	return (ft_read_line(fd, line, buff[fd], line_result));
}
