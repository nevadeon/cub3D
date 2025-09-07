/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:46:21 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/list.h"

void	**lst_to_array(t_alloc *alloc, t_list *list)
{
	void	**tab;
	int		i;

	if (!list)
		return (NULL);
	tab = mem_alloc(alloc, sizeof(char *) * (lst_len(list) + 1));
	i = 0;
	while (list)
	{
		tab[i++] = list->content;
		list = list->next;
	}
	tab[i] = NULL;
	return (tab);
}
