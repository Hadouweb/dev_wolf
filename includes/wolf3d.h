#ifndef WOLF3D_H
# define WOLF3D_H

#include <stdio.h>
#include "mlx.h"
#include "libft.h"

# define SIZE_W 1024
# define SIZE_H 768

typedef struct		s_obj
{
	void			*img;
	int				bpp;
	int				sizeline;
	int				endian;
	char			*data;
}					t_obj;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_color;

typedef struct  	s_app
{
	void			*mlx;
	void			*win;
	t_obj			*obj;
	int				end;
}					t_app;

int			w_event(int keycode, t_app *app);

void		w_draw(t_app *app);
void		w_set_obj(t_obj *obj, int x, int y, t_color color);
t_color		w_get_color(unsigned char r, unsigned char g,
	unsigned char b, unsigned char a);
t_obj		*w_init_obj_info(void *mlx, int width, int height);

#endif