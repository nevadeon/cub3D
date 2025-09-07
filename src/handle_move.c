/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:46:55 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
