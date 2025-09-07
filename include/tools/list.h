/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:48:52 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:49:03 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "allocators/allocator.h"

typedef void			(*t_print_fn)(void *);

typedef enum e_lifetime	t_lifetime;

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}	t_list;

t_list	*lst_new(t_alloc *alloc, void *content);
void	lst_add_front(t_list **list, t_list *new_node);
void	lst_add_back(t_list **list, t_list *new_node);
void	**lst_to_array(t_alloc *alloc, t_list *list);
int		lst_len(t_list *list);
void	lst_print(t_list *list, t_print_fn print_function);

#endif
