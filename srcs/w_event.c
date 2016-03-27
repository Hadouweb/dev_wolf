#include "wolf3d.h"

int			w_event(int keycode, t_app *app)
{
	if (keycode == 53)
		exit(1);
	else
		printf("%d\n", keycode);
	if (app)
		;
	return (1);
}