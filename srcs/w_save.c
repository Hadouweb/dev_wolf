void		w_set_square(t_app *app, int pos_x, int pos_y, t_color color)
{
	int		x;
	int		y;
	int		edge;

	edge = 50; 
	y = 0;
	while (y < edge)
	{
		x = 0;
		while (x < edge)
		{
			w_set_pixel(app->obj, x + pos_x, y + pos_y, color);
			x++;
		}
		y++;
	}
}

void		w_test(t_app *app)
{
	int		x;
	int		y;
	int		m;
	char	**tab;

	tab = app->map.tab;
	y = 0;
	m = 55;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x])
		{
			if (tab[y][x] == '1')
				w_set_square(app, x * m, y * m, w_get_color(0, 0, 255, 0));
			else if (tab[y][x] == '0')
				w_set_square(app, x * m, y * m, w_get_color(0, 255, 0, 0));
			x++;
		}
		y++;
	}
	w_draw(app);
}