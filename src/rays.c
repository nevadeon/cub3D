#include "cub3D.h"

void	cast_all_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(game, x);
		x++;
	}
}

void	cast_ray(t_game *game, int x)
{
	t_ray	ray;

	init_ray(game, x);
	ray = game->ray;
	init_step(&ray, game);
	dda_algorithm(game, &ray);
	calculate_perp_wall_dist(&ray, game);
	draw_wall(&ray, game, x);
	game->ray = ray;
}

void	init_ray(t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	game->ray.dirX = game->player.dirX + game->player.planeX * camera_x;
	game->ray.dirY = game->player.dirY + game->player.planeY * camera_x;
	game->ray.mapX = (int)game->player.posX;
	game->ray.mapY = (int)game->player.posY;
	game->ray.deltaDistX = fabs(1 / game->ray.dirX);
	game->ray.deltaDistY = fabs(1 / game->ray.dirY);
}
