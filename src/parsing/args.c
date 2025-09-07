/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:45:51 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "cub3D.h"

static bool	has_cub_extension(const char *s)
{
	const char	*dot;

	dot = NULL;
	while (*s)
	{
		if (*s == '.')
			dot = s;
		s++;
	}
	if (!dot)
		return (false);
	return (dot[1] == 'c' && dot[2] == 'u' && dot[3] == 'b' \
		&& dot[4] == '\0');
}

bool	parse_args(int argc, char const *argv[])
{
	int	fd;

	if (argc != 2)
		return (err_code(ERR_INVALID_ARGUMENT));
	if (!has_cub_extension(argv[1]))
		return (err_code(ERR_FILE_EXTENSION));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (err_errno(), err_code(ERR_OPEN_FAILED));
	close(fd);
	return (RETURN_SUCCESS);
}
