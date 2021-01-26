/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:39:32 by agautier          #+#    #+#             */
/*   Updated: 2021/01/26 16:29:35 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_sprite(t_game *game)
{
	int		sprite_curr;
	double	side;
	int		y_begin;
	int		y_curr;
	int		x_begin;
	int		x_curr;
	double	col_width;
	t_color col;
	unsigned int color;

	sprite_curr = 0;
	while (sprite_curr < game->nb_sprite)
	{
		if (game->sprites[sprite_curr].visible)
		{
			side = 64 * game->res.y / game->sprites[sprite_curr].dist;
			col_width = side / 64.0;

			y_begin = game->res.y - (game->res.y / 2 - ((64 * game->res.y) / game->sprites[sprite_curr].dist)) - side - side / 2;
			x_begin = (
				(double)(game->res.x/2.0) + 
				tan(
					atan2(
						game->sprites[sprite_curr].pos.y - game->player.pos.y,
						game->sprites[sprite_curr].pos.x - game->player.pos.x
					)
					- game->player.angle
				) * 
				(double)(game->res.x / 2.0) / tan(FOV / 2.0 * DEG) - side/2.0
			);

			x_curr = x_begin;
			while (x_curr < x_begin + (int)side)
			{
				if (x_curr >= 0 && x_curr < game->res.x &&
					game->sprites[sprite_curr].dist < game->dists[x_curr])
				{
					y_curr = y_begin;
					while (y_curr < y_begin + side)
					{
						color = *((unsigned int*)(game->sprite_data.data_addr) + ((int)((y_curr - y_begin) / col_width) * game->sprite_data.res.x) + (int)((x_curr - x_begin) / col_width));
						if (color && y_curr >= 0 && y_curr < game->res.y)
						{
							col = (t_color){(color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF};
							put_pixel(game, x_curr, y_curr, col);
						}
						y_curr++;
					}
				}
				x_curr++;
			}
		}
		sprite_curr++;
	}
}
