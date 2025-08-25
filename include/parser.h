#ifndef PARSER_H
# define PARSER_H

#include <stdbool.h>

typedef struct s_game t_game;
typedef struct s_allocator t_alloc;

/* utils */
int		skip_spaces(const char *s);
bool	is_space(char c);
bool	is_empty_line(const char *s);
bool	valid_map_char(char c);
bool	is_walkable(char c);
bool	validate_identifiers(const t_game *c);

/* colors */
bool	parse_rgb_triplet(const char *s, int *out);

/* header parsing */
bool	parse_header_line(t_game *out, char *line);

/* map */
bool	scan_player_and_chars(t_game *c);
bool	validate_closed_map(t_game *c);

/* reading */
bool	parse_lines(t_alloc *a, t_game *out, int fd);

#endif
