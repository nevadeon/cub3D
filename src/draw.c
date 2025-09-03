#include "cub3D.h"

void	draw_wall(t_ray *ray, t_game *game, int x)
{
	float	line_h;
	int		start;
	int		end;

	line_h = (int)(HEIGHT / ray->perpWallDist);
	start = -line_h / 2 + HEIGHT / 2;
	end = line_h / 2 + HEIGHT / 2;

	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT -1 ;

	/* plafond */
	draw_vertical_line (game->mlx, x, 0, start, game->map.ceil_rgb);
	/* mur */
	draw_textured_wall(game, ray, x, start, end);
	/* sol */
	draw_vertical_line(game->mlx, x, end, HEIGHT - 1, game->map.floor_rgb);
}

double	impact_wall_x(t_ray *ray, t_game *game, int ray_side)
{
	double wall_x;

	wall_x = 0.0;
	if (ray_side == 0)
		wall_x = game->player.posY + ray->perpWallDist * ray->dirY;
	else
		wall_x = game->player.posX + ray->perpWallDist * ray->dirX;
	return (wall_x);
}

int	x_in_texture(t_ray *ray, double wall_x, t_textures *tex)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->w);
	if (ray->side == 0 && ray->dirX > 0)
		tex_x = tex->w - tex_x - 1;
	if (ray->side == 1 && ray->dirY < 0)
		tex_x = tex->w - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->w)
		tex_x = tex->w -1;
	return (tex_x);
}

void	draw_textured_wall(t_game *game, t_ray *ray, int x, int start, int end)
{
	t_textures		*tex;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				y;
	unsigned int	color;

	if (!game || !game->mlx || (HEIGHT / ray->perpWallDist) <= 0)
		return;
	tex = pick_wall_texture(game, ray);
	if (!tex || !tex->addr || tex->w <= 0 || tex->h <= 0)
		return;
	y = start;
	wall_x = impact_wall_x(ray, game, ray->side);
	wall_x -= floor(wall_x); // garde la partie fractionnaire
	tex_x = x_in_texture(ray, wall_x, tex);
	step   = (double)tex->h / (double)(HEIGHT / ray->perpWallDist);
	tex_pos = (start - HEIGHT / 2.0 + (HEIGHT / ray->perpWallDist) / 2.0) * step;
	while (y < end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= tex->h)
			tex_y = tex->h - 1;
		tex_pos += step;
		color = get_tex_safe(tex, tex_x, tex_y);
		mlx_pixel_put_img(game->mlx, x, y, color);
		++y;
	}
}


static inline void	mlx_pixel_put_img(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	dst = NULL;
	if (!mlx || !mlx->addr)
		return;
	if ((unsigned)x >= WIDTH || (unsigned)y >= HEIGHT)
		return;
	dst = (char *)mlx->addr + (y * mlx->line_len + x * (mlx->img_bpp / 8));
	*(unsigned int *)dst = color;
}

static inline unsigned int get_tex_safe(t_textures *tx, int x, int y)
{
	char	*src;

	src = NULL;
	if (!tx || !tx->addr || tx->w <= 0 || tx->h <= 0)
		return (0);
	if (x < 0)
		x = 0;
	else if (x >= tx->w)
		x = tx->w - 1;
	if (y < 0)
		y = 0;
	else if (y >= tx->h)
		y = tx->h - 1;
	src = (char *)tx->addr + (y * tx->line_len + x * (tx->bits_per_pixel / 8));
	return *(unsigned int *)src;
}

static inline t_textures *pick_wall_texture(t_game *g, t_ray *r)
{
	// Convention: side==0 -> mur vertical (impact sur X), side==1 -> mur horizontal (impact sur Y)
	if (r->side == 0 && r->dirX > 0)
		return &g->tex[TEXTURE_WEST];
	if (r->side == 0 && r->dirX < 0)
		return &g->tex[TEXTURE_EAST];
	if (r->side == 1 && r->dirY > 0)
		return &g->tex[TEXTURE_NORTH];
	return &g->tex[TEXTURE_SOUTH];
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
