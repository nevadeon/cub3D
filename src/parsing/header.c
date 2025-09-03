#include "cub3D.h"
#include "parser.h"
#include "error.h"

static bool	parse_map_line(t_alloc *alloc, t_game *g, char *line)
{
	char	**new_arr;
	char	*copy;
	int		len;
	int		new_h;

	len = (int)str_clen(line, '\n', false);
	copy = str_extract(alloc, line, 0, (size_t)len);
	if (!copy)
		return (RETURN_FAILURE);
	new_h = g->map.height + 1;
	new_arr = mem_alloc(alloc, sizeof(char *) * (new_h + 1));
	if (!new_arr)
		return (RETURN_FAILURE);
	if (g->map.grid)
		str_memcpy(new_arr, g->map.grid, sizeof(char *) * (g->map.height));
	new_arr[g->map.height] = copy;
	new_arr[new_h] = NULL;
	g->map.grid = new_arr;
	g->map.height = new_h;
	if (len > g->map.width)
		g->map.width = len;
	return (RETURN_SUCCESS);
}

bool	trim_path(t_alloc *alloc, const char *src, char **dst)
{
	int	i;
	int len;

	if (*dst)
		return (err_code(ERR_DUP_IDENTIFIER));
	i = skip_spaces(src);
	if (src[i] == '\0')
		return (RETURN_FAILURE);
    len = 0;
    while (src[i + len] && src[i + len] != '\n' && !is_space(src[i + len]))
        len++;
    *dst = str_extract(alloc, (char *)src, i, len);
    return (*dst != NULL);
}

bool	parse_header_line(t_alloc *alloc, t_game *g, char *line)
{
	int		i;

	i = skip_spaces(line);
	if (line[i] == 'N' && line[i + 1] == 'O' && is_space(line[i + 2]))
		return (trim_path(alloc, &line[i + 2], &g->map.tex_no));
	if (line[i] == 'S' && line[i + 1] == 'O' && is_space(line[i + 2]))
		return (trim_path(alloc, &line[i + 2], &g->map.tex_so));
	if (line[i] == 'W' && line[i + 1] == 'E' && is_space(line[i + 2]))
		return (trim_path(alloc, &line[i + 2], &g->map.tex_we));
	if (line[i] == 'E' && line[i + 1] == 'A' && is_space(line[i + 2]))
		return (trim_path(alloc, &line[i + 2], &g->map.tex_ea));
	if (line[i] == 'F' && is_space(line[i + 1]))
		return (parse_rgb_triplet(&line[i + 1], &g->map.floor_rgb));
	if (line[i] == 'C' && is_space(line[i + 1]))
		return (parse_rgb_triplet(&line[i + 1], &g->map.ceil_rgb));
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

	in_map = false;
	while (true)
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
				if (!parse_header_line(alloc, game, line))
					return (RETURN_FAILURE);
				continue ;
			}
			in_map = true;
		}
		if (!parse_map_line(alloc, game, line))
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
