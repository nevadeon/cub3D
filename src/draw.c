#include "cub3D.h"

void	draw_wall(t_ray *ray, t_game *game, int x)
{
	t_draw	draw;
	float	line_h;
	int		start;
	int		end;

	line_h = (int)(HEIGHT / ray->perp_wall_dist);
	start = -line_h / 2 + HEIGHT / 2;
	end = line_h / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT -1 ;
	draw.x = x;
	draw.start = start;
	draw.end = end;
	draw_ceil(game->mlx, draw, game->map.ceil_rgb);
	draw_textured_wall(game, ray, draw);
	draw_floor(game->mlx, draw, game->map.floor_rgb);
}

void	draw_ceil(t_mlx *mlx, t_draw draw, int color)
{
	int		y;
	char	*px;

	px = NULL;
	y = 0;
	while (y <= draw.start)
	{
		px = mlx->addr + (y * mlx->line_len + draw.x * (mlx->img_bpp / 8));
		*(unsigned int *)px = color;
		y++;
	}
}

void	draw_floor(t_mlx *mlx, t_draw draw, int color)
{
	int		y;
	char	*px;

	px = NULL;
	y = draw.end;
	while (y <= HEIGHT - 1)
	{
		px = mlx->addr + (y * mlx->line_len + draw.x * (mlx->img_bpp / 8));
		*(unsigned int *)px = color;
		y++;
	}
}
