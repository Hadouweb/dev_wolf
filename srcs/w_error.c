#include "wolf3d.h"

void		w_print_error_exit(char *str, char *error)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(error, 2);
	exit(1);
}