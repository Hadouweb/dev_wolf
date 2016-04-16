#ifndef WOLF3D_H
# define WOLF3D_H

#include <stdio.h>
#include "mlx.h"
#include "libft.h"
#include <fcntl.h>
#include <math.h>

# define SIZE_W 1600
# define SIZE_H 1200

# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125

typedef struct		s_obj
{
	void			*img;
	int				bpp;
	int				sizeline;
	int				endian;
	char			*data;
}					t_obj;

typedef struct 		s_vector
{
	int				x;
	int				y;
}					t_vector;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_color;

typedef struct 		s_vline
{
	int				x;
	int				y_start;
	int				y_end;
	t_color			color;
}					t_vline;

typedef struct 		s_map
{
	int				x;
	int				y;
	int				**tab;
}					t_map;

typedef struct  	s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			cam_plane_x;
	double			cam_plane_y;
	double			camera_x;
}					t_player;

typedef struct  	s_ray
{
	double			ray_pos_x;
	double			ray_pos_y;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			dela_dist_x;
	double			dela_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				side;
}					t_ray;

typedef struct  	s_app
{
	void			*mlx;
	void			*win;
	t_obj			*obj;
	t_map			map;
	int				end;
	t_vline			current_vline;
	int				up;
	t_player		player;
	t_ray			ray;
}					t_app;

int			w_event_arrow_key(int keycode, t_app *app);
int			w_event_repeat(int keycode, t_app *app);
int			w_test(t_app *app);
int			w_event(int keycode, t_app *app);

void		w_draw(t_app *app);
void		w_draw_vline(t_app *app, int x);
t_vline		w_get_vline(int x, int y_start, int y_end, t_color color);
void		w_set_pixel(t_obj *obj, int x, int y, t_color color);
t_color		w_get_color(unsigned char r, unsigned char g,
	unsigned char b, unsigned char a);
t_obj		*w_init_obj_info(void *mlx, int width, int height);

void		w_del_node(void *content, size_t content_size);

void		w_set_map(t_app *app, char *file);

void		w_print_error_exit(char *str, char *error);

void		w_debug_map(t_app *app);

#endif