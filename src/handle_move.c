#include "cub3D.h"
#include <stdio.h>

void	handle_move(t_game *game)
{
	if (game->keys.w == 1)
		move_forward(game);
	else if (game->keys.s == 1)
		move_backward(game);
	else if (game->keys.a == 1)
		move_left(game);
	else if (game->keys.d == 1)
		move_right(game);
	else if (game->keys.left || game->keys.right)
		rotate(game);
	// dprintf(2, "dirx = %f | dirY = %f\n", game->player.dirX, game->player.dirY);
}

// nord x 0 y -2
// sud  x 0 y 2
// ouest x -2 y 0
// est  x 2 y 0
