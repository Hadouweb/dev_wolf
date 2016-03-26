/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 00:57:48 by nle-bret          #+#    #+#             */
/*   Updated: 2016/03/27 00:57:50 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		w_init_sdl(t_app *app)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_putstr_fd("Erreur lors de l'initialisation de la SDL : \n", 2);
		ft_putendl_fd(SDL_GetError(), 2);
		SDL_Quit();
		return (0);
	}
	app->win = SDL_CreateWindow("Test SDL 2.0",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_SHOWN);
	if (app->win == 0)
	{
		ft_putstr_fd("Erreur lors de la creation de la fenetre : ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
		SDL_Quit();
		return (0);
	}
	return (1);
}

int		main(void)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	if (!w_init_sdl(&app))
		return (1);
	while (!app.end)
	{
		SDL_WaitEvent(&app.event);
		if (app.event.window.event == SDL_WINDOWEVENT_CLOSE)
			app.end = 1;
	}
	SDL_DestroyWindow(app.win);
	SDL_Quit();
	return (0);
}
