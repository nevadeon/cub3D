/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:45:52 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parser.h"
#include "error.h"

static bool	read_uint_255(const char *s, int *i, int *v)
{
	int	acc;

	acc = 0;
	if (s[*i] < '0' || s[*i] > '9')
		return (RETURN_FAILURE);
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		acc = acc * 10 + (s[*i] - '0');
		if (acc > 255)
			return (err_code(ERR_RGB_OVERFLOW));
		(*i)++;
	}
	*v = acc;
	return (RETURN_SUCCESS);
}

static bool	skip_comma_spaces(const char *s, int *i)
{
	if (s[*i] != ',')
		return (RETURN_FAILURE);
	(*i)++;
	*i += skip_spaces(&s[*i]);
	return (RETURN_SUCCESS);
}

static bool	parse_component(const char *s, int *i, int *v)
{
	if (s[*i] == '-')
		return (err_code(ERR_RGB_NEGATIVE));
	if (!read_uint_255(s, i, v))
		return (RETURN_FAILURE);
	*i += skip_spaces(&s[*i]);
	return (RETURN_SUCCESS);
}

bool	parse_rgb_triplet(const char *s, int *out)
{
	int	i;
	int	vals[3];
	int	vi;

	if (*out != -1)
		return (err_code(ERR_DUP_IDENTIFIER));
	i = skip_spaces(s);
	vi = 0;
	while (vi < 3)
	{
		if (!parse_component(s, &i, &vals[vi]))
			return (RETURN_FAILURE);
		if (++vi < 3 && !skip_comma_spaces(s, &i))
			return (RETURN_FAILURE);
	}
	i += skip_spaces(&s[i]);
	if (s[i] && s[i] != '\n')
		return (err_code(ERR_RGB_TRAILING));
	*out = (vals[0] << 16) | (vals[1] << 8) | vals[2];
	return (RETURN_SUCCESS);
}
