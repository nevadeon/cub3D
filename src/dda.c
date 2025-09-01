#include "cub3D.h"

void	init_step(t_ray *ray, t_game *game)
{
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->player.posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - game->player.posX)
			* ray->deltaDistX;
	}
	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->player.posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->player.posY)
			* ray->deltaDistY;
	}
}

void	dda_algorithm(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		// sécurité : éviter un segfault si on sort de la map
		if (ray->mapX < 0 || ray->mapY < 0
			|| ray->mapY >= game->map.height || ray->mapX >= game->map.width)
			break ;
		if (game->map.grid[ray->mapY][ray->mapX] == '1')
			hit = 1;
	}
}

void	calculate_perp_wall_dist(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perpWallDist = ((ray->mapX - game->player.posX
					+ (1 - ray->stepX) / 2) / ray->dirX);
	else
		ray->perpWallDist = ((ray->mapY - game->player.posY
					+ (1 - ray->stepY) / 2) / ray->dirY);
}
