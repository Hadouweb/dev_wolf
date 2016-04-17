#include "wolf3d.h"

void		w_init_player(t_app *app)
{
	app->player.pos_x = 5; //Position du joueur en x
	app->player.pos_y = 5; //Position du joueur en y
	app->player.dir_x = -1; //Direction du joueur en x
	app->player.dir_y = 0; //Direction du joueur en y
	app->player.cam_plane_x = 0; //Plan de la camera en x
	app->player.cam_plane_y = 0.66; //Plan de la camera en y

	app->fps.time = 0; //time of current frame
  	app->fps.old_time = 0; //time of previous frame
  	app->fps.delay = 0;
  	app->fps.str_fps = ft_strdup("0");
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

void		w_calculate_ray(t_app *app, int x)
{
	app->player.camera_x = 2 * x / (double)SIZE_W - 1; //Position de la camera en x
	app->ray.ray_pos_x = app->player.pos_x; //Position de depart du rayon en x
	app->ray.ray_pos_y = app->player.pos_y; //Position de depart du rayon en y
	app->ray.ray_dir_x = app->player.dir_x + app->player.cam_plane_x * app->player.camera_x; //Direction du rayon en x
	app->ray.ray_dir_y = app->player.dir_y + app->player.cam_plane_y * app->player.camera_x; //Direction du rayon en y
	app->ray.map_x = (int)app->ray.ray_pos_x; //Position acutel du joueur/cam sur la grille en x
	app->ray.map_y = (int)app->ray.ray_pos_y; //Position acutel du joueur/cam sur la grille en y
	app->ray.dela_dist_x = sqrt(1 + (app->ray.ray_dir_y * app->ray.ray_dir_y) /
		(app->ray.ray_dir_x * app->ray.ray_dir_x)); // Delta entre la position actuel x et le prochain x
	app->ray.dela_dist_y = sqrt(1 + (app->ray.ray_dir_x * app->ray.ray_dir_x) /
		(app->ray.ray_dir_y * app->ray.ray_dir_y)); // Delta entre la position actuel y et le prochain y
}

void		w_calculate_step(t_app *app)
{
	if (app->ray.ray_dir_x < 0) //Direction du rayon
	{
		app->ray.step_x = -1; // Incrementation pour le deplacement du rayon
		app->ray.side_dist_x = (app->ray.ray_pos_x - app->ray.map_x) * app->ray.dela_dist_x; //Distane du 'bloque'
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

void		w_dda_algo(t_app *app)
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

void		w_calculate_current_vline(t_app *app, int x)
{
	double	perp_wall_dist;
	int		line_height;
	int 	draw_start;
	int		draw_end;
	t_color	color;

	if (app->ray.side == 0) // Caclul de la distance de la camera pour corriger le fisheye effect
		perp_wall_dist = (app->ray.map_x - app->ray.ray_pos_x +
			(1 - app->ray.step_x) / 2) / app->ray.ray_dir_x;
	else			 
		perp_wall_dist = (app->ray.map_y - app->ray.ray_pos_y +
			(1 - app->ray.step_y) / 2) / app->ray.ray_dir_y;

	line_height = (int)(SIZE_H / perp_wall_dist); // La hauteur du mur a tracer

	draw_start = -line_height / 2 + SIZE_H / 2; // Le bas du mur
	if(draw_start < 0)
		draw_start = 0;

	draw_end = line_height / 2 + SIZE_H / 2; // Le haut du mur
	if(draw_end >= SIZE_H)
		draw_end = SIZE_H - 1;

	if (app->ray.side == 0 && app->ray.ray_dir_x < 0)
		color = w_get_color(0, 255, 0, 0);
	else if (app->ray.side == 0 && app->ray.ray_dir_x > 0)
		color = w_get_color(255, 0, 0, 0);
	else if (app->ray.side == 1 && app->ray.ray_dir_y < 0)
		color = w_get_color(0, 0, 255, 0);
	else if (app->ray.side == 1 && app->ray.ray_dir_y > 0)
		color = w_get_color(255, 255, 0, 0);
	else
		color = w_get_color(0, 255, 0, 0);
	app->current_vline = w_get_vline(x, draw_start, draw_end, color);
}

void		w_print_fps(t_app *app) 
{
	app->fps.old_time = app->fps.time;
	app->fps.time = clock();
	app->fps.frame_time = (app->fps.time - app->fps.old_time) / 1000.0; //frameTime is the time this frame has taken, in seconds
	if (app->fps.delay > 10000)
	{
		ft_strdel(&app->fps.str_fps);
		app->fps.str_fps = ft_itoa((int)(1.0 / app->fps.frame_time));
		app->fps.delay = 0;
	}
	app->fps.delay++;
}

int			w_generate(t_app *app)
{
	int		x;

	x = 0;

	while (x < SIZE_W)
	{
		w_calculate_ray(app, x);
		w_calculate_step(app);
		w_dda_algo(app);
		w_calculate_current_vline(app, x);
		w_draw_vline(app, x);
		w_print_fps(app);
		x++;
		//w_debug_player(app);
		//w_debug_ray(app);
		//exit(0);
	}

	//clock_t t;
   // t = clock();
w_draw(app);
	//t = clock() - t;
   // double time_taken = ((double)t)/CLOCKS_PER_SEC;
	//printf("%f\n", time_taken);
	
	return (1);
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
	w_init_player(&app);
	//app.current_vline = w_get_vline(50, 0, SIZE_H, w_get_color(255, 255, 0, 0));
	//w_draw_vline(&app);
	//w_draw(&app);
	mlx_hook(app.win, 2, 3, w_event_repeat, &app);
	mlx_key_hook(app.win, w_event, &app);
	mlx_loop_hook(app.mlx, w_generate, &app);
	mlx_loop(app.mlx);
	return (0);
}
