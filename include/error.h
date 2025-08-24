#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

#define MAX_ERROR_COUNT 16
#define STDERR STDERR_FILENO

/* Error codes for composing user-facing messages */
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
	ERR_UNKNOWN,
}t_err;

/* Push an error code on the stack and return false for comma-return style */
bool	error(t_err code);

/* Print the composed error message (highest-level first) and clear stack */
void	error_print(void);

/* Clear the error stack without printing */
void	error_clear(void);

#endif
