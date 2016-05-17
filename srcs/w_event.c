#include "wolf3d.h"

int			w_event_arrow_key(int keycode, t_app *app)
{
	if (keycode == KEY_UP)
	{
		w_player_direction_up(app);
	}
	else if (keycode == KEY_RIGHT)
	{
		w_player_direction_right(app);
	}
	else if (keycode == KEY_LEFT)
	{
		w_player_direction_left(app);
	}
	else if (keycode == KEY_DOWN)
	{
		w_player_direction_down(app);
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
	if (app)
		;
	//w_event_arrow_key(keycode, app);
	return (1);
}