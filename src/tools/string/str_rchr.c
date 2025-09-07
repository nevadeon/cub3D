/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_rchr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:46:44 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/str.h"

char	*str_rchr(const char *s, int c)
{
	int	index;

	index = str_len(s);
	while (index > 0 && s[index] != (unsigned char) c)
		index--;
	if (s[index] == (unsigned char) c)
		return ((char *)(s + index));
	return ((char *)s);
}
