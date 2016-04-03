#include "wolf3d.h"

void		w_draw(t_app *app)
{
	mlx_clear_window(app->mlx, app->win);
	mlx_put_image_to_window(app->mlx, app->win, app->obj->img, 0, 0);
	ft_bzero(app->obj->data, SIZE_W * SIZE_H * 4);
}

t_color		w_get_color(unsigned char r, unsigned char g,
	unsigned char b, unsigned char a)
{
	t_color		color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

t_obj		*w_init_obj_info(void *mlx, int width, int height)
{
	t_obj	*obj;

	if ((obj = (t_obj *)ft_memalloc(sizeof(t_obj))) == NULL)
		ft_putstr_fd("Erreur d'allocation de t_obj\n", 2);
	obj->img = mlx_new_image(mlx, width, height);
	obj->data = mlx_get_data_addr(obj->img,
		&obj->bpp,
		&obj->sizeline,
		&obj->endian);
	ft_bzero(obj->data, width * height * 4);
	return (obj);
}

t_vline		w_get_vline(int x, int y_start, int y_end, t_color color)
{
	t_vline		vline;

	vline.x = x;
	vline.y_start = y_start;
	vline.y_end = y_end;
	vline.color = color;
	return (vline);
}