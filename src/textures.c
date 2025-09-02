#include "cub3D.h"

// void	load_texture(t_game *game)
// {
// 	game->map.tex_no = "/home/echapuis/Projets_42/cub3d/textures/no.xpm";
// game->map.tex_so = "/home/echapuis/Projets_42/cub3d/textures/so.xpm";
// game->map.tex_ea = "/home/echapuis/Projets_42/cub3d/textures/ea.xpm";
// game->map.tex_we = "/home/echapuis/Projets_42/cub3d/textures/we.xpm";

// char *paths[4] = {game->map.tex_no, game->map.tex_so, game->map.tex_we, game->map.tex_ea};

// for (int i = 0; i < 4; i++) // assuming 4 textures
// {
//     game->tex[i].img = mlx_xpm_file_to_image(
//         game->mlx,
//         paths[i],
//         &game->tex[i].w,
//         &game->tex[i].h
//     );
//     if (!game->tex[i].img)
//     {
//         fprintf(stderr, "Failed to load texture: %s\n", paths[i]);
//         exit(EXIT_FAILURE);
//     }

//     game->tex[i].addr = mlx_get_data_addr(
//         game->tex[i].img,
//         &game->tex[i].bits_per_pixel,
//         &game->tex[i].line_len,
//         &game->tex[i].endian
//     );

//     game->tex[i].pixel = malloc(sizeof(int) * game->tex[i].w * game->tex[i].h);
//     if (!game->tex[i].pixel)
// 	{
// 		printf("failed");
//         exit(EXIT_FAILURE);
// 	}
// 	//printf("end of boucle\n");
//     for (int y = 0; y < game->tex[i].h; y++)
//     {
//         for (int x = 0; x < game->tex[i].w; x++)
//         {
//             game->tex[i].pixel[y * game->tex[i].w + x] =
//                 *(int *)(game->tex[i].addr + y * game->tex[i].line_len + x * (game->tex[i].bits_per_pixel / 8));
//         }
//     }
// 	//printf("end of boucle\n");
// }
// }


void	load_texture(t_game *game)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	game->map.tex_no = "/home/echapuis/Projets_42/cub3d/textures/no.xpm";
	game->map.tex_so = "/home/echapuis/Projets_42/cub3d/textures/so.xpm";
	game->map.tex_ea = "/home/echapuis/Projets_42/cub3d/textures/ea.xpm";
	game->map.tex_we = "/home/echapuis/Projets_42/cub3d/textures/we.xpm";
	char *paths[4] = {game->map.tex_no, game->map.tex_so, game->map.tex_we, game->map.tex_ea};
	// printf("tex_no: %s\n", game->map.tex_no ? game->map.tex_no : "(null)");
	// printf("tex_so: %s\n", game->map.tex_so ? game->map.tex_so : "(null)");
	// printf("tex_we: %s\n", game->map.tex_we ? game->map.tex_we : "(null)");
	// printf("tex_ea: %s\n", game->map.tex_ea ? game->map.tex_ea : "(null)");
	printf("%s texture : ",paths[0]);
	// printf("%s : ", game->map.tex_no);
	// 	if (!game->map.tex_no || access(game->map.tex_no, F_OK) == -1)
	// {
	//     fprintf(stderr, "Texture file not found: %s\n", game->map.tex_no);
	//     exit(EXIT_FAILURE);
	// }


	// printf("MLX ptr: %p\n", game->mlx->mlx_init);
	// printf("Trying to load texture: %s\n", game->map.tex_no);
	i = 0;
	while (i < 4)
	{
		game->tex[i].img = mlx_xpm_file_to_image(game->mlx->mlx_init, paths[i], &game->tex[i].w, &game->tex[i].h);
		if (!game->tex[i].img) {
    		perror("mlx_xpm_file_to_image failed 111111111111111111");
    		exit(EXIT_FAILURE);
		}
		game->tex[i].pixel = malloc(sizeof(int) * game->tex[i].w * game->tex[i].h);
		if (!game->tex[i].pixel)
		{
			printf("fuck 2");
			exit(0);
		}


		//i = 0;
		//game->tex[i].pixel = malloc(sizeof(int) * game->tex[i].w * game->tex[i].h);
		for (y = 0; y < game->tex[i].h; y++)
		{
			for (x = 0; x < game->tex[i].w; x++)
			{
				int offset = y * game->tex[i].line_len + x * (game->tex[i].bits_per_pixel / 8);
				game->tex[i].pixel[y * game->tex[i].w + x] = *(int *)(game->tex[i].addr + offset);
			}
		}
		i++;
	}

	// i = 0;
	// while (i < 4)
	// {
	// 	y = 0;
	// 	while (y < game->tex[i].h)
	// 	{
	// 		x = 0;
	// 		while (x < game->tex[i].w)
	// 		{
	// 			game->tex[i].pixel[y * game->tex[i].w + x] = *(int *)(game->tex[i].addr + y * game->tex[i].line_len + x * (game->tex[i].bits_per_pixel / 8));
	// 			x++;
	// 		}
	// 		y++;
	// 	}
	//  	i++;
	// }
}


int	get_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dirX > 0)
			return (TEXTURE_EAST);
		else
			return (TEXTURE_WEST);
	}
	else
	{
		if (ray->dirY > 0)
			return (TEXTURE_SOUTH);
		else
			return (TEXTURE_NORTH);
	}
}
