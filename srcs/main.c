#include "wolf3d.h"

void		w_test_xpm(t_app *app)
{
	int 	height;
	int 	width;

	t_obj	*obj;

	if ((obj = (t_obj *)ft_memalloc(sizeof(t_obj))) == NULL)
		ft_putstr_fd("Erreur d'allocation de t_obj\n", 2);
	obj->img = mlx_xpm_file_to_image(app->mlx, "./arena.xpm", &width, &height);

	obj->data = mlx_get_data_addr(obj->img,
		&obj->bpp,
		&obj->sizeline,
		&obj->endian);
	app->ptr_xpm = obj;

	printf("sizeline: %d bpp: %d\n", obj->sizeline, obj->bpp);
	for (int x= 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			int index = y * obj->sizeline + x * obj->bpp / 16;
			printf("%d ", obj->data[index]);
		}
		printf("\n");
	}
	//ft_bzero(obj->data, width * height * 4);

	//printf("Height : %d, Width %d\n", height, width);
		//mlx_clear_window(app->mlx, app->win);
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
	else
		w_set_map(&app, "map/default");
	w_set_view(&app);
	w_test_xpm(&app);
	mlx_hook(app.win, 2, 3, w_event_repeat, &app);
	mlx_key_hook(app.win, w_event, &app);
	mlx_loop_hook(app.mlx, w_draw_view, &app);
	mlx_loop(app.mlx);
	return (0);
}
