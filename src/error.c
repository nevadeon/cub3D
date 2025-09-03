#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include "error.h"

static const char	*g_error_stack[ERROR_STACK_MAX];
static int			g_error_count = 0;

static const char	*g_error_strings[] = {
	[ERR_NONE] = "",
	[ERR_PARSING] = "In map file",
	[ERR_INVALID_ARGUMENT] = "Usage ./cub3D map_file.cub",
	[ERR_FILE_EXTENSION] = "Incorrect map file extension",
	[ERR_OPEN_FAILED] = "Cannot open file",
	[ERR_MAP_NOT_CLOSED] = "Map is not closed by walls",
	[ERR_MULTIPLE_PLAYERS] = "Multiple player positions",
	[ERR_INVALID_CHAR] = "Found invalid character",
	[ERR_NO_PLAYER] = "Missing player start",
	[ERR_DUP_IDENTIFIER] = "Duplicate identifier",
	[ERR_INV_IDENTIFIER] = "Missing or invalid identifier",
	[ERR_MISSING_MAP] = "Missing map",
	[ERR_RGB_OVERFLOW] = "over 255 RGB value",
	[ERR_RGB_NEGATIVE] = "Negative RGB value",
	[ERR_RGB_TRAILING] = "Trailing characters after RGB value",
	[ERR_MLX] = "Generic mlx error",
	[ERR_UNKNOWN] = "Unknown error",
};

void	err_flush(void)
{
	int		i;

	if (g_error_count == 0)
		return ;
	dprintf(STDERR_FILENO, "Error: ");
	i = g_error_count - 1;
	while (i >= 0)
	{
		dprintf(STDERR_FILENO, "%s", g_error_stack[i]);
		if (i > 0)
			dprintf(STDERR_FILENO, ": ");
		i--;
	}
	dprintf(STDERR_FILENO, "\n");
	g_error_count = 0;
}

bool	err_code(t_err code)
{
	assert(g_error_count < ERROR_STACK_MAX);
	assert(code > 0 && code < ERR_UNKNOWN);
	g_error_stack[g_error_count++] = g_error_strings[code];
	return (false);
}

bool	err_str(const char *str)
{
	assert(g_error_count < ERROR_STACK_MAX);
	g_error_stack[g_error_count++] = str;
	return (false);
}

bool	err_errno(void)
{
	assert(g_error_count < ERROR_STACK_MAX);
	g_error_stack[g_error_count++] = strerror(errno);
	return (false);
}
