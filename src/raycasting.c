/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:47:04 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	render(t_game *game)
{
	clear_image(game->mlx, 0x003366);
	handle_move(game);
	cast_all_rays(game);
	mlx_put_image_to_window(game->mlx->mlx_init, game->mlx->mlx_win,
		game->mlx->img_ptr, 0, 0);
	return (0);
}

void	clear_image(t_mlx *mlx, int color)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			dst = mlx->addr + (y * mlx->line_len + x * (mlx->img_bpp / 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}
