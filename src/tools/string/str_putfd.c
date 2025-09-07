/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_putfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:46:43 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/str.h"

size_t	str_putfd(const char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return (str_putfd("(null)", fd));
	len = str_len(s);
	write(fd, s, len);
	return (len);
}
