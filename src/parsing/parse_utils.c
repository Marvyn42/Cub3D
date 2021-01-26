/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:30:49 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:30:51 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parsed_data(int *parsing)
{
	int index;

	index = 0;
	while (index < 8)
	{
		if (!parsing[index])
			return (0);
		index++;
	}
	return (1);
}

int		find_elem(char **words, const char **tab)
{
	int	i;

	i = 0;
	while (tab[i] && words[0])
	{
		if (!ft_strncmp(tab[i], words[0], ft_strlen(words[0]) + 1))
			return (i);
		i++;
	}
	return (-1);
}

int		line_is_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		is_player(t_game *game, int x, int y)
{
	const char		key[5] = {'N', 'S', 'E', 'W', '\0'};
	const double	value[4] = {M_PI_2, -M_PI_2, 0, M_PI};
	int				i;

	i = 0;
	while (i < (int)ft_strlen(key) && game->map[y][x] != key[i])
		i++;
	if (i == (int)ft_strlen(key))
		return (0);
	game->player.angle = value[i];
	return (1);
}

char	*fill_buffer(char *line)
{
	static char	*buff = NULL;
	char		*tmp;

	if (!buff)
		buff = ft_strdup("");
	if (!ft_strlen(line) && !ft_strlen(buff))
		return (buff);
	else if (ft_strlen(line) && !ft_strlen(buff) && line_is_spaces(line))
		return (buff);
	tmp = buff;
	buff = ft_strjoin(tmp, line);
	ft_free(tmp);
	tmp = buff;
	if (!ft_strlen(line))
		buff = ft_strjoin(tmp, " \n");
	else
		buff = ft_strjoin(tmp, "\n");
	ft_free(tmp);
	return (buff);
}
