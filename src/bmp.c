/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:31:22 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/28 16:01:18 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Write file header
*/

static int	ft_bmp_file_header(t_game *game, int fd)
{
	unsigned char	*file_header;
	int				file_size;

	if (!(file_header = ft_calloc(BMP_FILE_HEADER_SIZE, sizeof(unsigned char))))
	{
		set_error(game, ERR_MALLOC);
		ft_error(game);
	}
	file_size = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE +
		(game->mlx.img.bpp / 8 * game->res.x) * game->res.y;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(BMP_FILE_HEADER_SIZE +
		BMP_INFO_HEADER_SIZE);
	write(fd, file_header, BMP_FILE_HEADER_SIZE);
	ft_free(file_header);
	return (1);
}

/*
** Write info header
*/

static int	ft_bmp_info_header(t_game *game, int fd)
{
	unsigned char	*info_header;

	if (!(info_header = ft_calloc(BMP_INFO_HEADER_SIZE, sizeof(unsigned char))))
	{
		set_error(game, ERR_MALLOC);
		ft_error(game);
	}
	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(game->res.x);
	info_header[5] = (unsigned char)(game->res.x >> 8);
	info_header[6] = (unsigned char)(game->res.x >> 16);
	info_header[7] = (unsigned char)(game->res.x >> 24);
	info_header[8] = (unsigned char)(game->res.y);
	info_header[9] = (unsigned char)(game->res.y >> 8);
	info_header[10] = (unsigned char)(game->res.y >> 16);
	info_header[11] = (unsigned char)(game->res.y >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(game->mlx.img.bpp);
	write(fd, info_header, BMP_INFO_HEADER_SIZE);
	ft_free(info_header);
	return (1);
}

/*
** Write image
*/

static int	ft_bmp_image(t_game *game, int fd)
{
	int	i;

	i = game->res.y;
	while (i >= 0)
	{
		write(fd, game->mlx.img.data_addr +
		(i * game->res.x * game->mlx.img.bpp / 8), game->mlx.img.size_line);
		i--;
	}
	return (1);
}

/*
** Write image from mlx->img to bmp file: TITLE_FILE
*/

int			ft_create_bmp(t_game *game)
{
	int	fd;
	int	safe;

	safe = 1;
	if ((fd = open(TITLE_BMP, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		safe = set_error(game, ERR_BMP);
	if (!ft_bmp_file_header(game, fd) || !ft_bmp_info_header(game, fd))
		safe = set_error(game, ERR_BMP_HEADER);
	if (!ft_bmp_image(game, fd))
		safe = set_error(game, ERR_BMP_IMG);
	if (close(fd) < 0)
		safe = set_error(game, ERR_BMP);
	if (!safe)
		ft_error(game);
	ft_putstr("\033[32mInfo\033[0m\nLe fichier ./");
	ft_putstr(TITLE_BMP);
	ft_putstr(" a été correctement enregistré.\n");
	return (1);
}
