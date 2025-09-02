#include "cub3D.h"

void	draw_wall(t_ray *ray, t_game *game, int x)
{
	float	line_h;
	int		start;
	int		end;
//	int		color;

	line_h = (int)(HEIGHT / ray->perpWallDist);
	start = -line_h / 2 + HEIGHT / 2;
	end = line_h / 2 + HEIGHT / 2;

	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT -1 ;
//	color = ray->side;

	/* plafond */
	draw_vertical_line (game->mlx, x, 0, start, 0x87CEEB);
	/* mur */
	//draw_textured_wall(game, ray, x, start, end);
	/* sol */
	draw_vertical_line(game->mlx, x, end, HEIGHT - 1, 0xD2B48C);
}

void draw_textured_wall(t_game *game, t_ray *ray, int x, int start, int end)
{
	t_textures *tex = NULL;
	int y;
	int tex_index;

	tex_index = get_texture_index(ray);
	tex = &game->tex[tex_index];
	if (!game->tex[tex_index].pixel)
	{
		printf("rho");
		exit(0);
	}
	if (!tex->pixel)
	{
		printf("hey");
		return;
	}
	setup_texture_mapping(game, ray, start, end);

	y = start;
	while (y < end)
	{
		tex->tex_y = (int)tex->tex_pos;
		if (tex->tex_y < 0)
			tex->tex_y = 0;
		if (tex->tex_y >= tex->h)
			tex->tex_y = tex->h - 1;

		tex->tex_pos += tex->step;
		tex->color = tex->pixel[tex->w * tex->tex_y + tex->tex_x];
		put_pixel(game->mlx, x, y, tex->color);
		y++;
	}
}


void	setup_texture_mapping(t_game  *game, t_ray *ray, int start, int end)
{
	int			tex_index;
	t_textures	*tex;
	float		wall_x;

	wall_x = 0.0;
	tex_index = get_texture_index(ray);
	tex = &game->tex[tex_index];

	if (ray->side == 0 && ray->dirX > 0)
		wall_x = game->player.posY + ray->perpWallDist * ray->dirY;
	else
		wall_x = game->player.posX + ray->perpWallDist * ray->dirX;
	wall_x -= floorf(wall_x);

	tex->tex_x = (int)(wall_x * tex->w);
	if ((ray->side == 0 && ray->dirX > 0) || (ray->side == 1 && ray->dirY < 0))
		tex->tex_x = tex->w - tex->tex_x - 1;

	tex->step = 1.0 * tex->h /(end - start);
	tex->tex_pos = (start - HEIGHT / 2 + (end - start) / 2) * tex->step;
}

void	draw_vertical_line(t_mlx *mlx, int x, int start, int end, int color)
{
	int		y;
	char	*px;

	px = NULL;
	y = start;
	while (y <= end)
	{
		px = mlx->addr + (y * mlx->line_len + x * (mlx->img_bpp / 8));
		*(unsigned int *)px = color;
		y++;
	}
}
