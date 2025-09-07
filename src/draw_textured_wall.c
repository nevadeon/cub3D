#include "cub3D.h"

void	draw_textured_wall(t_game *game, t_ray *ray, t_draw draw)
{
	t_textures		*tex;
	double			wall_x;

	if (!game || !game->mlx || (HEIGHT / ray->perp_wall_dist) <= 0)
		return ;
	tex = pick_wall_texture(game, ray);
	if (!tex || !tex->addr || tex->w <= 0 || tex->h <= 0)
		return ;
	wall_x = impact_wall_x(ray, game, ray->side);
	wall_x -= floor(wall_x);
	draw.tex_x = x_in_texture(ray, wall_x, tex);
	draw.step = calc_tex_step(ray, tex);
	draw.tex_pos = calc_tex_pos(draw.start, ray, draw.step);
	draw_wall_stripe(game, tex, draw);
}

double	impact_wall_x(t_ray *ray, t_game *game, int ray_side)
{
	double	wall_x;

	wall_x = 0.0;
	if (ray_side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	return (wall_x);
}

int	x_in_texture(t_ray *ray, double wall_x, t_textures *tex)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->w);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = tex->w - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = tex->w - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->w)
		tex_x = tex->w -1;
	return (tex_x);
}

void	draw_wall_stripe(t_game *game, t_textures *tex, t_draw draw)
{
	int				y;
	int				tex_y;
	unsigned int	color;

	y = draw.start;
	while (y < draw.end)
	{
		tex_y = (int)draw.tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= tex->h)
			tex_y = tex->h - 1;
		color = get_tex_safe(tex, draw.tex_x, tex_y);
		mlx_pixel_put_img(game->mlx, draw.x, y, color);
		draw.tex_pos += draw.step;
		y++;
	}
}

inline t_textures	*pick_wall_texture(t_game *g, t_ray *r)
{
	if (r->side == 0 && r->dir_x > 0)
		return (&g->tex[TEXTURE_WEST]);
	if (r->side == 0 && r->dir_x < 0)
		return (&g->tex[TEXTURE_EAST]);
	if (r->side == 1 && r->dir_y > 0)
		return (&g->tex[TEXTURE_NORTH]);
	return (&g->tex[TEXTURE_SOUTH]);
}
