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
