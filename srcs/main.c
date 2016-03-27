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
		1024, 768, SDL_WINDOW_SHOWN);
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
	t_app		app;
	int			t;
	SDL_Texture	*texture;
	SDL_Rect 	r;

	t = 20;
	ft_bzero(&app, sizeof(t_app));
	if (!w_init_sdl(&app))
		return (1);
	app.renderer = SDL_CreateRenderer(app.win, -1, SDL_RENDERER_ACCELERATED);
	//SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
	//SDL_RenderClear(app.renderer);
   	texture = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);
  // 	SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
   	//SDL_RenderDrawLine(app.renderer, 0, 10, 1000, 10);
    //SDL_RenderPresent(app.renderer);
	while (!app.end)
	{
		if (SDL_PollEvent(&app.event) && app.event.type == SDL_KEYDOWN)
		{
			if (app.event.window.event == SDL_WINDOWEVENT_CLOSE)
				app.end = 1;
			else if (app.event.key.keysym.sym == SDLK_ESCAPE)
				app.end = 1;
			else if (app.event.key.keysym.sym == SDLK_LEFT)
			{
				r.w = 100;
				r.h = 50;
				r.x=rand()%500;
                r.y=rand()%500;
				t += 1;
				printf("LEFT\n");
				SDL_SetRenderTarget(app.renderer, texture);
				SDL_SetRenderDrawColor(app.renderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderClear(app.renderer);
				SDL_SetRenderDrawColor(app.renderer, 0x00, 0xff, 0x00, 0x00);
				SDL_RenderDrawLine(app.renderer, 0, t, 1000, t);
				SDL_RenderDrawRect(app.renderer,&r);
				SDL_SetRenderTarget(app.renderer, NULL);
				SDL_RenderCopy(app.renderer, texture, NULL, NULL);
				SDL_RenderPresent(app.renderer);
			}
			else
				printf("%d\n", app.event.key.keysym.sym);
		}
	}
	SDL_DestroyWindow(app.win);
	SDL_Quit();
	return (0);
}
