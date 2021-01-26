/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:12 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:33:13 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_tex_type(char *words)
{
	char *texture_type;
	char *texture;

	texture_type = ".xpm";
	texture = *(&words) + (ft_strlen(words) - 4);
	if (ft_strncmp(texture, texture_type, 4))
		return (1);
	return (0);
}

double	dist(t_game *game, t_dpos inter)
{
	return (cos((game->dda.ray.a)) * (inter.x - game->player.pos.x) +
			sin((game->dda.ray.a)) * (inter.y - game->player.pos.y));
}

int		ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	init_dda(t_game *game)
{
	t_pos	max;

	find_max(game, &max.x, &max.y);
	game->dda.nb_ray = 0;
	game->dda.limit = 0;
	game->dda.dist_h = 0.0;
	game->dda.dist_v = 0.0;
	game->dda.map_pos = (t_pos){0, 0};
	game->dda.max = max;
	game->dda.ray = (t_ray){0.0, 0.0, 0.0};
	game->dda.offset = (t_dpos){0.0, 0.0};
	game->dda.inter_h = (t_dpos){0.0, 0.0};
	game->dda.inter_v = (t_dpos){0.0, 0.0};
	game->dda.col = (t_color){0, 0, 0};
	game->dda.line = (t_dpos){0.0, 0.0};
	game->dda.cos_angle = 0.0;
	game->dda.dist_t = 0.0;
}

int		check_cub(t_game *game, const char *file)
{
	int	safe;
	int	fd;

	safe = 1;
	if (ft_strncmp(file + ((int)ft_strlen(file) - 4), ".cub", 5))
		safe = set_error(game, ERR_ARG);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		safe = set_error(game, ERR_ARG);
	else if (close(fd) < 0)
		safe = set_error(game, ERR_ARG);
	if (!safe)
		ft_error(game);
	return (1);
}
