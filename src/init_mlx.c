/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:46:56 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	init_mlx(t_game *game, t_mlx *mlx)
{
	game->mlx = mlx;
	mlx->mlx_init = mlx_init();
	if (!mlx->mlx_init)
		return (err_code(ERR_MLX));
	mlx->mlx_win = mlx_new_window(mlx->mlx_init, WIDTH, HEIGHT, WINDOW_NAME);
	if (!mlx->mlx_win)
		return (mlx_destroy_display(mlx->mlx_init), free(mlx->mlx_init), \
			err_code(ERR_MLX));
	mlx->img_ptr = mlx_new_image(mlx->mlx_init, WIDTH, HEIGHT);
	if (!mlx->img_ptr)
		return (mlx_destroy_window(mlx->mlx_init, mlx->mlx_win), \
			mlx_destroy_display(mlx->mlx_init), free(mlx->mlx_init), \
			err_code(ERR_MLX));
	mlx->addr = mlx_get_data_addr(mlx->img_ptr,
			&mlx->img_bpp, &mlx->line_len, &mlx->endian);
	if (!mlx->addr)
		return (mlx_destroy_image(mlx->mlx_init, mlx->img_ptr), \
			mlx_destroy_window(mlx->mlx_init, mlx->mlx_win), \
			mlx_destroy_display(mlx->mlx_init), free(mlx->mlx_init), \
			err_code(ERR_MLX));
	return (RETURN_SUCCESS);
}

void	run_mlx(t_mlx *mlx, t_game *game)
{
	mlx_hook(mlx->mlx_win, DestroyNotify, StructureNotifyMask,
		cross_escape, mlx);
	mlx_hook(game->mlx->mlx_win, 2, 1L << 0, key_press, game);
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
