#include "wolf3d.h"

int			w_event_arrow_key(int keycode, t_app *app)
{
	double	pos_x;
	double	pos_y;
	double	old_dir_x;
	double	old_plane_x;
	double	move_speed;

	pos_x = app->player.pos_x;
	pos_y = app->player.pos_y;
	move_speed = 0.2;
	if (keycode == KEY_UP)
	{
		if (app->map.tab[(int)(pos_x + app->player.dir_x * move_speed)][(int)pos_y] == 0) 
			app->player.pos_x += app->player.dir_x * move_speed;
		if (app->map.tab[(int)pos_x][(int)(pos_y + app->player.dir_y * move_speed)] == 0) 
			app->player.pos_y += app->player.dir_y * move_speed;
	}
	else if (keycode == KEY_RIGHT)
	{
		old_dir_x = app->player.dir_x;
		app->player.dir_x = app->player.dir_x * cos(-move_speed) - app->player.dir_y * sin(-move_speed);
		app->player.dir_y = old_dir_x * sin(-move_speed) + app->player.dir_y * cos(-move_speed);
		old_plane_x = app->player.cam_plane_x;
		app->player.cam_plane_x = app->player.cam_plane_x * cos(move_speed) - app->player.cam_plane_y * sin(-move_speed);
		app->player.cam_plane_y = old_plane_x * sin(-move_speed) + app->player.cam_plane_y * cos(-move_speed);
	}
	else if (keycode == KEY_LEFT)
	{
		old_dir_x = app->player.dir_x;
		app->player.dir_x = app->player.dir_x * cos(move_speed) - app->player.dir_y * sin(move_speed);
		app->player.dir_y = old_dir_x * sin(move_speed) + app->player.dir_y * cos(move_speed);
		old_plane_x = app->player.cam_plane_x;
		app->player.cam_plane_x = app->player.cam_plane_x * cos(move_speed) - app->player.cam_plane_y * sin(move_speed);
		app->player.cam_plane_y = old_plane_x * sin(move_speed) + app->player.cam_plane_y * cos(move_speed);
	}
	else if (keycode == KEY_DOWN)
	{
		if (app->map.tab[(int)(pos_x - app->player.dir_x * move_speed)][(int)pos_y] == 0) 
			app->player.pos_x -= app->player.dir_x * move_speed;
		if (app->map.tab[(int)pos_x][(int)(pos_y - app->player.dir_y * move_speed)] == 0) 
			app->player.pos_y -= app->player.dir_y * move_speed;
	}
	return (1);
}

int			w_event_repeat(int keycode, t_app *app)
{
	if (app || keycode)
		;
	w_event_arrow_key(keycode, app);
	return (1);
}

int			w_event(int keycode, t_app *app)
{
	if (keycode == 53)
		exit(1);
	else
		printf("%d\n", keycode);
	if (app)
		;
	//w_event_arrow_key(keycode, app);
	return (1);
}