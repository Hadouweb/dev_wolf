#include "wolf3d.h"

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void		w_test(t_app *app)
{
double posX = 8, posY = 5; 
  double dirX = -1, dirY = 0; //initial direction vector
  double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

 // while(1)
  //{
	for(int x = 0; x < SIZE_W; x++)
	{

	  //calculate ray position and direction
	  double cameraX = 2 * x / (double)SIZE_W - 1; //x-coordinate in camera space
	  double rayPosX = posX;
	  double rayPosY = posY;
	  double rayDirX = dirX + planeX * cameraX;
	  double rayDirY = dirY + planeY * cameraX;
	  //which box of the map we're in
	  int mapX = (int)rayPosX;
	  int mapY = (int)rayPosY;

	  //length of ray from current position to next x or y-side
	  double sideDistX;
	  double sideDistY;

	   //length of ray from one x or y-side to next x or y-side
	  double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
	  double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
	  double perpWallDist;

	  //what direction to step in x or y-direction (either +1 or -1)
	  int stepX;
	  int stepY;

	  int hit = 0; //was there a wall hit?
	  int side; //was a NS or a EW wall hit?
	  //calculate step and initial sideDist
	  if (rayDirX < 0)
	  {
		stepX = -1;
		sideDistX = (rayPosX - mapX) * deltaDistX;
	  }
	  else
	  {
		stepX = 1;
		sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
	  }
	  if (rayDirY < 0)
	  {
		stepY = -1;
		sideDistY = (rayPosY - mapY) * deltaDistY;
	  }
	  else
	  {
		stepY = 1;
		sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
	  }
	  //perform DDA
	  while (hit == 0)
	  {
		//jump to next map square, OR in x-direction, OR in y-direction
		if (sideDistX < sideDistY)
		{
		  sideDistX += deltaDistX;
		  mapX += stepX;
		  side = 0;
		}
		else
		{
		  sideDistY += deltaDistY;
		  mapY += stepY;
		  side = 1;
		}
		//printf("ok\n");
		//Check if ray has hit a wall
		if (app->map.tab[mapX][mapY] > '0') 
			hit = 1;
		//printf("ok2\n");
	  }
	  //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
	  if (side == 0) 
	  	perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
	  else			 
	  	perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

	  //Calculate height of line to draw on screen
	  int lineHeight = (int)(SIZE_H / perpWallDist);

	  //calculate lowest and highest pixel to fill in current stripe
	  int drawStart = -lineHeight / 2 + SIZE_H / 2;
	  if(drawStart < 0)drawStart = 0;
	  int drawEnd = lineHeight / 2 + SIZE_H / 2;
	  if(drawEnd >= SIZE_H)drawEnd = SIZE_H - 1;

	  //give x and y sides different brightness
	  //if (side == 1) {color = color / 2;}

	  //draw the pixels of the stripe as a vertical line
	  //verLine(x, drawStart, drawEnd, color);
	  app->current_vline = w_get_vline(x, drawStart, drawEnd, 
	  	w_get_color(255, 255, 0, 0));
	  //printf("%d %d %d\n", x, drawStart, drawEnd);
	  w_draw_vline(app);
	    if (app->up)
	    {
	      if(app->map.tab[(int)(posX + dirX)][(int)posY] == '0') 
	      	posX += dirX * 0.01;
	      if(app->map.tab[(int)posX][(int)(posY + dirY)] == '0') 
	      	posY += dirY * 0.01;
	    }
	}
	w_draw(app);
	//}
}

int			main(int ac, char **av)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, SIZE_W, SIZE_H, "Wolf3D");
	app.obj = w_init_obj_info(app.mlx, SIZE_W, SIZE_H);

	if (ac > 1)
		w_set_map(&app, av[1]);
	//app.current_vline = w_get_vline(50, 0, SIZE_H, w_get_color(255, 255, 0, 0));
	//w_draw_vline(&app);
	//w_draw(&app);
	w_test(&app);

	mlx_key_hook(app.win, w_event, &app);
	mlx_loop(app.mlx);
	return (0);
}
