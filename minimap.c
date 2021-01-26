
#include "cub3d.h"

void    my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;
    dst = game->mlx.img.data_addr + (y * game->mlx.img.size_line + x * (game->mlx.img.bpp / 8));
    *(unsigned int*)dst = color;
}

void    draw_line(int x0, int y0, int x1, int y1, int color, t_game *game)
{
  int dx =  ft_abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -ft_abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
            my_mlx_pixel_put(game, x0, y0, color);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

void    disp_square(int x, int y, int color, t_game *game, int width)
{
    int i;
    int j;

    j = y + width; 
    while (j >= y)
    {
        i = x + width;
        while (i >= x)
        {    
            if (j == y || j == y + width || i == x || i == x + width)
                my_mlx_pixel_put(game, i, j, 0x000000);
            else
                my_mlx_pixel_put(game, i, j, color);
            i--;
        }
        j--;
    }
}

void    ft_disp_minimap(t_game *game)
{
    //printf("disp_map_____________\n");
    int i; 
    int j;
    int tileX;
    int tileY;
    int max_x;
    int max_y;

    find_max(game, &max_x, &max_y);
    j = 0;
    while (j < max_y)
    {
        i = 0; 
        while (i < max_x)
        {
            tileX = i * 64;    
            tileY = j * 64;

            if (game->map[j][i] == '1')
                disp_square(0.2 * tileX, 0.2 * tileY, 0xaaaa00, game, 0.2 * 64);
            else if (game->map[j][i] == '2')
                disp_square(0.2 * tileX, 0.2 * tileY, 0x8888ff, game, 0.2 * 64);    
            else
                disp_square(0.2 * tileX, 0.2 * tileY, 0x333333, game, 0.2 * 64);
            i++;
        }
        j++;
    }
    draw_line(game->player.pos.x / 5, game->player.pos.y / 5, (game->player.pos.x + cos(game->player.angle) * 63) / 5, (game->player.pos.y + sin(game->player.angle) * 63) / 5, 0x00ff00, game);
    draw_line(game->player.pos.x / 5, game->player.pos.y / 5, (game->player.pos.x + cos(game->player.angle - (FOV / 2 * M_PI / 180)) * 63) / 5, (game->player.pos.y + sin(game->player.angle - (FOV / 2 * M_PI / 180)) * 63) / 5, 0xff0000, game);
    draw_line(game->player.pos.x / 5, game->player.pos.y / 5, (game->player.pos.x + cos(game->player.angle + (FOV / 2 * M_PI / 180)) * 63) / 5, (game->player.pos.y + sin(game->player.angle + (FOV / 2 * M_PI / 180)) * 63) / 5, 0xff0000, game);
    disp_square(game->player.pos.x / 5 - 3, game->player.pos.y / 5 - 3, 0xffff00, game, 5);    
}
