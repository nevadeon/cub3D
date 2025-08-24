#include "cub3D.h"

int         render(t_game *game)
{
    // int x = 0;
    clear_image(game->mlx, 0x003366);
    // while (x < WIDTH)
    // {
    //     cast_ray(game, x);
    //     x++;
    // }
    mlx_put_image_to_window(game->mlx->mlx_init, game->mlx->mlx_win, game->mlx->img_ptr, 0,0);
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
			*(unsigned int*)dst = color;
			x++;
		}
		y++;
	}
}

// void	draw_pixel(t_mlx *mlx, int x, int y_start, int y_end, int color)
// {
// 	int y = y_start;
// 	while (y <= y_end)
// 	{
// 		char *px = mlx->addr + (y * mlx->line_len + x * (mlx->img_bpp / 8));
// 		*(unsigned int *)px = color;
// 	}
// }
