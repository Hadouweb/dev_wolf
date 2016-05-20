/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:52:17 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:52:19 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_debug_map(t_app *app)
{
	int		i;
	int		j;

	i = 0;
	ft_putstr("Largeur de la carte : ");
	ft_putnbr(app->map.x);
	ft_putchar('\n');
	ft_putstr("Hauteur de la carte : ");
	ft_putnbr(app->map.y);
	ft_putchar('\n');
	ft_putstr("Carte : \n");
	while (i < app->map.y)
	{
		j = 0;
		while (j < app->map.x)
		{	
			ft_putnbr(app->map.tab[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int		main(int ac, char **av)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	app.speed = MOVE_SPEED;
	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, SIZE_W, SIZE_H, "Wolf3D");
	app.obj = w_init_obj_info(app.mlx, SIZE_W, SIZE_H);
	if (ac > 1)
		w_read_map(&app, av[1]);
	else
		w_read_map(&app, "map/default");
	//w_debug_map(&app);
	w_set_view(&app);
	mlx_hook(app.win, 2, 3, w_event_repeat, &app);
	mlx_key_hook(app.win, w_event, &app);
	mlx_loop_hook(app.mlx, w_draw_view, &app);
	mlx_loop(app.mlx);
	return (0);
}
