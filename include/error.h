#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

#define MAX_ERROR_COUNT 16

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

bool	error_cub3d(t_err code);
void	error_print(void);
void	error_clear(void);

#endif
