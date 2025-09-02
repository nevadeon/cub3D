#include "error.h"
#include "cub3D.h"


/*
PlaneX and PlaneY
It must be perpendicular to the direction vector (dirX, dirY)
and its length determines the field of view (FOV)

he player direction vector (dirX, dirY) says where the player looks.
Example: looking along X → dirX = 1, dirY = 0.

The camera plane vector (planeX, planeY) is perpendicular to the direction.
Example: if dir = (1, 0) → plane = (0, 0.66).

The length of the plane controls the FOV:

0.66 ≈ 66° FOV (classic Wolf3D look).

Bigger values = wider FOV (like fisheye).

Smaller values = narrower FOV (zoomed-in).
*/
static void	init_game(t_game *game)
{
	*game = (t_game){
		.map.floor_rgb = -1,
		.map.ceil_rgb = -1,
		.player.planeX = 0.90,
		.player.planeY = 0,
	};
}

int	error_cleanup(t_alloc **allocator)
{
	error_flush();
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

	// init_data() need
	//{
	//      raycasting
	//      run_mlx
	//      destroy_mlx
	//}
	//cleanup(&game)

	/* Debug dump of game struct */
	printf("--- GAME DUMP ---\n");
	printf("tex_no: %s\n", game.map.tex_no ? game.map.tex_no : "(null)");
	printf("tex_so: %s\n", game.map.tex_so ? game.map.tex_so : "(null)");
	printf("tex_we: %s\n", game.map.tex_we ? game.map.tex_we : "(null)");
	printf("tex_ea: %s\n", game.map.tex_ea ? game.map.tex_ea : "(null)");
	printf("floor_rgb: %d\n", game.map.floor_rgb);
	printf("ceil_rgb: %d\n", game.map.ceil_rgb);
	printf("map.width: %d\n", game.map.width);
	printf("map.height: %d\n", game.map.height);
	printf("player.posX: %f\n", game.player.posX);
	printf("player.posY: %f\n", game.player.posY);
	printf("player.dirX: %f\n", game.player.dirX);
	printf("player.dirY: %f\n", game.player.dirY);
	printf("player.planeX: %f\n", game.player.planeX);
	printf("player.planeY: %f\n", game.player.planeY);
	printf("keys: w=%d s=%d a=%d d=%d left=%d right=%d\n",
		game.keys.w, game.keys.s, game.keys.a, game.keys.d, game.keys.left, game.keys.right);
	printf("ray.perpWallDist: %f mapX=%d mapY=%d side=%d\n",
		game.ray.perpWallDist, game.ray.mapX, game.ray.mapY, game.ray.side);
	printf("mlx ptr: %p\n", (void *)game.mlx);
	printf("map rows (first 20):\n");
	for (int y = 0; y < game.map.height; y++)
	{
		printf("%3d: %s\n", y, game.map.grid[y] ? game.map.grid[y] : "(null)");
	}
	printf("--- END DUMP ---\n");
	load_texture(&game);
	run_mlx(&mlx, &game);
	destroy(game.mlx);
	free_allocator(&allocator);
	return (EXIT_SUCCESS);
}
