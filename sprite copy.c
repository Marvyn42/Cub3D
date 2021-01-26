/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:38:22 by agautier          #+#    #+#             */
/*   Updated: 2021/01/26 15:11:309 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"

// void	*ft_realloc(void *ptr, size_t size)
// {
// 	void *str;

// 	if (!ptr)
// 		return (ptr = malloc(size));
// 	if ((!size && ptr) || (size <= ft_strlen(ptr)))
// 	{
// 		free(ptr);
// 		return (NULL);
// 	}
// 	if (!(str = (char *)malloc(size)))
// 		return (NULL);
// 	ft_memcpy(str, ptr, ft_strlen(ptr));
// 	ft_free(ptr);
// 	return (str);
// }


// // static void	count_sprites(t_game *game)
// // {
// // 	int nb_sprite;
// // 	int	x;
// // 	int	y;

// // 	nb_sprite = 0;
// // 	y = 0;
// // 	while (y < game->dda.max.y)
// // 	{
// // 		x = 0;
// // 		while (x < game->dda.max.x)
// // 		{
// // 			if (x < (int)ft_strlen(game->map[y]) && game->map[y][x] == '2')
// // 				nb_sprite++;
// // 			x++;
// // 		}
// // 		y++;
// // 	}
// // 	game->nb_sprite = nb_sprite;
// // }

// static void	sort_sprites(t_game *game)
// {
// 	int			i;
// 	t_sprite	tmp;

// 	i = 0;
// 	while (i < game->nb_sprite - 1)
// 	{
// 		if (game->sprites[i].dist < game->sprites[i + 1].dist &&
// 				(i + 1) < (game->nb_sprite))
// 		{
// 			tmp = game->sprites[i];
// 			game->sprites[i] = game->sprites[i + 1];
// 			game->sprites[i + 1] = tmp;
// 			i = -1;
// 		}
// 		i++;
// 	}
// }

// void		find_sprites(t_game *game)
// {
// 	t_pos p;

// 	p.y = 0;
// 	while (p.y < game->dda.max.y)
// 	{
// 		p.x = 0;
// 		while (p.x < game->dda.max.x)
// 		{
// 			if (p.x < (int)ft_strlen(game->map[p.y]) && game->map[p.y][p.x] == '2')
// 			{
// 				game->sprites = ft_realloc(game->sprites,
// 						sizeof(t_sprite) * (game->nb_sprite + 1));
// 				if (!game->sprites)
// 				{
// 					set_error(game, ERR_MALLOC);
// 					ft_error(game);
// 				}
// 				printf("game->sprite = %d\n", game->nb_sprite);
// 				game->sprites[game->nb_sprite] = (t_sprite){
// 						(t_pos){p.x * 64 + 32, p.y * 64 + 32}, 0.0, 0};
// 				game->nb_sprite++;
// 			}
// 			p.x++;
// 		}
// 		p.y++;
// 	}
// }

// void		calc_dist_sprite(t_game *game)
// {
// 	int	i;

// 	i = 0;
// 	while (i < game->nb_sprite)
// 	{
// 		game->sprites[i].dist = sqrt(
// 				pow((game->player.pos.x - game->sprites[i].pos.x), 2) +
// 				pow((game->player.pos.y - game->sprites[i].pos.y), 2));
// 		i++;
// 	}
// 	sort_sprites(game);
// }

// void		fill_visibility(t_game *game)
// {
// 	int	i;
// 	double	angle_player_sprite;
// 	double	delta_angle;

// 	i = 0;
// 	while (i < game->nb_sprite)
// 	{
// 		angle_player_sprite = atan2(
// 				game->sprites[i].pos.y - game->player.pos.y,
// 				game->sprites[i].pos.x - game->player.pos.x);
// 		delta_angle = game->player.angle - angle_player_sprite;
// 		if (delta_angle > 2 * M_PI)
// 			delta_angle -= 2 * M_PI;
// 		else if (delta_angle < 0)
// 			delta_angle += 2 * M_PI;
// 		if (delta_angle < FOV / 2 * DEG ||
// 				delta_angle > 2 * M_PI - FOV / 2 * DEG)
// 			game->sprites[i].visible = 1;
// 		else
// 			game->sprites[i].visible = 0;
// 		i++;
// 	}
// }
