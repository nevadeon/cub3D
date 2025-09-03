#include "cub3D.h"

int	load_all_textures(t_game *game)
{
	game->map.tex_no = "/home/echapuis/Projets_42/cub3d/textures/no.xpm";
	game->map.tex_so = "/home/echapuis/Projets_42/cub3d/textures/so.xpm";
 	game->map.tex_ea = "/home/echapuis/Projets_42/cub3d/textures/ea.xpm";
 	game->map.tex_we = "/home/echapuis/Projets_42/cub3d/textures/we.xpm";

	if (load_texture(game->mlx, &game->tex[TEXTURE_NORTH], game->map.tex_no))
		return (EXIT_FAILURE);
	if (load_texture(game->mlx, &game->tex[TEXTURE_SOUTH], game->map.tex_so))
		return (EXIT_FAILURE);
	if (load_texture(game->mlx, &game->tex[TEXTURE_WEST], game->map.tex_we))
		return (EXIT_FAILURE);
	if (load_texture(game->mlx, &game->tex[TEXTURE_EAST], game->map.tex_ea))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	load_texture(t_mlx *mlx, t_textures *tx, char *path)
{
	tx->img = mlx_xpm_file_to_image(mlx->mlx_init, path, &tx->w, &tx->h);
	if (!tx->img || tx->w <= 0 || tx->h <= 0)
		return (fprintf(stderr, "Load fail: %s\n", path), (EXIT_FAILURE));

	tx->addr = mlx_get_data_addr(tx->img, &tx->bits_per_pixel, &tx->line_len, &tx->endian);
	if (!tx->addr || tx->bits_per_pixel < 24)
		return (fprintf(stderr, "Data addr fail: %s\n", path), (EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
