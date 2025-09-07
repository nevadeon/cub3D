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
	game->ray.dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	game->ray.dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
	game->ray.delta_dist_x = fabs(1 / game->ray.dir_x);
	game->ray.delta_dist_y = fabs(1 / game->ray.dir_y);
}
