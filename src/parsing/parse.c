/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:31:01 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:31:03 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_data_parsed(int *data_parsed)
{
	int	index;

	index = 0;
	while (index < 8)
	{
		data_parsed[index] = 0;
		index++;
	}
}

void		global_parse(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		data_parsed[8];
	char	*buffer;

	init_data_parsed(data_parsed);
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (parsed_data(data_parsed))
			buffer = fill_buffer(line);
		else if (line)
			parse_data(line, game, data_parsed);
		ft_free(line);
	}
	if (parsed_data(data_parsed))
		buffer = fill_buffer(line);
	ft_free(line);
	if (!parse_map(game, buffer))
	{
		ft_free(buffer);
		ft_error(game);
	}
	ft_free(buffer);
	close(fd);
}

void		parse_data(char *line, t_game *game, int *data_parsed)
{
	const char	*tab[9] = {"R", "NO", "SO", "WE", "EA", "S", "F", "C", 0};
	int			(*const tab_f[8])(t_game *, char **, int) = {
		fill_resolution, fill_texture, fill_texture, fill_texture,
		fill_texture, fill_texture, fill_color, fill_color};
	char		**words;
	int			index;

	if (ft_strlen(line) > 0)
	{
		words = ft_split_charset(line, ft_get_whitespaces());
		index = find_elem(words, tab);
		if ((index >= 0 && !(data_parsed[index] = tab_f[index](game,
			words, index)))
			|| (index == -1 && words[0]))
		{
			free_split(words);
			ft_free(line);
			set_error(game, ERR_DATA);
			ft_error(game);
		}
		free_split(words);
	}
}

int			parse_map(t_game *game, char *buffer)
{
	int	index;

	index = 0;
	while (buffer[index])
		index++;
	index--;
	if (index < 0)
		return (set_error(game, ERR_MAP));
	while (buffer[index] == '\n' || buffer[index] == ' ')
	{
		buffer[index] = '\0';
		index--;
	}
	game->map = ft_split(buffer, '\n');
	if (!check_player(game))
		return (set_error(game, ERR_MAP));
	if (!find_zeros(game))
		return (set_error(game, ERR_MAP));
	if (!check_closed_map(game))
		return (set_error(game, ERR_MAP));
	return (1);
}
