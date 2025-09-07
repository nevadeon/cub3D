/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:46:58 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "cub3D.h"

static void	init_game(t_game *game)
{
	*game = (t_game){
		.map.floor_rgb = -1,
		.map.ceil_rgb = -1,
		.player.plane_x = 0.90,
		.player.plane_y = 0,
	};
}

int	error_cleanup(t_alloc **allocator)
{
	err_flush();
	free_allocator(allocator);
	return (EXIT_FAILURE);
}

int	main(int argc, char const *argv[])
{
	t_alloc	*allocator;
	t_game	game;
	t_mlx	mlx;

	(void)argc;
	(void)argv;
	allocator = new_mgc_allocator(0);
	if (!allocator)
		return (EXIT_FAILURE);
	if (!parse_args(argc, argv))
		return (error_cleanup(&allocator));
	init_game(&game);
	if (!parse_cub_file(allocator, &game, argv[1]))
		return (error_cleanup(&allocator));
	if (!init_mlx(&game, &mlx))
		return (error_cleanup(&allocator));
	if (!load_all_textures(&game))
		return (destroy(game.mlx), error_cleanup(&allocator));
	run_mlx(&mlx, &game);
	free_textures(&game);
	destroy(game.mlx);
	free_allocator(&allocator);
	return (EXIT_SUCCESS);
}
