#include "wolf3d.h"

int			w_event_arrow_key(int keycode, t_app *app)
{
	int		pos_x;
	int		pos_y;
	double	old_dir_x;
	double	old_plane_x;
	double	rotate;
	double	move_speed;

	pos_x = (int)app->player.pos_x;
	pos_y = (int)app->player.pos_y;
	move_speed = 0.05;
	if (keycode == KEY_UP)
	{
		if (app->map.tab[(int)(pos_x + app->player.dir_x)][pos_y] == 0) 
			app->player.pos_x += app->player.dir_x * 0.05;
		if (app->map.tab[pos_x][(int)(pos_y + app->player.dir_y)] == 0) 
			app->player.pos_y += app->player.dir_y * 0.05;
		/*if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) 
			posX += dirX * moveSpeed;
      	if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) 
      		posY += dirY * moveSpeed;*/
		//w_test(app);
	}
	else if (keycode == KEY_LEFT)
	{
		rotate = 0.1;
		old_dir_x = app->player.dir_x;
		app->player.dir_x = app->player.dir_x * cos(rotate) - app->player.dir_y * sin(rotate);
		app->player.dir_y = old_dir_x * sin(rotate) + app->player.dir_y * cos(rotate);
		old_plane_x = app->player.cam_plane_x;
		app->player.cam_plane_x = app->player.cam_plane_x * cos(rotate) - app->player.cam_plane_y * sin(rotate);
		app->player.cam_plane_y = old_plane_x * sin(rotate) + app->player.cam_plane_y * cos(rotate);
		//w_test(app);
	}
	else if (keycode == KEY_RIGHT)
	{
		rotate = -0.1;
		old_dir_x = app->player.dir_x;
		app->player.dir_x = app->player.dir_x * cos(rotate) - app->player.dir_y * sin(rotate);
		app->player.dir_y = old_dir_x * sin(rotate) + app->player.dir_y * cos(rotate);
		old_plane_x = app->player.cam_plane_x;
		app->player.cam_plane_x = app->player.cam_plane_x * cos(rotate) - app->player.cam_plane_y * sin(rotate);
		app->player.cam_plane_y = old_plane_x * sin(rotate) + app->player.cam_plane_y * cos(rotate);
		//w_test(app);
	}
	else if (keycode == KEY_DOWN)
	{
		if (app->map.tab[(int)(pos_x + app->player.dir_x)][pos_y] == '0') 
			app->player.pos_x -= app->player.dir_x * 0.05;
		if (app->map.tab[pos_x][(int)(pos_y + app->player.dir_y)] == '0') 
			app->player.pos_y -= app->player.dir_y * 0.05;
		//w_test(app);
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