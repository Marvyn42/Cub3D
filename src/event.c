/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:32:03 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:32:04 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int keycode, t_game *game)
{
	if (keycode == Z_KEY)
		game->player.key.z = 1;
	else if (keycode == S_KEY)
		game->player.key.s = 1;
	else if (keycode == Q_KEY)
		game->player.key.q = 1;
	else if (keycode == D_KEY)
		game->player.key.d = 1;
	else if (keycode == ARROW_LEFT_KEY)
		game->player.key.arrow_left = 1;
	else if (keycode == ARROW_RIGHT_KEY)
		game->player.key.arrow_right = 1;
	else if (keycode == ESC_KEY)
		close_win(game);
	return (1);
}

int		key_release(int keycode, t_game *game)
{
	if (keycode == Z_KEY)
		game->player.key.z = 0;
	else if (keycode == S_KEY)
		game->player.key.s = 0;
	else if (keycode == Q_KEY)
		game->player.key.q = 0;
	else if (keycode == D_KEY)
		game->player.key.d = 0;
	else if (keycode == ARROW_LEFT_KEY)
		game->player.key.arrow_left = 0;
	else if (keycode == ARROW_RIGHT_KEY)
		game->player.key.arrow_right = 0;
	return (1);
}

int		loop_hook(t_game *game)
{
	int		i;
	int		(*const move[6])(t_game *) = {forward, left, backward, right,
			rotate_left, rotate_right};
	void	*ptr;

	i = 0;
	ptr = &(game->player.key);
	while (i < 6)
	{
		if (*(int *)ptr)
			move[i](game);
		ptr += sizeof(int);
		i++;
	}
	if (game->player.key.z ||
		game->player.key.s ||
		game->player.key.q ||
		game->player.key.d ||
		game->player.key.arrow_left ||
		game->player.key.arrow_right)
		move_player(game);
	return (1);
}

void	global_event(t_game *game)
{
	mlx_hook(game->mlx.win, CLIENT_MESSAGE, STRUCTURE_NOTIFY_MASK,
			close_win, game);
	mlx_hook(game->mlx.win, VISIBILITY_NOTIFY, VISIBILITY_CHANGE_MASK,
			minimise_hook, game);
	mlx_hook(game->mlx.win, KEY_PRESS, (1L << 0), key_press, game);
	mlx_hook(game->mlx.win, KEY_RELEASE, (1L << 1), key_release, game);
	mlx_loop_hook(game->mlx.id, loop_hook, game);
}

int		minimise_hook(t_game *game)
{
	mlx_put_image_to_window(game->mlx.id, game->mlx.win,
			game->mlx.img.id, 0, 0);
	return (0);
}
