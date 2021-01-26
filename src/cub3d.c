/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:31:32 by mamaquig          #+#    #+#             */
/*   Updated: 2021/01/26 18:31:33 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char *argv[])
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc == 2 && check_cub(&game, argv[1]))
	{
		game.mlx.id = mlx_init();
		global_parse(argv[1], &game);
		global_img(&game);
		global_win(&game);
		global_event(&game);
		mlx_loop(game.mlx.id);
	}
	else if (argc == 3 && check_cub(&game, argv[1]) &&
		(!ft_strncmp(argv[2], "--save", 7) || !ft_strncmp(argv[2], "-s", 3)))
	{
		game.mlx.id = mlx_init();
		global_parse(argv[1], &game);
		global_img(&game);
		ft_create_bmp(&game);
		free_game(&game);
		exit(EXIT_SUCCESS);
	}
	set_error(&game, ERR_ARG);
	ft_error(&game);
	return (0);
}
