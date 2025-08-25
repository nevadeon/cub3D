#include "cub3D.h"

int	key_press(int key, t_game *game)
{
	if (key == XK_Escape)
	{
		destroy(game->mlx);
		//cleanup(game);
		exit(EXIT_SUCCESS);
	}
	if (key == XK_w)
		game->keys.w = 1;
	if (key == XK_s)
		game->keys.s = 1;
	if (key == XK_a)
		game->keys.a = 1;
	if (key == XK_d)
		game->keys.d = 1;
	if (key == XK_Left)
		game->keys.left = 1;
	if (key == XK_Right)
		game->keys.right = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == XK_w)
		game->keys.w = 0;
	if (key == XK_s)
		game->keys.s = 0;
	if (key == XK_a)
		game->keys.a = 0;
	if (key == XK_d)
		game->keys.d = 0;
	if (key == XK_Left)
		game->keys.left = 0;
	if (key == XK_Right)
		game->keys.right = 0;
	return (0);
}

int	cross_escape(t_mlx *mlx)
{
	mlx_loop_end(mlx->mlx_init);
	return (0);
}

bool init_mlx(t_game *game, t_mlx *mlx)
{
	game->mlx = mlx;
	mlx->mlx_init = mlx_init();
	if (!mlx->mlx_init)
		return (error_push_code(ERR_MLX));
	mlx->mlx_win = mlx_new_window(mlx->mlx_init, WIDTH, HEIGHT, WINDOW_NAME);
	if(!mlx->mlx_win)
		return (mlx_destroy_display(mlx), error_push_code(ERR_MLX));
	mlx->img_ptr = mlx_new_image(mlx->mlx_init, WIDTH, HEIGHT);
	if (!mlx->img_ptr)
		return (mlx_destroy_display(mlx), error_push_code(ERR_MLX));
	mlx->addr = mlx_get_data_addr(mlx->img_ptr,
			&mlx->img_bpp, &mlx->line_len, &mlx->endian);
	if (!mlx->addr)
		return (mlx_destroy_display(mlx), error_push_code(ERR_MLX));
	return (RETURN_SUCCESS);
}

void	run_mlx(t_mlx *mlx, t_game *game)
{
	mlx_hook(mlx->mlx_win, DestroyNotify, StructureNotifyMask, cross_escape, mlx);
	mlx_hook(mlx->mlx_win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(mlx->mlx_win, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_loop_hook(mlx->mlx_init, render, game);
	mlx_loop(mlx->mlx_init);
}

void	destroy(t_mlx *mlx)
{
	if (mlx->img_ptr)
		mlx_destroy_image(mlx->mlx_init, mlx->img_ptr);
	if (mlx->mlx_win)
		mlx_destroy_window(mlx->mlx_init, mlx->mlx_win);
	if (mlx->mlx_init)
	{
		mlx_destroy_display(mlx->mlx_init);
		free(mlx->mlx_init);
	}
}
