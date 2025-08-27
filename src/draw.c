#include "cub3D.h"

void draw_wall(t_ray *ray, t_game *game, int x)
{
	float line_h;
	int start;
	int end;
	int color;

	line_h = (int)(HEIGHT / ray->perpWallDist);
	start = -line_h / 2 + HEIGHT / 2;
	end = line_h / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT -1 ;

	color = ray->side;
	if (ray->side == 1)
		color = 0x0000ff;
	else
		color = 0x000000;
	draw_vertical_line(game->mlx, x, start, end, color);
}

void draw_vertical_line(t_mlx *mlx, int x, int start, int end, int color)
{
	int y;
	char *px;

	px = NULL;
	y = start;
	while (y <= end)
	{
		px = mlx->addr + (y  * mlx->line_len + x * (mlx->img_bpp / 8));
		*(unsigned int *)px = color;
		y++;
	}
}
