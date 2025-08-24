#include "cub3d.h"
#include "error.h"

int	main(int argc, char const *argv[])
{
	t_alloc	*allocator;
	t_cub	cfg;

	allocator = new_mgc_allocator(0);
	if (!allocator)
		return (1);
	if (!parse_args(argc, argv))
		return (error_print(), free_allocator(&allocator), 1);
	if (!parse_cub_file(allocator, argv[1], &cfg))
		return (error_print(), free_allocator(&allocator), 1);
	(void)cfg;
	free_allocator(&allocator);
	return (0);
}
