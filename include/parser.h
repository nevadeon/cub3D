#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

/* utils */
int		skip_spaces(const char *s);
bool	is_space(char c);
bool	is_empty_line(const char *s);
bool	valid_map_char(char c);
bool	is_walkable(char c);
bool	validate_identifiers(const t_cub *c);

/* colors */
bool	parse_rgb_triplet(const char *s, int *out);

/* header parsing */
bool	parse_header_line(t_cub *out, char *line);

/* map */
bool	scan_player_and_chars(t_cub *c);
bool	validate_closed_map(t_cub *c);

/* reading */
bool	parse_lines(t_alloc *a, int fd, t_cub *out);

#endif
