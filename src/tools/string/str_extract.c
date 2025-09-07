/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:46:36 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocators/allocator.h"
#include "tools/str.h"

char	*str_extract(t_alloc *alloc, char *s, size_t start, size_t len)
{
	char	*ret;

	ret = mem_alloc(alloc, len + 1);
	if (!ret)
		return (NULL);
	ret = str_memcpy(ret, s + start, len);
	ret[len] = '\0';
	return (ret);
}
