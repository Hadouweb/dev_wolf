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

void		w_add_texture_xpm(t_app *app, char *file_name, char num)
{
	t_texture	texture;
	t_obj		*obj;
	int			height;
	int			width;

	printf("%s\n\n", file_name);
	obj = NULL;
	ft_bzero(&texture, sizeof(t_texture));
	if ((obj = (t_obj *)ft_memalloc(sizeof(t_obj))) == NULL)
		ft_putstr_fd("Erreur d'allocation de t_obj\n", 2);

	obj->img = mlx_xpm_file_to_image(app->mlx, file_name,
		&width, &height);

	if (obj->img == NULL)
		return;

	obj->data = mlx_get_data_addr(obj->img,
		&obj->bpp,
		&obj->sizeline,
		&obj->endian);

	texture.num = num;
	texture.x = 0;
	texture.y = 0;
	texture.width = width;
	texture.height = height;
	texture.obj = obj;

	ft_lstpush_front(&app->lst_texture, &texture, sizeof(t_texture));

	t_texture *test;

	test = (t_texture*)app->lst_texture->content;
	//w_print_lst_texture(test);
	//ft_lstprint(app->lst_texture, w_print_lst_texture);
}

void		w_set_directive(t_app *app, char *str, int i)
{
	if (str[i] && str[1] == '0')
		app->player.pos_x = w_check_position(app, &str[i], 'x');
	else if (str[i] && str[1] == '1')
		app->player.pos_y = w_check_position(app, &str[i], 'y');
	else if (str[i] && str[1] >= '2' && str[1] <= '9')
		w_add_texture_xpm(app, &str[i], str[1]);
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
			w_set_directive(app, str, i);
		}
	}

}

int			w_check_line(t_app *app, char *str)
{
	int		i;

	i = 0;
	if (str)
	{
		if (str[0] && str[0] == '!')
		{
			w_check_directive(app, str);
			return (1);
		}
		else
		{
			while (str[i])
			{
				if (str[i] != ' ' && (str[i] > '9' || str[i] < '0'))
				{
					ft_putstr_fd("Mauvais format de map\n", 2);
					exit(1);
				}
				i++;
			}
		}
	}
	return (0);
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
