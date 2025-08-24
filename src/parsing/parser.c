#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "cub3D.h"
#include "parser.h"
#include "error.h"

/* init */
static void	init_game(t_game *c)
{
	*c = (t_game)
	{
		.tex_no = NULL,
		.tex_so = NULL,
		.tex_we = NULL,
		.tex_ea = NULL,
		.floor_rgb = -1,
		.ceil_rgb = -1,
		.map = NULL,
		.map_w = 0,
		.map_h = 0,
		.player_x = -1,
		.player_y = -1,
		.player_dir = '\0',
	};
}

bool	validate_identifiers(const t_game *c)
{
	if (!c->tex_no || !c->tex_so || !c->tex_we || !c->tex_ea)
		return (error(ERR_INV_IDENTIFIER));
	if (c->floor_rgb == -1 || c->ceil_rgb == -1)
		return (error(ERR_INV_IDENTIFIER));
	if (!c->map || c->map_h <= 0 || c->map_w <= 0)
		return (error(ERR_MISSING_MAP));
	return (true);
}

bool	parse_cub_file(t_alloc *alloc, const char *path, t_game *out)
{
	int	fd;

	init_game(out);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error(ERR_OPEN_FAILED));
	if (!parse_lines(alloc, fd, out))
		return (close(fd), false);
	close(fd);
	if (!validate_identifiers(out))
		return (false);
	if (!scan_player_and_chars(out))
		return (false);
	if (!validate_closed_map(out))
		return (false);
	return (true);
}
