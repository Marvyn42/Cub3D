/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:30:35 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:30:38 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_zeros(t_game *game, t_pos zero, int nb_lines)
{
	if (game->map[zero.y][zero.x] == '0' || game->map[zero.y][zero.x] == '2')
	{
		if (zero.y == 0 || zero.x == 0)
			return (set_error(game, ERR_MAP));
		if (((int)ft_strlen(game->map[zero.y - 1]) >= zero.x
			&& game->map[zero.y - 1][zero.x] == ' ')
			|| game->map[zero.y][zero.x - 1] == ' '
			|| (zero.y < nb_lines - 1
				&& (int)ft_strlen(game->map[zero.y + 1]) >= zero.x
				&& game->map[zero.y + 1][zero.x] == ' ')
			|| ((int)ft_strlen(game->map[zero.y]) > zero.x
				&& game->map[zero.y][zero.x + 1] == ' ')
			|| (zero.y < nb_lines - 1
				&& (int)ft_strlen(game->map[zero.y + 1]) < zero.x)
			|| (int)ft_strlen(game->map[zero.y - 1]) < zero.x)
		{
			return (set_error(game, ERR_MAP));
		}
	}
	return (1);
}

int			check_player(t_game *game)
{
	int	x;
	int	y;

	game->player.pos = (t_pos){-1, -1};
	y = 1;
	while (game->map[y] && game->map[y + 1])
	{
		x = 1;
		while (x < (int)ft_strlen(game->map[y]) - 1)
		{
			if (is_player(game, x, y))
			{
				if (game->player.pos.x != -1 || game->player.pos.y != -1)
					return (set_error(game, ERR_MAP));
				game->player.pos = (t_pos){ x, y };
			}
			x++;
		}
		y++;
	}
	if (game->player.pos.x == -1 || game->player.pos.y == -1)
		return (set_error(game, ERR_MAP));
	return (1);
}

int			find_zeros(t_game *game)
{
	t_pos	zero;
	int		nb_lines;

	nb_lines = 0;
	zero.y = 0;
	while (game->map[zero.y])
	{
		nb_lines++;
		zero.y++;
	}
	zero.y = 0;
	while (game->map[zero.y])
	{
		zero.x = 0;
		while (zero.x < (int)ft_strlen(game->map[zero.y]))
		{
			if (!check_zeros(game, zero, nb_lines))
				return (set_error(game, ERR_MAP));
			zero.x++;
		}
		zero.y++;
	}
	return (1);
}

int			check_closed_map(t_game *game)
{
	if (!check_horizontaly_begin(game))
		return (set_error(game, ERR_MAP));
	if (!check_horizontaly_end(game))
		return (set_error(game, ERR_MAP));
	if (!check_verticaly_begin(game))
		return (set_error(game, ERR_MAP));
	if (!check_verticaly_end(game))
		return (set_error(game, ERR_MAP));
	return (1);
}
