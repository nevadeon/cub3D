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
}
