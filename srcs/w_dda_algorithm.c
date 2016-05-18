#include "wolf3d.h"

void		w_preparation_for_dda_algorithm(t_app *app)
{
	// Delta entre la premiere intersection et la prochaine en x
	app->ray.dela_dist_x = sqrt(1 + (app->ray.ray_dir_y * app->ray.ray_dir_y) /
		(app->ray.ray_dir_x * app->ray.ray_dir_x));
	// Delta entre la premiere intersection et la prochaine en y
	app->ray.dela_dist_y = sqrt(1 + (app->ray.ray_dir_x * app->ray.ray_dir_x) /
		(app->ray.ray_dir_y * app->ray.ray_dir_y));
	if (app->ray.ray_dir_x < 0) //Direction du rayon
	{
		app->ray.step_x = -1; // Incrementation pour le deplacement du rayon
		app->ray.side_dist_x = (app->ray.ray_pos_x - app->ray.map_x) * app->ray.dela_dist_x; //Distance du 'bloque'
	}
	else
	{
		app->ray.step_x = 1;
		app->ray.side_dist_x = (app->ray.map_x + 1.0 - app->ray.ray_pos_x) * app->ray.dela_dist_x;
	}
	if (app->ray.ray_dir_y < 0)
	{
		app->ray.step_y = -1;
		app->ray.side_dist_y = (app->ray.ray_pos_y - app->ray.map_y) * app->ray.dela_dist_y;
	}
	else
	{
		app->ray.step_y = 1;
		app->ray.side_dist_y = (app->ray.map_y + 1.0 - app->ray.ray_pos_y) * app->ray.dela_dist_y;
	}
}

void		w_dda_algorithm(t_app *app)
{
	int 	hit;

	hit = 0;
	while (hit == 0)
	{
		if (app->ray.side_dist_x < app->ray.side_dist_y) // Saute au prochain bloque en x
		{
			app->ray.side_dist_x += app->ray.dela_dist_x; // Incrementation de la distance
			app->ray.map_x += app->ray.step_x; // Incrementation de la position courante
			app->ray.side = 0;
		}
		else // Saute au prochain bloque en y
		{
			app->ray.side_dist_y += app->ray.dela_dist_y;
			app->ray.map_y += app->ray.step_y;
			app->ray.side = 1;
		}
		if (app->ray.map_x < app->map.x && app->ray.map_y < app->map.y)
		{
			if (app->map.tab[app->ray.map_x][app->ray.map_y] > 0) // Rayon touche un mur
				hit = 1;
		}
		else
			hit = 1;
	}
}