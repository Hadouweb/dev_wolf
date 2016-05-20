#include "wolf3d.h"

void	w_set_view(t_app *app)
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


void	w_set_one_dim(int **tab, t_list *l)
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

int		**w_set_tab(t_list *l)
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