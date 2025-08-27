#include "cub3D.h"

void	handle_move(t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double	newX;
	double	newY;
	double	old_dirX;
	double	old_planeX;
	double angle;

	move_speed = 0.1;
	rot_speed = 0.05;
	angle = rot_speed;
	newX = 0;
	newY = 0;
	if (game->keys.w == 1)
		move_forward(game);
	else if (game->keys.s == 1)
		move_backward(game);
	else if (game->keys.a == 1)
		move_left(game);
	else if (game->keys.d == 1)
		move_right(game);
	else if (game->keys.left || game->keys.right)
	{
		old_dirX = game->player.dirX;
		old_planeX = game->player.planeX;
		if (game->keys.left)
			angle = -rot_speed;
		// Rotate direction vector
		game->player.dirX = game->player.dirX * cos(angle) - game->player.dirY * sin(angle);
		game->player.dirY = old_dirX * sin(angle) + game->player.dirY * cos(angle);

		// Rotate camera plane
		game->player.planeX = game->player.planeX * cos(angle) - game->player.planeY * sin(angle);
		game->player.planeY = old_planeX * sin(angle) + game->player.planeY * cos(angle);
	}
}

void move_forward(t_game *game)
{
	double move_speed;
	double newX;
	double newY;

	move_speed = 0.1;
	newX = game->player.posX + game->player.dirX * move_speed;
	newY = game->player.posY + game->player.dirY * move_speed;
	if (game->map[(int)game->player.posY][(int)newX] == '0')
		game->player.posX = newX;
	if (game->map[(int)newY][(int)game->player.posX] == '0')
		game->player.posY = newY;
}


void	move_backward(t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double newX;
	double newY;

	move_speed = 0.1;
	rot_speed = 0.05;

	newX = game->player.posX - game->player.dirX * move_speed;
	newY = game->player.posY - game->player.dirY * move_speed;
	if (game->map[(int)game->player.posY][(int)newX] == '0')
		game->player.posX = newX;
	if (game->map[(int)newY][(int)game->player.posX] == '0')
		game->player.posY = newY;
}

void	move_left(t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double newX;
	double newY;

	move_speed = 0.1;
	rot_speed = 0.05;

	newX = game->player.posX - game->player.planeX * move_speed;
	newY = game->player.posY - game->player.planeY * move_speed;
	if (game->map[(int)game->player.posY][(int)newX] == '0')
		game->player.posX = newX;
	if (game->map[(int)newY][(int)game->player.posX] == '0')
		game->player.posY = newY;
}

void	move_right(t_game *game)
{
	double	move_speed;
	double	rot_speed;
	double newX;
	double newY;

	move_speed = 0.1;
	rot_speed = 0.05;
	newX = game->player.posX + game->player.planeX * move_speed;
	newY = game->player.posY + game->player.planeY * move_speed;
	if (game->map[(int)game->player.posY][(int)newX] == '0')
		game->player.posX = newX;
	if (game->map[(int)newY][(int)game->player.posX] == '0')
		game->player.posY = newY;
}
