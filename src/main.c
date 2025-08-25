#include "error.h"
#include "cub3D.h"

static void	init_game(t_game *c)
{
	*c = (t_game)
	{
		.tex_no = NULL,
		.tex_so = NULL,
		.tex_we = NULL,
		.tex_ea = NULL,
		.floor_rgb = -1,
		.ceil_rgb = -1,
		.map = NULL,
		.map_w = 0,
		.map_h = 0,
		.player_x = -1,
		.player_y = -1,
		.player_dir = '\0',
	};
}

int	main(int argc, char const *argv[])
{
	t_alloc	*allocator;
	t_game	game;
	t_mlx	mlx;

	allocator = new_mgc_allocator(0);
	if (!allocator)
		return (1);
	if (!parse_args(argc, argv))
		return (error_print(), free_allocator(&allocator), 1);
	init_game(&game);
	if (!parse_cub_file(allocator, &game, argv[1]))
		return (error_print(), free_allocator(&allocator), 1);

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
	// run_mlx(&mlx, &game);
	destroy(&mlx);

	free_allocator(&allocator);
	return (0);
}
