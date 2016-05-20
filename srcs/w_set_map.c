#include "wolf3d.h"

void		w_set_directive(t_app *app, char *str, int i)
{
	if (str[i] && str[1] == '0')
		app->player.pos_x = w_check_position(app, &str[i], 'x');
	else if (str[i] && str[1] == '1')
		app->player.pos_y = w_check_position(app, &str[i], 'y');
	else if (str[i] && str[1] >= '2' && str[1] <= '9')
		w_set_texture(app, &str[i], str[1]);
}

void		w_set_map(t_app *app, char *file)
{
	int		fd;
	char	*line;
	t_list	*lst;
	int		size;
	int		token;

	fd = open(file, O_RDONLY);
	lst = NULL;
	size = 0;
	app->player.pos_x = -1;
	app->player.pos_y = -1;
	token = 0;
	if (fd == -1)
		w_print_error_exit("Erreur d'ouverture du fichier : ", file);
	while (get_next_line(fd, &line) > 0)
	{
		if ((line[0] >= '0' && line[0] <= '9') || line[0] == '!')
		{
			if (w_check_line(app, line) == 1)
				token = 1;
			if (token == 0)
				line = ft_del_char(line, ' ');
			size = ft_strlen(line) + 1;
			ft_lstpush_back(&lst, line, size);
			ft_strdel(&line);
			if (token == 0)
				app->map.y++;
			if (size > app->map.x && token == 0)
				app->map.x = size - 2;
		}
	}
	if (app->map.y == 0)
	{
		ft_putstr_fd("Mauvais format de fichier\n", 2);
		exit(1);
	}
	app->map.y--;
	app->map.tab = w_set_tab(lst);
	if ((app->player.pos_x == -1 || app->player.pos_y == -1) ||
		app->map.tab[(int)app->player.pos_x][(int)app->player.pos_y] != 0)
	{
		ft_putstr_fd("Mauvaise position de la camera\n", 2);
		exit(1);
	}
	w_debug_map(app);
	ft_lstprint(lst, NULL);
	ft_lstdel(&lst, w_del_node);
}