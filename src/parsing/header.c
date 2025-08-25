#include "cub3D.h"
#include "parser.h"
#include "error.h"

static bool	parse_map_line(t_alloc *alloc, t_game *g, char *line)
{
	int		len;
	int		new_h;
	char	*copy;
	char	**new_arr;

	len = (int)str_clen(line, '\n', RETURN_FAILURE);
	copy = str_extract(alloc, line, 0, (size_t)len);
	if (!copy)
		return (RETURN_FAILURE);
	new_h = g->map_h + 1;
	new_arr = mem_alloc(alloc, sizeof(char *) * (new_h + 1));
	if (!new_arr)
		return (RETURN_FAILURE);
	if (g->map)
		str_memcpy(new_arr, g->map, sizeof(char *) * (g->map_h));
	new_arr[g->map_h] = copy;
	new_arr[new_h] = NULL;
	g->map = new_arr;
	g->map_h = new_h;
	if (len > g->map_w)
		g->map_w = len;
	return (RETURN_SUCCESS);
}

bool	trim_path(const char *src, char **dst)
{
	int	i;

	if (*dst)
		return (error_push_code(ERR_DUP_IDENTIFIER));
	i = skip_spaces(src);
	if (src[i] == '\0')
		return (RETURN_FAILURE);
	*dst = (char *)&src[i];
	return (RETURN_SUCCESS);
}

bool	parse_header_line(t_game *g, char *line)
{
	int		i;

	i = skip_spaces(line);
	if (line[i] == 'N' && line[i + 1] == 'O' && is_space(line[i + 2]))
		return (trim_path(&line[i + 2], &g->tex_no));
	if (line[i] == 'S' && line[i + 1] == 'O' && is_space(line[i + 2]))
		return (trim_path(&line[i + 2], &g->tex_so));
	if (line[i] == 'W' && line[i + 1] == 'E' && is_space(line[i + 2]))
		return (trim_path(&line[i + 2], &g->tex_we));
	if (line[i] == 'E' && line[i + 1] == 'A' && is_space(line[i + 2]))
		return (trim_path(&line[i + 2], &g->tex_ea));
	if (line[i] == 'F' && is_space(line[i + 1]))
		return (parse_rgb_triplet(&line[i + 1], &g->floor_rgb));
	if (line[i] == 'C' && is_space(line[i + 1]))
		return (parse_rgb_triplet(&line[i + 1], &g->ceil_rgb));
	return (RETURN_FAILURE);
}

static bool	is_header_prefix(const char *line)
{
	int	i;

	i = skip_spaces(line);
	if ((line[i] == 'N' && line[i + 1] == 'O' && is_space(line[i + 2]))
		|| (line[i] == 'S' && line[i + 1] == 'O' && is_space(line[i + 2]))
		|| (line[i] == 'W' && line[i + 1] == 'E' && is_space(line[i + 2]))
		|| (line[i] == 'E' && line[i + 1] == 'A' && is_space(line[i + 2]))
		|| (line[i] == 'F' && is_space(line[i + 1]))
		|| (line[i] == 'C' && is_space(line[i + 1])))
		return (RETURN_SUCCESS);
	return (RETURN_FAILURE);
}

bool	parse_lines(t_alloc *alloc, t_game *game, int fd)
{
	char	*line;
	bool	in_map;

	in_map = RETURN_FAILURE;
	while (RETURN_SUCCESS)
	{
		line = str_gnl(alloc, fd);
		if (!line)
			break ;
		if (!in_map)
		{
			if (is_empty_line(line))
				continue ;
			if (is_header_prefix(line))
			{
				if (!parse_header_line(game, line))
					return (RETURN_FAILURE);
				continue ;
			}
			in_map = RETURN_SUCCESS;
		}
		if (!parse_map_line(alloc, game, line))
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
