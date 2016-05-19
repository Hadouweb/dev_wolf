#include "wolf3d.h"

void			w_current_position_of_ray(t_app *app, int x)
{
	app->player.camera_x = 2 * x / (double)SIZE_W - 1; //Position de la camera en x
	app->ray.ray_pos_x = app->player.pos_x; //Position de depart du rayon en x
	app->ray.ray_pos_y = app->player.pos_y; //Position de depart du rayon en y
	app->ray.ray_dir_x = app->player.dir_x + app->player.cam_plane_x * app->player.camera_x; //Direction du rayon en x
	app->ray.ray_dir_y = app->player.dir_y + app->player.cam_plane_y * app->player.camera_x; //Direction du rayon en y
	app->ray.map_x = (int)app->ray.ray_pos_x; //Position acutel du joueur/cam sur la grille en x
	app->ray.map_y = (int)app->ray.ray_pos_y; //Position acutel du joueur/cam sur la grille en y
}

static double	w_correction_fisheye_effect(t_app *app)
{
	double	perp_wall_dist;

	if (app->ray.side == 0) // Calcul de la distance de la camera pour corriger le fisheye effect
		perp_wall_dist = (app->ray.map_x - app->ray.ray_pos_x +
			(1 - app->ray.step_x) / 2) / app->ray.ray_dir_x;
	else			 
		perp_wall_dist = (app->ray.map_y - app->ray.ray_pos_y +
			(1 - app->ray.step_y) / 2) / app->ray.ray_dir_y;
	return (perp_wall_dist);
}

t_color			w_get_cardinal_color(t_app *app)
{
	t_color color;
	
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
	return (color);
}

t_color			w_texture_color(t_app *app, int x)
{
	t_color 	color;

	color = w_get_color(0, 255, 0, 0);
	if (x && app)
		;
	return (color);
}

void		w_set_pixel_texture(t_obj *obj, int x, int y, t_obj *texture, int wall_height)
{
	int 	index;
	int 	d;
	int 	texture_y;
	int 	index_texture;

	if (y < 0 || y > SIZE_H - 1 || x < 0 || x > SIZE_W - 1)
		return ;
	d = y * 256 - SIZE_H * 128 + wall_height * 128;
	texture_y = ((d * texture->height) / wall_height) / 256;
	index_texture = texture_y * texture->sizeline +
		texture->x * texture->bpp / 8;
	index = y * obj->sizeline + x * obj->bpp / 8;
	obj->data[index] = texture->data[index_texture];
	obj->data[index + 1] = texture->data[index_texture + 1];
	obj->data[index + 2] = texture->data[index_texture + 2];
}

void			w_preparation_for_texture(t_app *app, double perp_wall_dist)
{
	double	wall_x;

	if (app->ray.side == 0) 
		wall_x = app->ray.ray_pos_y + perp_wall_dist * app->ray.ray_dir_y;
	else
		wall_x = app->ray.ray_pos_x + perp_wall_dist * app->ray.ray_dir_x;
	wall_x -= floor(wall_x);

	app->texture->x = (int)(wall_x * (double)app->texture->width);
	if(app->ray.side == 0 && app->ray.ray_dir_y > 0) 
		app->texture->x = app->texture->width - app->texture->x - 1;
	if(app->ray.side == 1 && app->ray.ray_dir_x < 0) 
		app->texture->x = app->texture->width - app->texture->x - 1;
}

void			w_preparation_for_vline(t_app *app, int x)
{
	int		wall_height;
	int 	down_wall;
	int		top_wall;
	double	perp_wall_dist;

	perp_wall_dist = w_correction_fisheye_effect(app);
	wall_height = (int)(SIZE_H / perp_wall_dist); // La hauteur du mur a tracer

	down_wall = -wall_height / 2 + SIZE_H / 2; // Le bas du mur
	if (down_wall < 0)
		down_wall = 0;

	top_wall = wall_height / 2 + SIZE_H / 2; // Le haut du mur
	if (top_wall >= SIZE_H)
		top_wall = SIZE_H - 1;

	w_preparation_for_texture(app, perp_wall_dist);
	app->current_vline = w_get_vline(x, down_wall, top_wall,
		w_texture_color(app, x));
}

void			w_draw_vline(t_app *app, int x)
{
	int		y;
	int		max;
	int 	height;

	y = app->current_vline.y_start;
	max = app->current_vline.y_end;
	height = max - y;
	while (y < max)
	{
		w_set_pixel_texture(app->obj, x, y, app->texture, height);
		y++;
	}
}

int				w_draw_view(t_app *app)
{
	int		x;

	x = 0;

	while (x < SIZE_W)
	{
		w_current_position_of_ray(app, x);
		w_preparation_for_dda_algorithm(app);
		w_dda_algorithm(app);
		w_preparation_for_vline(app, x);
		w_draw_vline(app, x);
		w_print_fps(app);
		x++;
	}
	w_draw(app);
	return (1);
}