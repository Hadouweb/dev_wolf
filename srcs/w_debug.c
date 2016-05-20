/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_debug.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:52:28 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:52:29 by nle-bret         ###   ########.fr       */
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
	while (i <= app->map.y)
	{
		j = 0;
		while (j <= app->map.x)
		{	
			ft_putnbr(app->map.tab[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void		w_debug_player(t_app *app) 
{
	printf("______ PLAYER _______\n");
	printf("pos_x : %f\n", app->player.pos_x);
	printf("pos_y : %f\n", app->player.pos_y);
	printf("dir_x : %f\n", app->player.dir_x);
	printf("dir_y : %f\n", app->player.dir_y);
	printf("cam_plane_x : %f\n", app->player.cam_plane_x);
	printf("cam_plane_y : %f\n", app->player.cam_plane_y);
	printf("camera_x : %f\n", app->player.camera_x);
}

void		w_debug_ray(t_app *app) 
{
	printf("______ RAYON _______\n");
	printf("ray_pos_x : %f\n", app->ray.ray_pos_x);
	printf("ray_pos_y : %f\n", app->ray.ray_pos_y);
	printf("ray_dir_x : %f\n", app->ray.ray_dir_x);
	printf("ray_dir_y : %f\n", app->ray.ray_dir_y);
	printf("map_x : %d\n", app->ray.map_x);
	printf("map_y : %d\n", app->ray.map_y);
	printf("dela_dist_x : %f\n", app->ray.dela_dist_x);
	printf("dela_dist_y : %f\n", app->ray.dela_dist_y);
	printf("side_dist_x : %f\n", app->ray.side_dist_x);
	printf("side_dist_y : %f\n", app->ray.side_dist_y);
	printf("step_x : %d\n", app->ray.step_x);
	printf("step_y : %d\n", app->ray.step_y);
	printf("side : %d\n", app->ray.side);
}

void		w_print_lst_texture(void *data)
{
	t_texture	*texture;

	texture = (t_texture*)data;
	printf("width %d\n", texture->width);
	printf("height %d\n", texture->height);
	printf("x %d\n", texture->x);
	printf("y %d\n", texture->y);
	printf("num %d\n", texture->num);
}

