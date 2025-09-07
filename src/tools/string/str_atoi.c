/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:45:46 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:48:03 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/str.h"
#include "tools/char.h"

int	str_atoi(const char *s)
{
	int		result;
	int		index;
	bool	positive;

	if (!s)
		return (0);
	if (str_equals(s, "-2147483648"))
		return (-2147483648);
	positive = (s[0] != '-');
	result = 0;
	index = (s[0] == '-' || s[0] == '+');
	while (s[index] && char_isnum(s[index]))
	{
		result *= 10;
		result += s[index] - '0';
		index++;
	}
	if (positive)
		return (result);
	return (-result);
}
