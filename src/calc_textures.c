/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:46:48 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	calc_tex_pos(int start, t_ray *ray, double step)
{
	double	tex_pos;

	tex_pos = (start - HEIGHT / 2.0
			+ (HEIGHT / ray->perp_wall_dist) / 2.0) * step;
	return (tex_pos);
}

double	calc_tex_step(t_ray *ray, t_textures *tex)
{
	double	step;

	step = 0.0;
	if (ray->perp_wall_dist > 0)
		step = (double)tex->h / (HEIGHT / ray->perp_wall_dist);
	return (step);
}

inline unsigned int	get_tex_safe(t_textures *tx, int x, int y)
{
	char	*src;

	src = NULL;
	if (!tx || !tx->addr || tx->w <= 0 || tx->h <= 0)
		return (0);
	if (x < 0)
		x = 0;
	else if (x >= tx->w)
		x = tx->w - 1;
	if (y < 0)
		y = 0;
	else if (y >= tx->h)
		y = tx->h - 1;
	src = (char *)tx->addr + (y * tx->line_len + x * (tx->bits_per_pixel / 8));
	return (*((unsigned int *)(src)));
}
