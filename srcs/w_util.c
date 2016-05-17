#include "wolf3d.h"

void		w_del_node(void *content, size_t content_size)
{
	ft_strdel((char**)&content);
	content_size = 0;
}

t_color			w_get_cardinal_color(t_app *app)
{
	t_color color;
	
	if (app->ray.side == 0 && app->ray.ray_dir_x < 0)
		color = w_get_color(0, 255, 0, 0);
	else if (app->ray.side == 0 && app->ray.ray_dir_x > 0)
		color = w_get_color(255, 0, 0, 0);
	else if (app->ray.side == 1 && app->ray.ray_dir_y < 0)
		color = w_get_color(0, 0, 255, 0);
	else if (app->ray.side == 1 && app->ray.ray_dir_y > 0)
		color = w_get_color(255, 255, 0, 0);
	else
		color = w_get_color(0, 255, 0, 0);
	return (color);
}

void			w_print_fps(t_app *app) 
{
	app->fps.old_time = app->fps.time;
	app->fps.time = clock();
	app->fps.frame_time = (app->fps.time - app->fps.old_time) / 1000.0; //frameTime is the time this frame has taken, in seconds
	if (app->fps.delay > 10000)
	{
		ft_strdel(&app->fps.str_fps);
		app->fps.str_fps = ft_itoa((int)(1.0 / app->fps.frame_time));
		app->fps.delay = 0;
	}
	app->fps.delay++;
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
