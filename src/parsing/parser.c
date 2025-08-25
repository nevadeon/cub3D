#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "cub3D.h"
#include "parser.h"
#include "error.h"

bool	validate_identifiers(const t_game *game)
{
	if (!game->tex_no || !game->tex_so || !game->tex_we || !game->tex_ea)
		return (error_push_code(ERR_INV_IDENTIFIER));
	if (game->floor_rgb == -1 || game->ceil_rgb == -1)
		return (error_push_code(ERR_INV_IDENTIFIER));
	if (!game->map || game->map_h <= 0 || game->map_w <= 0)
		return (error_push_code(ERR_MISSING_MAP));
	return (RETURN_SUCCESS);
}

bool	parse_cub_file(t_alloc *alloc, t_game *game, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_push_errno(), error_push_code(ERR_OPEN_FAILED));
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
