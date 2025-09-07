#include "cub3D.h"

void	move_forward(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;
	double	offset;

	move_speed = 0.02;
	if (game->player.dir_x > 0)
		offset = 0.2;
	else
		offset = -0.2;
	new_x = game->player.pos_x + game->player.dir_x * move_speed;
	new_y = game->player.pos_y + game->player.dir_y * move_speed;
	if (game->map.grid[(int)game->player.pos_y][(int)(new_x + offset)] == '0')
		game->player.pos_x = new_x;
	if (game->player.dir_y > 0)
		offset = 0.2;
	else
		offset = -0.2;
	if (game->map.grid[(int)(new_y + offset)][(int)game->player.pos_x] == '0')
		game->player.pos_y = new_y;
}

void	move_backward(t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double	new_x;
	double	new_y;
	double	offset;

	move_speed = 0.02;
	rot_speed = 0.005;
	if (game->player.dir_x < 0)
		offset = 0.2;
	else
		offset = -0.2;
	new_x = game->player.pos_x - game->player.dir_x * move_speed;
	new_y = game->player.pos_y - game->player.dir_y * move_speed;
	if (game->map.grid[(int)game->player.pos_y][(int)(new_x + offset)] == '0')
		game->player.pos_x = new_x;
	if (game->player.dir_y < 0)
		offset = 0.2;
	else
		offset = -0.2;
	if (game->map.grid[(int)(new_y + offset)][(int)game->player.pos_x] == '0')
		game->player.pos_y = new_y;
}

void	move_left(t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double	new_x;
	double	new_y;
	double	offset;

	move_speed = 0.02;
	rot_speed = 0.005;
	new_x = game->player.pos_x - game->player.plane_x * move_speed;
	new_y = game->player.pos_y - game->player.plane_y * move_speed;
	if (-game->player.plane_x > 0)
		offset = 0.2;
	else
		offset = -0.2;
	if (game->map.grid[(int)game->player.pos_y][(int)(new_x + offset)] == '0')
		game->player.pos_x = new_x;
	if (-game->player.plane_y > 0)
		offset = 0.2;
	else
		offset = -0.2;
	if (game->map.grid[(int)(new_y + offset)][(int)game->player.pos_x] == '0')
		game->player.pos_y = new_y;
}

void	move_right(t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double	new_x;
	double	new_y;
	double	offset;

	move_speed = 0.02;
	rot_speed = 0.005;
	new_x = game->player.pos_x + game->player.plane_x * move_speed;
	new_y = game->player.pos_y + game->player.plane_y * move_speed;
	if (game->player.plane_x > 0)
		offset = 0.2;
	else
		offset = -0.2;
	if (game->map.grid[(int)game->player.pos_y][(int)(new_x + offset)] == '0')
		game->player.pos_x = new_x;
	if (game->player.plane_y > 0)
		offset = 0.2;
	else
		offset = -0.2;
	if (game->map.grid[(int)(new_y + offset)][(int)game->player.pos_x] == '0')
		game->player.pos_y = new_y;
}

void	rotate(t_game *game)
{
	double	angle;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.03;
	angle = -rot_speed;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	if (game->keys.right)
		angle = rot_speed;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	game->player.plane_x = game->player.plane_x
		* cos(angle) - game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}
