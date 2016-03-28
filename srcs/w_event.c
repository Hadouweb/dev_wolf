#include "wolf3d.h"

int			w_event_arrow_key(int keycode, t_app *app)
{
	int		pos_x;
	int		pos_y;
	double	old_dir_x;
	double	old_plane_x;

	pos_x = (int)app->player.pos_x;
	pos_y = (int)app->player.pos_y;
	if (keycode == KEY_UP)
	{
		if (app->map.tab[(int)(pos_x + app->player.dir_x)][pos_y] == '0') 
			app->player.pos_x += app->player.dir_x * 0.05;
		if (app->map.tab[pos_x][(int)(pos_y + app->player.dir_y)] == '0') 
			app->player.pos_y += app->player.dir_y * 0.05;
		w_test(app);
	}
	else if (keycode == KEY_LEFT)
	{

	}
	else if (keycode == KEY_RIGHT)
	{
		w_test(app);
		old_dir_x = app->player.dir_x;
		app->player.dir_x = app->player.dir_x * cos(-3) - app->player.dir_y * sin(-3);
		app->player.dir_y = old_dir_x * sin(-3) + app->player.dir_y * cos(-3);
		old_plane_x = app->player.cam_plane_x;
		app->player.cam_plane_x = app->player.cam_plane_x - app->player.cam_plane_y;
		app->player.cam_plane_y = old_plane_x + app->player.cam_plane_y;
	}
	else if (keycode == KEY_DOWN)
	{
		if (app->map.tab[(int)(pos_x + app->player.dir_x)][pos_y] == '0') 
			app->player.pos_x -= app->player.dir_x * 0.05;
		if (app->map.tab[pos_x][(int)(pos_y + app->player.dir_y)] == '0') 
			app->player.pos_y -= app->player.dir_y * 0.05;
		w_test(app);
	}
	return (1);
}

int			w_event_repeat(int keycode, t_app *app)
{
	w_event_arrow_key(keycode, app);
	return (1);
}

int			w_event(int keycode, t_app *app)
{
	if (keycode == 53)
		exit(1);
	else
		printf("%d\n", keycode);
	w_event_arrow_key(keycode, app);
	return (1);
}