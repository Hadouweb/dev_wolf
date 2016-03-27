#include "wolf3d.h"

void		w_set_map(t_app *app, char *file)
{
	int		fd;
	char	*line;
	t_list	*lst;
	int		size;

	fd = open(file, O_RDONLY);
	lst = NULL;
	size = 0;
	if (fd == -1)
		w_print_error_exit("Erreur d'ouverture du fichier : ", file);
	while (get_next_line(fd, &line) > 0)
	{
		size = ft_strlen(line) + 1;
		ft_lstpush_back(&lst, line, size);
		ft_strdel(&line);
		app->map.y++;
		if (size > app->map.x)
			app->map.x = size;
	}
	app->map.tab = (char**)ft_lsttotab(lst);
	ft_lstdel(&lst, w_del_node);
	w_debug_map(app);
}
