/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:00 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:33:01 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	count_sprites(t_game *game)
{
	int nb_sprite;
	int	x;
	int	y;
	int	max_x;
	int max_y;

	find_max(game, &max_x, &max_y);
	nb_sprite = 0;
	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			if (x < (int)ft_strlen(game->map[y]) && game->map[y][x] == '2')
				nb_sprite++;
			x++;
		}
		y++;
	}
	game->nb_sprite = nb_sprite;
}

static void		sort_sprites(t_game *game)
{
	int			i;
	t_sprite	tmp;

	i = 0;
	while (i < game->nb_sprite - 1)
	{
		if (game->sprites[i].dist < game->sprites[i + 1].dist &&
				(i + 1) < (game->nb_sprite))
		{
			tmp = game->sprites[i];
			game->sprites[i] = game->sprites[i + 1];
			game->sprites[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

void			find_sprites(t_game *game)
{
	int	x;
	int	y;
	int	nb_sprite;

	count_sprites(game);
	nb_sprite = game->nb_sprite;
	if (!(game->sprites = malloc(sizeof(*game->sprites) * nb_sprite)))
	{
		set_error(game, ERR_MALLOC);
		ft_error(game);
	}
	y = -1;
	while (++y < game->dda.max.y)
	{
		x = -1;
		while (++x < game->dda.max.x)
		{
			if (x < (int)ft_strlen(game->map[y]) && game->map[y][x] == '2')
			{
				game->sprites[nb_sprite - 1] = (t_sprite){
						(t_pos){x * 64 + 32, y * 64 + 32}, 0.0, 0};
				nb_sprite--;
			}
		}
	}
}

void			calc_dist_sprite(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_sprite)
	{
		game->sprites[i].dist = sqrt(
				pow((game->player.pos.x - game->sprites[i].pos.x), 2) +
				pow((game->player.pos.y - game->sprites[i].pos.y), 2));
		i++;
	}
	sort_sprites(game);
}

void			fill_visibility(t_game *game)
{
	int		i;
	double	angle_player_sprite;
	double	delta_angle;

	i = 0;
	while (i < game->nb_sprite)
	{
		angle_player_sprite = atan2(
				game->sprites[i].pos.y - game->player.pos.y,
				game->sprites[i].pos.x - game->player.pos.x);
		delta_angle = game->player.angle - angle_player_sprite;
		if (delta_angle > 2 * M_PI)
			delta_angle -= 2 * M_PI;
		else if (delta_angle < 0)
			delta_angle += 2 * M_PI;
		if (delta_angle < FOV / 2 * DEG ||
				delta_angle > 2 * M_PI - FOV / 2 * DEG)
			game->sprites[i].visible = 1;
		else
			game->sprites[i].visible = 0;
		i++;
	}
}
