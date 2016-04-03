#include "wolf3d.h"

void		w_debug_map(t_app *app)
{
	int		i;
	int		j;

	i = 0;
	ft_putstr("Largeur de la carte : ");
	ft_putnbr(app->map.x);
	ft_putchar('\n');
	ft_putstr("Hauteur de la carte : ");
	ft_putnbr(app->map.y);
	ft_putchar('\n');
	ft_putstr("Carte : \n");
	while (i <= app->map.y)
	{
		j = 0;
		while (j <= app->map.x)
		{	
			ft_putnbr(app->map.tab[i][j]);
			//ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
