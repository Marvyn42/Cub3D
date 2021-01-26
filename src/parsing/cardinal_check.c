/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:30:24 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:30:28 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		find_max(t_game *game, int *max_x, int *max_y)
{
	int	x;

	*max_x = 0;
	*max_y = 0;
	while (game->map[*max_y])
	{
		x = ft_strlen(game->map[*max_y]);
		if (x > *max_x)
			*max_x = x;
		*max_y += 1;
	}
}

int			check_horizontaly_begin(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x] == ' ')
			x++;
		if (game->map[y][x] && game->map[y][x] != '1')
			return (0);
		y++;
	}
	return (1);
}

int			check_horizontaly_end(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = ft_strlen(game->map[y]) - 1;
		while (x && game->map[y][x] == ' ')
			x--;
		if (x && game->map[y][x] != '1')
			return (0);
		y++;
	}
	return (1);
}

int			check_verticaly_begin(t_game *game)
{
	int	x;
	int	y;
	int	max_y;
	int	max_x;

	find_max(game, &max_x, &max_y);
	x = 0;
	while (x < max_x)
	{
		y = 0;
		while (game->map[y] && (x >= (int)ft_strlen(game->map[y])
				|| game->map[y][x] == ' '))
			y++;
		if (game->map[y] && x >= (int)ft_strlen(game->map[y]) && y <= max_y
				&& game->map[y][x] != '1' && game->map[y][x] != ' ')
			return (0);
		x++;
	}
	return (1);
}

int			check_verticaly_end(t_game *game)
{
	int	x;
	int	y;
	int	max_y;
	int	max_x;

	find_max(game, &max_x, &max_y);
	x = 0;
	while (x < max_x)
	{
		y = max_y - 1;
		while (y && game->map[y] && (x >= (int)ft_strlen(game->map[y])
				|| game->map[y][x] == ' '))
			y--;
		if (y && game->map[y] && game->map[y][x] != '1'
				&& game->map[y][x] != ' ')
			return (0);
		x++;
	}
	return (1);
}
