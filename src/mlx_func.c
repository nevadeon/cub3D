/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:47:00 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline void	mlx_pixel_put_img(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	dst = NULL;
	if (!mlx || !mlx->addr)
		return ;
	if ((unsigned)x >= WIDTH || (unsigned)y >= HEIGHT)
		return ;
	dst = (char *)mlx->addr + (y * mlx->line_len + x * (mlx->img_bpp / 8));
	*(unsigned int *)dst = color;
}

int	key_press(int key, t_game *game)
{
	if (key == XK_Escape)
	{
		mlx_loop_end(game->mlx->mlx_init);
		return (0);
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
