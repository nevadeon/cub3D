#include "cub3D.h"

char *worldMap[30] = {
    "11111111111111111111",
    "10000000000000000001",
    "10000000000000111001",
    "10000000000000000001",
    "10001000111110000001",
    "10000000000000000001",
    "10000010000000000001",
    "10000010000000000001",
    "10000010000000000001",
    "10000010000000000001",
    "10000010011000000001",
    "10000000001000000001",
    "10001110011000000001",
    "10000000000000100101",
    "10000000011000100101",
    "10000000000000100101",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
	"10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
	"10000000000000000001",
    "10000000000000000001",
    "11111111111111111111"
};

int	render(t_game *game)
{
	game->map = worldMap;
	game->map_h = 30;
	game->map_w = 30;
	clear_image(game->mlx, 0x003366);
	handle_move(game);
	cast_all_rays(game);
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

void	draw_pixel(t_mlx *mlx, int x, int y_start, int y_end, int color)
{
	int y = y_start;
	while (y <= y_end)
	{
		char *px = mlx->addr + (y * mlx->line_len + x * (mlx->img_bpp / 8));
		*(unsigned int *)px = color;
	}
}
