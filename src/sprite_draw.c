/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:32:54 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:32:55 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_sprite(t_game *game, t_calc_sprite *cs)
{
	cs->side = 64 * game->res.y / game->sprites[cs->sprite_curr].dist;
	cs->col_width = cs->side / 64.0;
	cs->y_begin = game->res.y -
			(game->res.y / 2 - ((64 * game->res.y) /
				game->sprites[cs->sprite_curr].dist)) -
			cs->side - cs->side / 2;
	cs->x_begin = (
		(double)(game->res.x / 2.0) + tan(
			atan2(game->sprites[cs->sprite_curr].pos.y - game->player.pos.y,
				game->sprites[cs->sprite_curr].pos.x - game->player.pos.x) -
				game->player.angle) *
			(double)(game->res.x / 2.0) / tan(FOV / 2.0 * DEG) - cs->side / 2);
}

static void	print_sprite(t_game *game, t_calc_sprite *cs)
{
	cs->x_curr = cs->x_begin;
	while (cs->x_curr < cs->x_begin + (int)cs->side)
	{
		if (cs->x_curr >= 0 && cs->x_curr < game->res.x &&
			game->sprites[cs->sprite_curr].dist < game->dists[cs->x_curr])
		{
			cs->y_curr = cs->y_begin;
			while (cs->y_curr < cs->y_begin + cs->side)
			{
				cs->color = *((unsigned int*)(game->sprite_data.data_addr) +
						((int)((cs->y_curr - cs->y_begin) / cs->col_width) *
						game->sprite_data.res.x) +
						(int)((cs->x_curr - cs->x_begin) / cs->col_width));
				if (cs->color && cs->y_curr >= 0 && cs->y_curr < game->res.y)
				{
					cs->col = (t_color){(cs->color & 0xFF0000) >> 16,
						(cs->color & 0x00FF00) >> 8, cs->color & 0x0000FF};
					put_pixel(game, cs->x_curr, cs->y_curr, cs->col);
				}
				cs->y_curr++;
			}
		}
		cs->x_curr++;
	}
}

void		draw_sprite(t_game *game)
{
	t_calc_sprite	cs;

	cs.sprite_curr = 0;
	while (cs.sprite_curr < game->nb_sprite)
	{
		if (game->sprites[cs.sprite_curr].visible)
		{
			calc_sprite(game, &cs);
			print_sprite(game, &cs);
		}
		cs.sprite_curr++;
	}
}
