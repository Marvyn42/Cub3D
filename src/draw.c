/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:31:39 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 21:36:48 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_tex_id(t_game *game)
{
	if (game->dda.ray.a >= 0 &&
			game->dda.ray.a < M_PI &&
			game->dda.dist_v > game->dda.dist_h)
		return (1);
	else if (game->dda.ray.a >= M_PI_2 &&
			game->dda.ray.a < 3 * M_PI_2 &&
			game->dda.dist_v < game->dda.dist_h)
		return (2);
	else if (game->dda.dist_v < game->dda.dist_h)
		return (3);
	else
		return (0);
}

static	int	find_tex_x(t_game *game, int tex_id)
{
	int	tex_x;

	if (game->dda.dist_v < game->dda.dist_h)
		tex_x = fmod(game->dda.ray.y / 64, 1) *
			(&game->north_data + tex_id)->res.x;
	else
		tex_x = fmod(game->dda.ray.x / 64, 1) *
			(&game->north_data + tex_id)->res.x;
	if (tex_id == 1 || tex_id == 2)
		tex_x = 64 - tex_x;
	return (tex_x);
}

static void	draw_floor_and_ceil(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->dda.line.x)
	{
		put_pixel(game, game->dda.nb_ray, y, game->ceiling);
		put_pixel(game, game->dda.nb_ray, y + game->dda.line.x +
			game->dda.line.y, game->floor);
		y++;
	}
}

void		draw_columns(t_game *game)
{
	int				y;
	int				tex_id;
	int				tex_x;
	int				tex_y;
	unsigned int	color;

	tex_id = find_tex_id(game);
	tex_x = find_tex_x(game, tex_id);
	draw_floor_and_ceil(game);
	y = (int)game->dda.line.x + 1;
	while (y < game->res.y - game->dda.line.x)
	{
		tex_y = (y + game->dda.line.y / 2 - game->res.y / 2) *
			((&game->north_data + tex_id)->res.y / game->dda.line.y);
		color = *((unsigned int*)((&game->north_data + tex_id)->data_addr) +
			(tex_y * (&game->north_data + tex_id)->res.x + tex_x));
		game->dda.col = (t_color){(color & 0xFF0000) >> 16,
			(color & 0x00FF00) >> 8, color & 0x0000FF};
		put_pixel(game, game->dda.nb_ray, y, game->dda.col);
		y++;
	}
}
