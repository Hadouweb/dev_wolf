#include "wolf3d.h"

void		w_del_node(void *content, size_t content_size)
{
	ft_strdel((char**)&content);
	content_size = 0;
}