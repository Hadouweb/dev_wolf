#include "wolf3d.h"

void		w_player_direction_up(t_app *app)
{
	double	pos_x;
	double	pos_y;

	pos_x = app->player.pos_x;
	pos_y = app->player.pos_y;
	if (app->map.tab[(int)(pos_x + app->player.dir_x * MOVE_SPEED)][(int)pos_y] == 0) 
		app->player.pos_x += app->player.dir_x * MOVE_SPEED;
	if (app->map.tab[(int)pos_x][(int)(pos_y + app->player.dir_y * MOVE_SPEED)] == 0) 
		app->player.pos_y += app->player.dir_y * MOVE_SPEED;
}

void		w_player_direction_right(t_app *app)
{
	double	old_dir_x;
	double	old_plane_x;
	double	pos_x;
	double	pos_y;

	pos_x = app->player.pos_x;
	pos_y = app->player.pos_y;
	old_dir_x = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cos(-MOVE_SPEED) - app->player.dir_y * sin(-MOVE_SPEED);
	app->player.dir_y = old_dir_x * sin(-MOVE_SPEED) + app->player.dir_y * cos(-MOVE_SPEED);
	old_plane_x = app->player.cam_plane_x;
	app->player.cam_plane_x = app->player.cam_plane_x * cos(MOVE_SPEED) - app->player.cam_plane_y * sin(-MOVE_SPEED);
	app->player.cam_plane_y = old_plane_x * sin(-MOVE_SPEED) + app->player.cam_plane_y * cos(-MOVE_SPEED);
}

void		w_player_direction_left(t_app *app)
{
	double	old_dir_x;
	double	old_plane_x;
	double	pos_x;
	double	pos_y;

	pos_x = app->player.pos_x;
	pos_y = app->player.pos_y;
	old_dir_x = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cos(MOVE_SPEED) - app->player.dir_y * sin(MOVE_SPEED);
	app->player.dir_y = old_dir_x * sin(MOVE_SPEED) + app->player.dir_y * cos(MOVE_SPEED);
	old_plane_x = app->player.cam_plane_x;
	app->player.cam_plane_x = app->player.cam_plane_x * cos(MOVE_SPEED) - app->player.cam_plane_y * sin(MOVE_SPEED);
	app->player.cam_plane_y = old_plane_x * sin(MOVE_SPEED) + app->player.cam_plane_y * cos(MOVE_SPEED);	
}

void		w_player_direction_down(t_app *app)
{
	double	pos_x;
	double	pos_y;

	pos_x = app->player.pos_x;
	pos_y = app->player.pos_y;
	if (app->map.tab[(int)(pos_x - app->player.dir_x * MOVE_SPEED)][(int)pos_y] == 0) 
		app->player.pos_x -= app->player.dir_x * MOVE_SPEED;
	if (app->map.tab[(int)pos_x][(int)(pos_y - app->player.dir_y * MOVE_SPEED)] == 0) 
		app->player.pos_y -= app->player.dir_y * MOVE_SPEED;	
}