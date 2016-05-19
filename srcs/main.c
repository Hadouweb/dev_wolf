#include "wolf3d.h"

void		w_add_texture_xpm(t_app *app)
{
	t_texture	*texture;

	if ((texture = (t_texture *)ft_memalloc(sizeof(t_texture))) == NULL)
		ft_putstr_fd("Erreur d'allocation de t_texture\n", 2);
	if ((texture->obj = (t_obj *)ft_memalloc(sizeof(t_obj))) == NULL)
		ft_putstr_fd("Erreur d'allocation de t_obj\n", 2);
	texture->obj->img = mlx_xpm_file_to_image(app->mlx, "./b1.xpm",
		&texture->width, &texture->height);

	texture->obj->data = mlx_get_data_addr(texture->obj->img,
		&texture->obj->bpp,
		&texture->obj->sizeline,
		&texture->obj->endian);
	texture->num = '1';
	ft_lstpush_back(&app->lst_texture, texture, sizeof(t_texture));
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
	w_add_texture_xpm(&app);
	mlx_hook(app.win, 2, 3, w_event_repeat, &app);
	mlx_key_hook(app.win, w_event, &app);
	mlx_loop_hook(app.mlx, w_draw_view, &app);
	mlx_loop(app.mlx);
	return (0);
}
