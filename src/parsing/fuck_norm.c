/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuck_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:45:54 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parser.h"
#include "error.h"

void	set_player_w_e(t_game *g, char ch)
{
	if (ch == 'W')
	{
		g->player.dir_y = 0;
		g->player.dir_x = -1;
		g->player.plane_x = 0;
		g->player.plane_y = -0.66;
	}
	else if (ch == 'E')
	{
		g->player.dir_y = 0;
		g->player.dir_x = 1;
		g->player.plane_x = 0;
		g->player.plane_y = 0.66;
	}
}
