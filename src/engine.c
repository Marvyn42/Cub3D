/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:31:46 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:31:47 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_h_direction(t_game *game, t_dda *dda)
{
	double	atan;

	atan = -1 / tan(dda->ray.a);
	if (dda->ray.a > M_PI)
	{
		dda->ray.y = (((int)game->player.pos.y >> 6) << 6) - 0.0001;
		dda->ray.x = (game->player.pos.y - dda->ray.y) * atan
				+ game->player.pos.x;
		dda->offset.y = -64;
		dda->offset.x = -dda->offset.y * atan;
	}
	else if (dda->ray.a < M_PI)
	{
		dda->ray.y = (((int)game->player.pos.y >> 6) << 6) + 64;
		dda->ray.x = (game->player.pos.y - dda->ray.y) * atan
				+ game->player.pos.x;
		dda->offset.y = 64;
		dda->offset.x = -dda->offset.y * atan;
	}
	else
	{
		dda->ray.x = game->player.pos.x;
		dda->ray.y = game->player.pos.y;
		dda->limit = dda->max.x;
	}
}

void		dda_horizontal(t_game *game, t_dda *dda)
{
	dda->dist_h = 1000000;
	dda->limit = 0;
	dda_h_direction(game, dda);
	while (dda->limit < dda->max.y)
	{
		dda->map_pos.x = (int)dda->ray.x >> 6;
		dda->map_pos.y = (int)dda->ray.y >> 6;
		if (dda->map_pos.x < dda->max.x && dda->map_pos.y < dda->max.y
				&& dda->map_pos.x >= 0 && dda->map_pos.y >= 0
				&& dda->map_pos.x < (int)ft_strlen(game->map[dda->map_pos.y])
				&& game->map[dda->map_pos.y][dda->map_pos.x] == '1')
		{
			dda->inter_h.x = dda->ray.x;
			dda->inter_h.y = dda->ray.y;
			dda->dist_h = dist(game, dda->inter_h);
			dda->limit = dda->max.y;
		}
		else
		{
			dda->ray.x += dda->offset.x;
			dda->ray.y += dda->offset.y;
			dda->limit += 1;
		}
	}
}

static void	dda_v_direction(t_game *game, t_dda *dda)
{
	double	ntan;

	ntan = -tan(dda->ray.a);
	if (dda->ray.a > M_PI_2 && dda->ray.a < 3 * M_PI_2)
	{
		dda->ray.x = (((int)game->player.pos.x >> 6) << 6) - 0.0001;
		dda->ray.y = (game->player.pos.x - dda->ray.x) * ntan
				+ game->player.pos.y;
		dda->offset.x = -64;
		dda->offset.y = -dda->offset.x * ntan;
	}
	else if (dda->ray.a < M_PI_2 || dda->ray.a > 3 * M_PI_2)
	{
		dda->ray.x = (((int)game->player.pos.x >> 6) << 6) + 64;
		dda->ray.y = (game->player.pos.x - dda->ray.x) * ntan
				+ game->player.pos.y;
		dda->offset.x = 64;
		dda->offset.y = -dda->offset.x * ntan;
	}
	else
	{
		dda->ray.x = game->player.pos.x;
		dda->ray.y = game->player.pos.y;
		dda->limit = dda->max.y;
	}
}

void		dda_vertical(t_game *game, t_dda *dda)
{
	dda->dist_v = 1000000;
	dda->limit = 0;
	dda_v_direction(game, dda);
	while (dda->limit < dda->max.x)
	{
		dda->map_pos.x = (int)dda->ray.x >> 6;
		dda->map_pos.y = (int)dda->ray.y >> 6;
		if (dda->map_pos.x < dda->max.x && dda->map_pos.y < dda->max.y
			&& dda->map_pos.x >= 0 && dda->map_pos.y >= 0
			&& dda->map_pos.x < (int)ft_strlen(game->map[dda->map_pos.y])
			&& game->map[dda->map_pos.y][dda->map_pos.x] == '1')
		{
			dda->inter_v.x = dda->ray.x;
			dda->inter_v.y = dda->ray.y;
			dda->dist_v = dist(game, dda->inter_v);
			dda->limit = dda->max.x;
		}
		else
		{
			dda->ray.x += dda->offset.x;
			dda->ray.y += dda->offset.y;
			dda->limit += 1;
		}
	}
}

void		find_intersection(t_game *game)
{
	if (game->dda.dist_v < game->dda.dist_h)
	{
		game->dda.ray.x = game->dda.inter_v.x;
		game->dda.ray.y = game->dda.inter_v.y;
		game->dda.dist_t = game->dda.dist_v;
	}
	if (game->dda.dist_h < game->dda.dist_v)
	{
		game->dda.ray.x = game->dda.inter_h.x;
		game->dda.ray.y = game->dda.inter_h.y;
		game->dda.dist_t = game->dda.dist_h;
	}
}
