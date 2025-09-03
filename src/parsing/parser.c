#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "cub3D.h"
#include "parser.h"
#include "error.h"

bool	validate_identifiers(const t_game *g)
{
	if (!g->map.tex_no || !g->map.tex_so || !g->map.tex_we || !g->map.tex_ea)
		return (err_code(ERR_INV_IDENTIFIER));
	if (g->map.floor_rgb == -1 || g->map.ceil_rgb == -1)
		return (err_code(ERR_INV_IDENTIFIER));
	if (!g->map.grid || g->map.height <= 0 || g->map.width <= 0)
		return (err_code(ERR_MISSING_MAP));
	return (RETURN_SUCCESS);
}

bool	parse_cub_file(t_alloc *alloc, t_game *game, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (err_errno(), err_code(ERR_OPEN_FAILED));
	if (!parse_lines(alloc, game, fd))
		return (close(fd), RETURN_FAILURE);
	close(fd);
	if (!validate_identifiers(game))
		return (RETURN_FAILURE);
	if (!scan_player_and_chars(game))
		return (RETURN_FAILURE);
	if (!validate_closed_map(game))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
