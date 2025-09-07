#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdarg.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <fcntl.h>
# include <math.h>

# include "parser.h"
# include "error.h"
# include "allocators/allocator.h"
# include "allocators/mgc_allocator.h"
# include "tools/str.h"

# define RETURN_FAILURE	false
# define RETURN_SUCCESS true

# define WINDOW_NAME	"Cub3D"
# define WIDTH			1500
# define HEIGHT			900
# define TILE_SIZE		64

# define TEXTURE_NORTH	0
# define TEXTURE_SOUTH	1
# define TEXTURE_EAST	2
# define TEXTURE_WEST	3

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

typedef struct s_mlx
{
	void	*mlx_init;
	void	*mlx_win;
	void	*img_ptr;
	void	*addr;
	int		img_bpp;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_keys
{
	int	right;
	int	left;
	int	w;
	int	s;
	int	a;
	int	d;
}	t_keys;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	float	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		side;
	float	dir_x;
	float	dir_y;
	float	step_x;
	float	step_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
}	t_ray;

typedef struct s_draw
{
	int		x;
	int		start;
	int		end;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_draw;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
	int		w;
	int		h;
	int		*pixel;
	int		tex_x;
	int		tex_y;
	float	step;
	float	tex_pos;
	int		color;
}	t_textures;

typedef struct s_map
{
	char	**grid;
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		width;
	int		height;
	int		floor_rgb;
	int		ceil_rgb;
}	t_map;

typedef struct s_game
{
	t_mlx		*mlx;
	t_map		map;
	t_player	player;
	t_keys		keys;
	t_ray		ray;
	t_textures	tex[4];
}	t_game;

bool	parse_args(int argc, char const *argv[]);
bool	parse_cub_file(t_alloc *alloc, t_game *out, const char *path);

/*
        // INIT_MLX //
*/
bool	init_mlx(t_game *game, t_mlx *mlx);
void	run_mlx(t_mlx *mlx, t_game *game);
void	destroy(t_mlx *mlx);

int		cross_escape(t_mlx *mlx);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);

/*
        // RAYCASTING //
*/
void	clear_image(t_mlx *mlx, int color);
int		render(t_game *game);
void	raycast(t_game *game);
void	put_pixel(t_mlx *mlx, int x, int y, unsigned int color);

/*
		// RAYS //
*/

void	cast_all_rays(t_game *game);
void	cast_ray(t_game *game, int x);
void	init_ray(t_game *game, int x);

/*
		// DDA //
*/
void	init_step(t_ray *ray, t_game *game);
void	dda_algorithm(t_game *game, t_ray *ray);
void	calculate_perp_wall_dist(t_ray *ray, t_game *game);

/*
		// DRAW //
*/
void	draw_wall(t_ray *ray, t_game *game, int x);
void	draw_ceil(t_mlx *mlx, t_draw draw, int color);
void	draw_floor(t_mlx *mlx, t_draw draw, int color);
void	draw_wall_stripe(t_game *game, t_textures *tex, t_draw draw);
void	draw_textured_wall(t_game *game, t_ray *ray, t_draw draw);

t_textures	*pick_wall_texture(t_game *g, t_ray *r);
unsigned int				get_tex_safe(t_textures *tx, int x, int y);

int		get_pixel_color(t_textures *tex, int x, int y);
void	mlx_pixel_put_img(t_mlx *mlx, int x, int y, unsigned int color);
double	impact_wall_x(t_ray *ray, t_game *game, int ray_side);
int		x_in_texture(t_ray *ray, double wall_x, t_textures *tex);
double	calc_tex_pos(int start, t_ray *ray, double step);
double	calc_tex_step(t_ray *ray, t_textures *tex);
/*
		//MOVEMENT//
*/
void	handle_move(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate(t_game *game);
/*
		//TEXTURES//
*/
void	free_textures(t_game *game);
bool	load_all_textures(t_game *game);

#endif
