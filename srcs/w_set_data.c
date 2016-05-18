#include "wolf3d.h"

static void	w_set_one_dim(int **tab, t_list *l)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char*)l->content;
	while (i < l->content_size)
	{
		(*tab)[i] = (int)(str[i] - '0');
		i++;
	}
}

static int	**w_set_tab(t_list *l)
{
	int		**tab;
	size_t	size;
	size_t	i;

	size = ft_lstsize(l);
	if ((tab = (int **)ft_memalloc(size * sizeof(int *) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i < size && l)
	{
		if ((tab[i] = (int *)ft_memalloc(l->content_size * sizeof(int))) == NULL)
			return (NULL);
		w_set_one_dim(&tab[i], l);
		l = l->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int			w_check_position(t_app *app, char *str, char d)
{
	int		p;

	p = ft_atoi(str);
	if (d == 'x' && p >= 0 && p <= app->map.x)
		return (p);
	else if (d == 'y' && p >= 0 && p <= app->map.y)
		return (p);
	ft_putstr_fd("Mauvaise position de la camera\n", 2);
	exit(1);
	return (0);
}

void		w_check_directive(t_app *app, char *str)
{
	int		i;

	i = 0;
	if (str[1] && str[1] >= '0' && str[1] <= '9')
	{
		i++;
		while (str[i] && str[i] != ' ')
			i++;
		if (str[i] && str[i] == ' ')
		{
			i++;
			if (str[i] && str[1] == '0')
				app->player.pos_x = w_check_position(app, &str[i], 'x');
			else if (str[i] && str[1] == '1')
				app->player.pos_y = w_check_position(app, &str[i], 'y');
		}
	}

}

void		w_check_line(t_app *app, char *str)
{
	int		i;

	i = 0;
	if (str)
	{
		if (str[0] && str[0] == '!')
			w_check_directive(app, str);
		else
		{
			while (str[i])
			{
				if (str[i] != ' ' && (str[i] > '9' || str[i] < '0'))
				{
					ft_putstr_fd("Mauvais format de fichier\n", 2);
					exit(1);
				}
				i++;
			}
		}
	}
}

void		w_set_map(t_app *app, char *file)
{
	int		fd;
	char	*line;
	t_list	*lst;
	int		size;

	fd = open(file, O_RDONLY);
	lst = NULL;
	size = 0;
	app->player.pos_x = -1;
	app->player.pos_y = -1;
	if (fd == -1)
		w_print_error_exit("Erreur d'ouverture du fichier : ", file);
	while (get_next_line(fd, &line) > 0)
	{
		w_check_line(app, line);
		line = ft_del_char(line, ' ');
		size = ft_strlen(line) + 1;
		ft_lstpush_back(&lst, line, size);
		ft_strdel(&line);
		app->map.y++;
		if (size > app->map.x)
			app->map.x = size - 2;
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

	ft_lstdel(&lst, w_del_node);
}

void		w_set_view(t_app *app)
{
	app->player.dir_x = -1; //Direction du joueur en x
	app->player.dir_y = 0; //Direction du joueur en y
	app->player.cam_plane_x = 0; //Plan de la camera en x
	app->player.cam_plane_y = 0.60; //Plan de la camera en y

	app->fps.time = 0; //time of current frame
  	app->fps.old_time = 0; //time of previous frame
  	app->fps.delay = 0;
  	app->fps.str_fps = ft_strdup("0");
}
