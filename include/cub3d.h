#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>

# include "allocator.h"
# include "mgc_allocator.h"
# include "str.h"

typedef struct s_cub
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_rgb;
	int		ceil_rgb;
	char	**map;
	int		map_w;
	int		map_h;
	int		player_x;
	int		player_y;
	char	player_dir;
} t_cub;

bool	parse_args(int argc, char const *argv[]);
bool	parse_cub_file(t_alloc *alloc, const char *path, t_cub *out);

#endif
