#include "cub3D.h"
#include "error.h"
#include "cub3D.h"

int	main(int argc, char const *argv[])
{
	t_alloc	*allocator;
	t_game	game;
	t_mlx	mlx;

	allocator = new_mgc_allocator(0);
	if (!allocator)
		return (1);
	// if (!parse_args(argc, argv))
	// 	return (error_print(), free_allocator(&allocator), 1);
	// if (!parse_cub_file(allocator, argv[1], &game))
	// 	return (error_print(), free_allocator(&allocator), 1);

	// init_data() need
	//{
	//      raycasting
	//      run_mlx
	//      destroy_mlx
	//}
	//cleanup(&game)

	// --- For TESTING --- //
	if (init_mlx(&game, &mlx) == EXIT_FAILURE)
	{
		fprintf(stderr, "Error: MLX init failed\n");
		return (EXIT_FAILURE);
	}

	// init joueur (en attendant parsing)
	game.player.posX = 12;
	game.player.posY = 10;
	game.player.dirX = -1; // regarde vers la gauche
	game.player.dirY = 0;
	game.player.planeX = 0;
	game.player.planeY = 0.90; // FOV ~ 66°

	// init touches
	game.keys.w = 0;
	game.keys.s = 0;
	game.keys.a = 0;
	game.keys.d = 0;
	game.keys.left = 0;
	game.keys.right = 0;

	// lancer la boucle
	run_mlx(&mlx, &game);
	destroy(&mlx);

	free_allocator(&allocator);
	return (0);
}
