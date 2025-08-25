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

static bool	check_neighbors(t_game *c, int x, int y, int off[4][2])
{
	int		k;
	int		nx;
	int		ny;
	int		nlen;
	char	ch;

	k = 0;
	while (k < 4)
	{
		nx = x + off[k][0];
		ny = y + off[k][1];
		if (ny < 0 || ny >= c->map_h)
			return (error_push_code(ERR_MAP_NOT_CLOSED));
		nlen = (int)str_len(c->map[ny]);
		if (nx < 0 || nx >= nlen)
			return (error_push_code(ERR_MAP_NOT_CLOSED));
		ch = c->map[ny][nx];
		if (ch == ' ')
			return (error_push_code(ERR_MAP_NOT_CLOSED));
		k++;
	}
	return (RETURN_SUCCESS);
}

static bool	set_player(t_game *c, char ch, int x, int y)
{
	if (c->player_dir != '\0')
		return (error_push_code(ERR_MULTIPLE_PLAYERS));
	c->player_x = x;
	c->player_y = y;
	c->player_dir = ch;
	return (RETURN_SUCCESS);
}

bool	scan_player_and_chars(t_game *c)
{
	int			y;
	int			x;
	int			len;
	char		ch;

	y = 0;
	while (y < c->map_h)
	{
		len = (int)str_len(c->map[y]);
		x = 0;
		while (x < len)
		{
			ch = c->map[y][x];
			if (!valid_map_char(ch))
				return (error_push_code(ERR_INVALID_CHAR));
			if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
				if (!set_player(c, ch, x, y))
					return (RETURN_FAILURE);
			x++;
		}
		y++;
	}
	if (c->player_dir == '\0')
		return (error_push_code(ERR_NO_PLAYER));
	return (RETURN_SUCCESS);
}

bool	validate_closed_map(t_game *c)
{
	int	y;
	int	x;
	int	len;
	int	off[4][2];

	init_offsets(off);
	y = 0;
	while (y < c->map_h)
	{
		len = (int)str_len(c->map[y]);
		x = 0;
		while (x < len)
		{
			if (is_walkable(c->map[y][x]))
				if (!check_neighbors(c, x, y, off))
					return (RETURN_FAILURE);
			x++;
		}
		y++;
	}
	return (RETURN_SUCCESS);
}
