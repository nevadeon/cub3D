#include "cub3d.h"
#include "parser.h"
#include  "error.h"

/* returns true on success; on failure, leaves *i at first invalid char */
static bool	read_uint_255(const char *s, int *i, int *v)
{
	int	acc;

	acc = 0;
	if (s[*i] < '0' || s[*i] > '9')
		return (false);
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		acc = acc * 10 + (s[*i] - '0');
		if (acc > 255)
			return (error(ERR_RGB_OVERFLOW));
		(*i)++;
	}
	*v = acc;
	return (true);
}

static bool	skip_comma_spaces(const char *s, int *i)
{
	if (s[*i] != ',')
		return (false);
	(*i)++;
	*i += skip_spaces(&s[*i]);
	return (true);
}

static bool	parse_component(const char *s, int *i, int *v)
{
	if (s[*i] == '-')
		return (false);
	if (!read_uint_255(s, i, v))
		return (false);
	*i += skip_spaces(&s[*i]);
	return (true);
}

bool	parse_rgb_triplet(const char *s, int *out)
{
	int i;
	int vals[3];
	int vi;

	if (*out != -1)
		return (error(ERR_DUP_IDENTIFIER));
	i = skip_spaces(s);
	vi = 0;
	while (vi < 3)
	{
		if (!parse_component(s, &i, &vals[vi]))
			return (false);
		if (++vi < 3 && !skip_comma_spaces(s, &i))
			return (false);
	}
	i += skip_spaces(&s[i]);
	if (s[i] && s[i] != '\n')
		return (error(ERR_RGB_TRAILING));
	*out = (vals[0] << 16) | (vals[1] << 8) | vals[2];
	return (true);
}
