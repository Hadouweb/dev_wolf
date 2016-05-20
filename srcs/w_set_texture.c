#include "wolf3d.h"

void		w_set_texture(t_app *app, char *file_name, char num)
{
	t_texture	texture;
	t_obj		*obj;
	int			height;
	int			width;

	printf("%s\n\n", file_name);
	obj = NULL;
	ft_bzero(&texture, sizeof(t_texture));
	if ((obj = (t_obj *)ft_memalloc(sizeof(t_obj))) == NULL)
		ft_putstr_fd("Erreur d'allocation de t_obj\n", 2);

	obj->img = mlx_xpm_file_to_image(app->mlx, file_name,
		&width, &height);

	if (obj->img == NULL)
		return;

	obj->data = mlx_get_data_addr(obj->img,
		&obj->bpp,
		&obj->sizeline,
		&obj->endian);

	texture.num = num;
	texture.x = 0;
	texture.y = 0;
	texture.width = width;
	texture.height = height;
	texture.obj = obj;

	ft_lstpush_front(&app->lst_texture, &texture, sizeof(t_texture));

	t_texture *test;

	test = (t_texture*)app->lst_texture->content;
}