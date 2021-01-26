/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:07 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:33:08 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_game *game, t_img *tex_data, char *tex_name)
{
	tex_data->bpp = -1;
	tex_data->size_line = -1;
	tex_data->endian = -1;
	tex_data->res.x = 0;
	tex_data->res.y = 0;
	tex_data->id = mlx_xpm_file_to_image(game->mlx.id, tex_name,
			&tex_data->res.x, &tex_data->res.y);
	tex_data->data_addr = mlx_get_data_addr(tex_data->id, &tex_data->bpp,
			&tex_data->size_line, &tex_data->endian);
}
