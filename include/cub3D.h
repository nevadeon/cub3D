#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
//#include "libft/libft.h"
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
# define WIDTH			1000
# define HEIGHT			800
# define TILE_SIZE		64
# define PLANE_Y		0.90 // FOV ~ 66°

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

typedef struct s_mlx
{
	void	*mlx_init; //--> ptr vers mlx_init()
	void	*mlx_win; //--> fenetre
	void	*img_ptr; //--> img buffer
	void	*addr; //-->acces au pixels
	int		img_bpp; // bits pr pixel
	int		line_len; //long d'une ligne en memoire
	int		endian;
}	t_mlx;

typedef struct s_keys
{
	int right; //--> rotate right
	int left; // --> rotate left
	int w; // --> move forward
	int s; // --> move backward
	int a; // --> left
	int d; // --> right
}	t_keys;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}	t_player;

// planeX planeY define the 2D plane perpendicular to the player view direction
// determine : FOV, projection of 3D walls

typedef struct s_ray
{
	float	perpWallDist;
	int		mapX;
	int		mapY;
	int		side;
	float	dirX;
	float	dirY;
	float	stepX;
	float	stepY;
	float	sideDistX;
	float	sideDistY;
	float	deltaDistX;
	float	deltaDistY;
}	t_ray;

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
void	draw_pixel(t_mlx *mlx, int x, int y_start, int y_end, int color);

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
void draw_wall(t_ray *ray, t_game *game, int x);
void draw_vertical_line(t_mlx *mlx, int x, int start, int end, int color);

/*
		//MOVEMENT//
*/

void	handle_move(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate(t_game *game);
#endif
