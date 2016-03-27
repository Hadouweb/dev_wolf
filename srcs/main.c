#include "wolf3d.h"

void		w_test(t_app *app)
{
	int		i;

	i = 0;

	while (i < SIZE_W)
	{
		w_set_obj(app->obj, i, 10, w_get_color(0, 200, 255, 0));
		i++;
	}
	w_draw(app);
}

int			main(void)
{
	t_app	app;

	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, SIZE_W, SIZE_H, "Wolf3D");
	app.obj = w_init_obj_info(app.mlx, SIZE_W, SIZE_H);

	w_test(&app);

	mlx_key_hook(app.win, w_event, &app);
	mlx_loop(app.mlx);
	return (0);
}