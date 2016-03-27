#include "wolf3d.h"

void		w_debug_map(t_app *app)
{
	int		i;

	i = 0;
	ft_putstr("Largeur de la carte : ");
	ft_putnbr(app->map.x);
	ft_putchar('\n');
	ft_putstr("Hauteur de la carte : ");
	ft_putnbr(app->map.y);
	ft_putchar('\n');
	ft_putstr("Carte : \n");
	while (app->map.tab[i])
	{
		ft_putendl(app->map.tab[i]);
		i++;
	}
}
