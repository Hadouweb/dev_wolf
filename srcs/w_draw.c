#include "wolf3d.h"

void		w_draw(t_app *app)
{
	mlx_clear_window(app->mlx, app->win);
	mlx_put_image_to_window(app->mlx, app->win, app->obj->img, 0, 0);
	mlx_string_put(app->mlx, app->win, 20, 10, 0xFFFFFF, "FPS : ");
	mlx_string_put(app->mlx, app->win, 80, 10, 0xFFFFFF, app->fps.str_fps);
	ft_bzero(app->obj->data, SIZE_W * SIZE_H * 4);
}

void		w_set_pixel(t_obj *obj, int x, int y, t_color color)
{
	int 	index;

	if (y < 0 || y > SIZE_H - 1 || x < 0 || x > SIZE_W - 1)
		return ;
	index = y * obj->sizeline + x * obj->bpp / 8;
	obj->data[index] = color.r;
	obj->data[index + 1] = color.g;
	obj->data[index + 2] = color.b;
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