/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:32:45 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:32:45 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_game *game)
{
	if (game->dda.ray.a < 0)
		game->dda.ray.a += 2 * M_PI;
	if (game->dda.ray.a > 2 * M_PI)
		game->dda.ray.a -= 2 * M_PI;
	dda_horizontal(game, &game->dda);
	dda_vertical(game, &game->dda);
	find_intersection(game);
	game->dists[game->dda.nb_ray] = game->dda.dist_t;
	game->dda.cos_angle = game->player.angle - game->dda.ray.a;
	if (game->dda.cos_angle < 0)
		game->dda.cos_angle += 2 * M_PI;
	if (game->dda.cos_angle > 2 * M_PI)
		game->dda.cos_angle -= 2 * M_PI;
	game->dda.dist_t = game->dda.dist_t * cos(game->dda.cos_angle);
	game->dda.line.y = (64 * game->res.y) / game->dda.dist_t;
	game->dda.line.x = game->res.y / 2 - game->dda.line.y / 2;
	if (game->dda.line.x < 0)
		game->dda.line.x = 0;
}

void	raycaster(t_game *game)
{
	game->dda.ray.a = game->player.angle - FOV / 2 * DEG;
	game->dda.nb_ray = 0;
	while (game->dda.nb_ray < game->res.x)
	{
		raycast(game);
		draw_columns(game);
		game->dda.ray.a += FOV * DEG / game->res.x;
		if (game->dda.ray.a > 2 * M_PI)
			game->dda.ray.a -= 2 * M_PI;
		game->dda.nb_ray++;
	}
}
