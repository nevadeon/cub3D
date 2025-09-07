/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:48:52 by nevadeon          #+#    #+#             */
/*   Updated: 2025/09/07 17:52:04 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

# define ERROR_STACK_MAX	8

typedef enum e_err
{
	ERR_NONE = 0,
	ERR_PARSING,
	ERR_FILE_EXTENSION,
	ERR_OPEN_FAILED,
	ERR_INVALID_ARGUMENT,
	ERR_MAP_NOT_CLOSED,
	ERR_MULTIPLE_PLAYERS,
	ERR_INVALID_CHAR,
	ERR_NO_PLAYER,
	ERR_DUP_IDENTIFIER,
	ERR_INV_IDENTIFIER,
	ERR_MISSING_MAP,
	ERR_RGB_OVERFLOW,
	ERR_RGB_TRAILING,
	ERR_RGB_NEGATIVE,
	ERR_MLX,
	ERR_UNKNOWN,
}	t_err;

void	err_flush(void);
bool	err_code(t_err code);
bool	err_str(const char *str);
bool	err_errno(void);

#endif
