#include "cub3D.h"
#include "parser.h"
#include "error.h"

static void	init_offsets(int off[4][2])
{
	off[0][0] = 1;
	off[0][1] = 0;
	off[1][0] = -1;
	off[1][1] = 0;
	off[2][0] = 0;
	off[2][1] = 1;
	off[3][0] = 0;
	off[3][1] = -1;
}

static bool	check_neighbors(t_game *g, int x, int y, int off[4][2])
{
	int		k;
	int		nx;
	int		ny;
	int		nlen;
	char	c;

	k = 0;
	while (k < 4)
	{
		nx = x + off[k][0];
		ny = y + off[k][1];
		if (ny < 0 || ny >= g->map.height)
			return (err_code(ERR_MAP_NOT_CLOSED));
		nlen = (int)str_len(g->map.grid[ny]);
		if (nx < 0 || nx >= nlen)
			return (err_code(ERR_MAP_NOT_CLOSED));
		c = g->map.grid[ny][nx];
		if (c == ' ')
			return (err_code(ERR_MAP_NOT_CLOSED));
		k++;
	}
	return (RETURN_SUCCESS);
}

static bool	set_player(t_game *g, char ch, int x, int y)
{
	if (g->player.pos_x != 0)
		return (err_code(ERR_MULTIPLE_PLAYERS));
	g->player.pos_x = x + 0.5;
	g->player.pos_y = y + 0.5;
	if (ch == 'N')
	{
		g->player.dir_y = -1;
		g->player.dir_x = 0;
		g->player.plane_x = 0.66;
		g->player.plane_y = 0;
	}
	else if (ch == 'S')
	{
		g->player.dir_y = 1;
		g->player.dir_x = 0;
		g->player.plane_x = -0.66;
		g->player.plane_y = 0;
	}
	else
		set_player_w_e(g, ch);
	g->map.grid[y][x] = '0';
	return (RETURN_SUCCESS);
}

bool	scan_player_and_chars(t_game *g)
{
	int		y;
	int		x;
	int		len;
	char	c;

	y = 0;
	while (y < g->map.height)
	{
		len = (int)str_len(g->map.grid[y]);
		x = 0;
		while (x < len)
		{
			c = g->map.grid[y][x];
			if (!valid_map_char(c))
				return (err_code(ERR_INVALID_CHAR));
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				if (!set_player(g, c, x, y))
					return (RETURN_FAILURE);
			x++;
		}
		y++;
	}
	if (g->player.pos_x == 0)
		return (err_code(ERR_NO_PLAYER));
	return (RETURN_SUCCESS);
}

bool	validate_closed_map(t_game *g)
{
	int	y;
	int	x;
	int	len;
	int	off[4][2];

	init_offsets(off);
	y = 0;
	while (y < g->map.height)
	{
		len = (int)str_len(g->map.grid[y]);
		x = 0;
		while (x < len)
		{
			if (is_walkable(g->map.grid[y][x]))
				if (!check_neighbors(g, x, y, off))
					return (RETURN_FAILURE);
			x++;
		}
		y++;
	}
	return (RETURN_SUCCESS);
}
