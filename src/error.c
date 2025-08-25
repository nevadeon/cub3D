#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "error.h"

/* simple static stack to record error context top-down */
#define MAX_ERROR_COUNT 16

static t_err		g_error_stack[MAX_ERROR_COUNT];
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
	[ERR_UNKNOWN] = "Unknown error",
};

static const size_t	err_strings_size = sizeof(g_error_strings) / sizeof(char *);

bool	error_throw(t_err code)
{
	assert(g_error_count < MAX_ERROR_COUNT);
	g_error_stack[g_error_count++] = code;
	return (false);
}

void	error_print(void)
{
	int		i;
	t_err	code;

	if (g_error_count == 0)
		return ;
	dprintf(STDERR_FILENO, "Error: ");
	i = g_error_count - 1;
	while (i >= 0)
	{
		code = g_error_stack[i];
		assert(code > 0 && code < err_strings_size);
		dprintf(STDERR_FILENO, "%s", g_error_strings[code]);
		if (i > 0)
			dprintf(STDERR_FILENO, ": ");
		i--;
	}
	dprintf(STDERR_FILENO, "\n");
	g_error_count = 0;
}

void	error_clear(void)
{
	g_error_count = 0;
}
