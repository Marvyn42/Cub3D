/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:32:14 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:32:15 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_mlx(t_game *game)
{
	if (game->mlx.id)
	{
		mlx_loop_end(game->mlx.id);
		if (game->mlx.img.id)
			mlx_destroy_image(game->mlx.id, game->mlx.img.id);
		if (game->north_data.id)
			mlx_destroy_image(game->mlx.id, game->north_data.id);
		if (game->south_data.id)
			mlx_destroy_image(game->mlx.id, game->south_data.id);
		if (game->west_data.id)
			mlx_destroy_image(game->mlx.id, game->west_data.id);
		if (game->east_data.id)
			mlx_destroy_image(game->mlx.id, game->east_data.id);
		if (game->sprite_data.id)
			mlx_destroy_image(game->mlx.id, game->sprite_data.id);
		if (game->mlx.win)
			mlx_destroy_window(game->mlx.id, game->mlx.win);
		mlx_destroy_display(game->mlx.id);
		ft_free(game->mlx.id);
	}
}

void		free_split(char **words)
{
	int index;

	index = 0;
	while (words[index])
	{
		ft_free(words[index]);
		index++;
	}
	ft_free(words);
}

void		free_game(t_game *game)
{
	free_mlx(game);
	if (game->map)
		free_split(game->map);
	if (game->north)
		ft_free(game->north);
	if (game->south)
		ft_free(game->south);
	if (game->west)
		ft_free(game->west);
	if (game->east)
		ft_free(game->east);
	if (game->sprite)
		ft_free(game->sprite);
	if (game->dists)
		ft_free(game->dists);
	if (game->sprites)
		ft_free(game->sprites);
}
