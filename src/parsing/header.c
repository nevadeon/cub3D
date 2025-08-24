#include "cub3D.h"
#include "parser.h"
#include "error.h"

static bool	parse_map_line(
		t_alloc *a, char ***arr, int *h, int *w, char *line)
{
	int		len;
	int		new_h;
	char	*copy;
	char	**new_arr;

	len = (int)str_clen(line, '\n', false);
	copy = str_extract(a, line, 0, (size_t)len);
	if (!copy)
		return (false);
	new_h = *h + 1;
	new_arr = mem_alloc(a, sizeof(char *) * (new_h + 1));
	if (!new_arr)
		return (false);
	if (*arr)
		str_memcpy(new_arr, *arr, sizeof(char *) * (*h));
	new_arr[*h] = copy;
	new_arr[new_h] = NULL;
	*arr = new_arr;
	*h = new_h;
	if (len > *w)
		*w = len;
	return (true);
}

bool	trim_path(const char *src, char **dst)
{
	int i;

	if (*dst)
		return (error(ERR_DUP_IDENTIFIER));
	i = skip_spaces(src);
	if (src[i] == '\0')
		return (false);
	*dst = (char *)&src[i];
	return (true);
}

bool	parse_header_line(t_game *out, char *line)
{
	int		i;

	i = skip_spaces(line);
	if (line[i] == 'N' && line[i + 1] == 'O' && is_space(line[i + 2]))
		return (trim_path(&line[i + 2], &out->tex_no));
	if (line[i] == 'S' && line[i + 1] == 'O' && is_space(line[i + 2]))
		return (trim_path(&line[i + 2], &out->tex_so));
	if (line[i] == 'W' && line[i + 1] == 'E' && is_space(line[i + 2]))
		return (trim_path(&line[i + 2], &out->tex_we));
	if (line[i] == 'E' && line[i + 1] == 'A' && is_space(line[i + 2]))
		return (trim_path(&line[i + 2], &out->tex_ea));
	if (line[i] == 'F' && is_space(line[i + 1]))
		return (parse_rgb_triplet(&line[i + 1], &out->floor_rgb));
	if (line[i] == 'C' && is_space(line[i + 1]))
		return (parse_rgb_triplet(&line[i + 1], &out->ceil_rgb));
	return (false);
}

static bool is_header_prefix(const char *line)
{
	int i;

	i = skip_spaces(line);
	if ((line[i] == 'N' && line[i + 1] == 'O' && is_space(line[i + 2]))
	 || (line[i] == 'S' && line[i + 1] == 'O' && is_space(line[i + 2]))
	 || (line[i] == 'W' && line[i + 1] == 'E' && is_space(line[i + 2]))
	 || (line[i] == 'E' && line[i + 1] == 'A' && is_space(line[i + 2]))
	 || (line[i] == 'F' && is_space(line[i + 1]))
	 || (line[i] == 'C' && is_space(line[i + 1])))
		return (true);
	return (false);
}

bool	parse_lines(t_alloc *a, int fd, t_game *out)
{
	char	*line;
	bool	in_map;

	in_map = false;
	while (true)
	{
		line = str_gnl(a, fd);
		if (!line)
			break ;
		if (!in_map)
		{
			if (is_empty_line(line))
				continue ;
			if (is_header_prefix(line))
			{
				if (!parse_header_line(out, line))
					return (false);
				continue ;
			}
			in_map = true;
		}
		if (!parse_map_line(a, &out->map, &out->map_h, &out->map_w, line))
			return (false);
	}
	return (true);
}
