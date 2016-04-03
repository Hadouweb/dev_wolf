#include "wolf3d.h"

void		w_init_player(t_app *app)
{
	app->player.pos_x = 5;
	app->player.pos_y = 5;
	app->player.dir_x = -1;
	app->player.dir_y = 0;
	app->player.cam_plane_x = 0;
	app->player.cam_plane_y = 0.66;
}

void		w_calculate_ray(t_app *app, int x)
{
	app->player.camera_x = 2 * x / (double)SIZE_W - 1;
	app->ray.ray_pos_x = app->player.pos_x;
	app->ray.ray_pos_y = app->player.pos_y;
	app->ray.ray_dir_x = app->player.dir_x + app->player.cam_plane_x * app->player.camera_x;
	app->ray.ray_dir_y = app->player.dir_y + app->player.cam_plane_y * app->player.camera_x;
	app->ray.map_x = (int)app->ray.ray_pos_x;
	app->ray.map_y = (int)app->ray.ray_pos_y;
	app->ray.dela_dist_x = sqrt(1 + (app->ray.ray_dir_y * app->ray.ray_dir_y) /
		(app->ray.ray_dir_x * app->ray.ray_dir_x));
	app->ray.dela_dist_y = sqrt(1 + (app->ray.ray_dir_x * app->ray.ray_dir_x) /
		(app->ray.ray_dir_y * app->ray.ray_dir_y));

	if (app->ray.ray_dir_x < 0)
	{
		app->ray.step_x = -1;
		app->ray.side_dist_x = (app->ray.ray_pos_x - app->ray.map_x) * app->ray.dela_dist_x;
	}
	else
	{
		app->ray.step_x = 1;
		app->ray.side_dist_x = (app->ray.map_x + 1.0 - app->ray.ray_pos_x) * app->ray.dela_dist_x;
	}
	if (app->ray.ray_dir_y < 0)
	{
		app->ray.step_y = -1;
		app->ray.side_dist_y = (app->ray.ray_pos_y - app->ray.map_y) * app->ray.dela_dist_y;
	}
	else
	{
		app->ray.step_y = 1;
		app->ray.side_dist_y = (app->ray.map_y + 1.0 - app->ray.ray_pos_y) * app->ray.dela_dist_y;
	}
	app->ray.side = -1;
}

void		w_dda_algo(t_app *app)
{
	int 	hit;

	hit = 0;
	while (hit == 0)
	{
		if (app->ray.side_dist_x < app->ray.side_dist_y)
		{
			app->ray.side_dist_x += app->ray.dela_dist_x;
			app->ray.map_x += app->ray.step_x;
			app->ray.side = 0;
		}
		else
		{
			app->ray.side_dist_y += app->ray.dela_dist_y;
			app->ray.map_y += app->ray.step_y;
			app->ray.side = 1;
		}
		if (app->map.tab[app->ray.map_x][app->ray.map_y] > 0)
			hit = 1;
	}
}

void		w_calculate_current_vline(t_app *app, int x)
{
	double	perp_wall_dist;
	int		line_height;
	int 	draw_start;
	int		draw_end;
	t_color	color;

	if (app->ray.side == 0) 
		perp_wall_dist = (app->ray.map_x - app->ray.ray_pos_x +
			(1 - app->ray.step_x) / 2) / app->ray.ray_dir_x;
	else			 
		perp_wall_dist = (app->ray.map_y - app->ray.ray_pos_y +
			(1 - app->ray.step_y) / 2) / app->ray.ray_dir_y;

	line_height = (int)(SIZE_H / perp_wall_dist);

	draw_start = -line_height / 2 + SIZE_H / 2;
	if(draw_start < 0)
		draw_start = 0;

	draw_end = line_height / 2 + SIZE_H / 2;
	if(draw_end >= SIZE_H)
		draw_end = SIZE_H - 1;

	color = w_get_color(255, 255, 0, 0);
	if (app->ray.side == 1)
		color = w_get_color(125, 125, 0, 0);
	app->current_vline = w_get_vline(x, draw_start, draw_end, color);
}

void		w_set_pixel(t_obj *obj, int x, int y, t_color color)
{
	if (y < 0 || y > SIZE_H - 1 || x < 0 || x > SIZE_W - 1)
		return ;
	obj->data[y * obj->sizeline + x * obj->bpp / 8] = color.r;
	obj->data[y * obj->sizeline + x * obj->bpp / 8 + 1] = color.g;
	obj->data[y * obj->sizeline + x * obj->bpp / 8 + 2] = color.b;
	obj->data[y * obj->sizeline + x * obj->bpp / 8 + 3] = color.a;
}

void		w_draw_vline(t_app *app, int x)
{
	int		y;
	int		max;
	t_color	color;

	y = app->current_vline.y_start;
	max = app->current_vline.y_end;
	color = app->current_vline.color;
	while (y < max)
	{
		w_set_pixel(app->obj, x, y, color);
		y++;
	}
}

int			w_test(t_app *app)
{
	int		x;

	x = 0;
	while (x < SIZE_W)
	{
		w_calculate_ray(app, x);
		w_dda_algo(app);
		w_calculate_current_vline(app, x);
		w_draw_vline(app, x);
		x++;
	}
	w_draw(app);
	return (1);
}

int			main(int ac, char **av)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, SIZE_W, SIZE_H, "Wolf3D");
	app.obj = w_init_obj_info(app.mlx, SIZE_W, SIZE_H);

	if (ac > 1)
		w_set_map(&app, av[1]);
	w_init_player(&app);
	//app.current_vline = w_get_vline(50, 0, SIZE_H, w_get_color(255, 255, 0, 0));
	//w_draw_vline(&app);
	//w_draw(&app);
	mlx_hook(app.win, 2, 3, w_event_repeat, &app);
	mlx_key_hook(app.win, w_event, &app);
	mlx_loop_hook(app.mlx, w_test, &app);
	mlx_loop(app.mlx);
	return (0);
}
