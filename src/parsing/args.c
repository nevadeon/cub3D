#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "cub3d.h"
#include "error.h"

static bool	has_cub_extension(const char *s)
{
	const char	*dot;

	dot = NULL;
	while (*s)
	{
		if (*s == '.')
			dot = s;
		s++;
	}
	if (!dot)
		return (false);
	return (dot[1] == 'c' && dot[2] == 'u' && dot[3] == 'b' \
		&& dot[4] == '\0');
}

bool	parse_args(int argc, char const *argv[])
{
	int	fd;

	if (argc != 2)
		return (error(ERR_INVALID_ARGUMENT));
	if (!has_cub_extension(argv[1]))
		return (error(ERR_FILE_EXTENSION));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error(ERR_OPEN_FAILED));
	close(fd);
	return (true);
}
