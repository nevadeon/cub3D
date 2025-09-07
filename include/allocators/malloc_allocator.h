/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_allocator.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:48:52 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:48:59 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_ALLOCATOR_H
# define MALLOC_ALLOCATOR_H

# include "allocators/allocator.h"

t_alloc	*new_malloc_allocator(int unused_param);
void	*malloc_alloc_fn(void *data, size_t size);
void	malloc_free_fn(void *data);

#endif
