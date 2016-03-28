#include "wolf3d.h"

static void		w_draw_x(t_inc inc, t_img *obj, t_vector a, t_vector b)
{
	int		i;

	i = 0;
	inc.e = 2 * inc.dy - inc.dx;
	inc.inc1 = 2 * (inc.dy - inc.dx);
	inc.inc2 = 2 * inc.dy;
	while (i < inc.dx)
	{
		if (inc.e >= 0)
		{
			inc.y += inc.incy;
			inc.e += inc.inc1;
		}
		else
			inc.e += inc.inc2;
		inc.x += inc.incx;
		w_generate_image(obj, inc.x, inc.y, color);
		i++;
	}
}

static void		w_draw_y(t_inc inc, t_img *obj, t_vector a, t_vector b)
{
	int		i;

	i = 0;
	inc.e = 2 * inc.dx - inc.dy;
	inc.inc1 = 2 * (inc.dx - inc.dy);
	inc.inc2 = 2 * inc.dx;
	while (i < inc.dy)
	{
		if (inc.e >= 0)
		{
			inc.x += inc.incx;
			inc.e += inc.inc1;
		}
		else
			inc.e += inc.inc2;
		inc.y += inc.incy;
		w_generate_image(obj, inc.x, inc.y, color);
		i++;
	}
}

void			w_draw_line(t_img *obj, t_vector a, t_vector b, t_color color)
{
	int		i;
	t_inc	inc;

	i = 0;
	inc.dx = fabs(b.x - a.x);
	inc.dy = fabs(b.y - a.y);
	inc.incx = 1;
	inc.incy = 1;
	if (b.x < a.x)
		inc.incx = -1;
	if (b.y < a.y)
		inc.incy = -1;
	inc.x = a.x;
	inc.y = a.y;
	if (inc.dx > inc.dy)
		ft_draw_x(inc, obj, a, b);
	else
		ft_draw_y(inc, obj, a, b);
}