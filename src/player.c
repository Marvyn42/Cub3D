/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:32:32 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 19:43:49 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game)
{
	if (game->map[game->player.pos.y][game->player.pos.x] == 'N')
		game->player.angle = -M_PI_2;
	else if (game->map[game->player.pos.y][game->player.pos.x] == 'S')
		game->player.angle = M_PI_2;
	else if (game->map[game->player.pos.y][game->player.pos.x] == 'W')
		game->player.angle = M_PI;
	else if (game->map[game->player.pos.y][game->player.pos.x] == 'E')
		game->player.angle = 0;
	game->player.pos = (t_pos){game->player.pos.x * 64 + 32,
			game->player.pos.y * 64 + 32};
	game->player.delta = (t_pos){cos(game->player.angle) * game->speed,
			sin(game->player.angle) * game->speed};
}

void	move_player(t_game *game)
{
	raycaster(game);
	calc_dist_sprite(game);
	fill_visibility(game);
	draw_sprite(game);
	mlx_put_image_to_window(game->mlx.id, game->mlx.win, game->mlx.img.id,
			0, 0);
}
