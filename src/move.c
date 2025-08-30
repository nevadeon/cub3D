#include "cub3D.h"

void	move_forward(t_game *game)
{
	double	move_speed;
	double	player_radius;
	double	new_x;
	double	new_y;
	double	offset;

	move_speed = 0.02;
	player_radius = 0.2;

	if (game->player.dirX > 0)
		offset = player_radius;
	else
		offset = -player_radius;
	new_x = game->player.posX + game->player.dirX * move_speed;
	new_y = game->player.posY + game->player.dirY * move_speed;
	if (game->map[(int)game->player.posY][(int)(new_x + offset)] == '0')
		game->player.posX = new_x;
	if (game->player.dirY > 0)
		offset = player_radius;
	else
		offset = -player_radius;
	if (game->map[(int)(new_y + offset)][(int)game->player.posX] == '0')
		game->player.posY = new_y;
}

void	move_backward(t_game *game)
{
	double	player_radius;
	double	move_speed;
	double	rot_speed;
	double	new_x;
	double	new_y;
	double	offset;

	move_speed = 0.02;
	rot_speed = 0.005;
	player_radius = 0.2;

	//colision X
	if (game->player.dirX < 0)
		offset = player_radius;
	else
		offset = -player_radius;
	new_x = game->player.posX - game->player.dirX * move_speed;
	new_y = game->player.posY - game->player.dirY * move_speed;
	if (game->map[(int)game->player.posY][(int)(new_x + offset)] == '0')
		game->player.posX = new_x;

	//colision Y
	if (game->player.dirY < 0)
		offset = player_radius;
	else
		offset = -player_radius;
	if (game->map[(int)(new_y + offset)][(int)game->player.posX] == '0')
		game->player.posY = new_y;
}

void	move_left(t_game *game)
{
	double	player_radius;
	double	move_speed;
	double	rot_speed;
	double	new_x;
	double	new_y;
	double	offset;

	move_speed = 0.02;
	rot_speed = 0.005;
	player_radius = 0.2;
	new_x = game->player.posX - game->player.planeX * move_speed;
	new_y = game->player.posY - game->player.planeY * move_speed;
	if (-game->player.planeX > 0)
		offset = player_radius;
	else
		offset = -player_radius;
	if (game->map[(int)game->player.posY][(int)(new_x + offset)] == '0')
		game->player.posX = new_x;

	if (-game->player.planeY > 0)
		offset = player_radius;
	else
		offset = -player_radius;
	if (game->map[(int)(new_y + offset)][(int)game->player.posX] == '0')
		game->player.posY = new_y;
}

void	move_right(t_game *game)
{
	double	player_radius;
	double	move_speed;
	double	rot_speed;
	double	new_x;
	double	new_y;
	double	offset;

	player_radius = 0.2;
	move_speed = 0.02;
	rot_speed = 0.005;
	new_x = game->player.posX + game->player.planeX * move_speed;
	new_y = game->player.posY + game->player.planeY * move_speed;
	if (game->player.planeX > 0)
		offset = player_radius;
	else
		offset = -player_radius;
	if (game->map[(int)game->player.posY][(int)(new_x + offset)] == '0')
		game->player.posX = new_x;
	if (game->player.planeY > 0)
		offset = player_radius;
	else
		offset = -player_radius;
	if (game->map[(int)(new_y + offset)][(int)game->player.posX] == '0')
		game->player.posY = new_y;
}

void	rotate(t_game *game)
{
	double	angle;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.03;
	angle = rot_speed;
	old_dir_x = game->player.dirX;
	old_plane_x = game->player.planeX;
	if (game->keys.right)
		angle = -rot_speed;
	game->player.dirX = game->player.dirX * cos(angle) - game->player.dirY * sin(angle);
	game->player.dirY = old_dir_x * sin(angle) + game->player.dirY * cos(angle);
	game->player.planeX = game->player.planeX * cos(angle) - game->player.planeY * sin(angle);
	game->player.planeY = old_plane_x * sin(angle) + game->player.planeY * cos(angle);
}
