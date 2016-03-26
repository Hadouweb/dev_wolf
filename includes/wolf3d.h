#ifndef WOLF3D_H
# define WOLF3D_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include "libft.h"

typedef struct  	s_app
{
	SDL_Window		*win;
	SDL_Event 		event;
	int				end;
}					t_app;

#endif