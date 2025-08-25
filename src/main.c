#include "error.h"
#include "cub3D.h"

// static void init_keys(t_keys *keys)
// {
// 	*keys = (t_keys){
// 		.w = 0,
// 		.s = 0,
// 		.a = 0,
// 		.d = 0,
// 		.left = 0,
// 		.right = 0,
// 	};
// }

static void	init_game(t_game *game)
{
	*game = (t_game){
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

		.player.posX = 12,
		.player.posY = 10,
		.player.dirX = -1, // regarde vers la gauche
		.player.dirY = 0,
		.player.planeX = 0,
		.player.planeY = 0.90, // FOV ~ 66°

		.keys.w = 0,
		.keys.s = 0,
		.keys.a = 0,
		.keys.d = 0,
		.keys.left = 0,
		.keys.right = 0,
	};
}

int	error_cleanup(t_alloc **allocator)
{
	error_flush();
	free_allocator(allocator);
	return (EXIT_FAILURE);
}

int	cleanup(t_alloc **allocator, t_game *game)
{
	destroy(game->mlx);
	free_allocator(allocator);
	return (EXIT_SUCCESS);
}

int	main(int argc, char const *argv[])
{
	t_alloc	*allocator;
	t_game	game;
	t_mlx	mlx;

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

	// init_data() need
	//{
	//      raycasting
	//      run_mlx
	//      destroy_mlx
	//}
	//cleanup(&game)

	// lancer la boucle
	// run_mlx(&mlx, &game);

	return (cleanup(&allocator, &game));
}
