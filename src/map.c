/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:29:27 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/10/18 17:10:39 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))
		#define SGN(_x) ((_x) < 0 ? -1 : \
						((_x) > 0 ? 1 : 0))
#define MAX_VALUE 2147483647
#define TRUE 1
#define FALSE 0

void drawLine(t_game *data, int x0, int y0, int x1, int y1, int color)
		{
			char *dst;
			int dx = x1 - x0;
			int dy = y1 - y0;
			int incX = SGN(dx);
			int incY = SGN(dy);
			dx = ABS(dx);
			dy = ABS(dy);


	// printf("%d - %d - %d - %d\n", x0, y0, x1, y1);
			if (dy == 0)
			{
				// horizontal line
				for (int x = x0; x != x1 + incX; x += incX)
				{
						dst = data->addr + (y0 * data->line_length + x * (data->bits_per_pixel / 8));
					*(unsigned int*)dst = color;
				}
			}
			else if (dx == 0)
			{
				// vertical line
				for (int y = y0; y != y1 + incY; y += incY)
				{
					dst = data->addr + (y * data->line_length + x0 * (data->bits_per_pixel / 8));
					*(unsigned int*)dst = color;
				}
			}
			else if (dx >= dy)
			{
				// more horizontal than vertical
				int slope = 2 * dy;
				int error = -dx;
				int errorInc = -2 * dx;
				int y = y0;

				for (int x = x0; x != x1 + incX; x += incX)
				{
					dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
					*(unsigned int*)dst = color;
					error += slope;

					if (error >= 0)
					{
						y += incY;
						error += errorInc;
					}
				}
			}
			else
			{
				// more vertical than horizontal
				int slope = 2 * dx;
				int error = -dy;
				int errorInc = -2 * dy;
				int x = x0;

				for (int y = y0; y != y1 + incY; y += incY)
				{
					dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
					*(unsigned int*)dst = color;
					error += slope;

					if (error >= 0)
					{
						x += incX;
						error += errorInc;
					}
				}
			}
		}

void drawCircle(int xc, int yc, int x, int y, int color, t_game *data) 
{ 
	char *dst;

	dst = data->addr + ((yc+y)* data->line_length + (xc+x)* (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	dst = data->addr + ((yc+y)* data->line_length + (xc-x)* (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	dst = data->addr + ((yc-y)* data->line_length + (xc+x)* (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	dst = data->addr + ((yc-y)* data->line_length + (xc-x)* (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	dst = data->addr + ((yc+x)* data->line_length + (xc+y)* (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	dst = data->addr + ((yc+x)* data->line_length + (xc-y)* (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	dst = data->addr + ((yc-x)* data->line_length + (xc+y)* (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	dst = data->addr + ((yc-x)* data->line_length + (xc-y)* (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
} 
  
// Function for circle-generation 
// using Bresenham's algorithm 
void circleBres(t_game *data, int xc, int yc, int r) 
{ 
    int x = 0, y = r; 
    int d = 3 - 2 * r;
    drawCircle(xc, yc, x, y, 0x00000000, data); 
    while (y >= x) 
    { 
        // for each pixel we will 
        // draw all eight pixels 
          
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
        drawCircle(xc, yc, x, y, 0x00000000, data); 
    } 
} 

void	makewall(t_game *data, int x, int y, int color)
{
	char *dst;
	int iy;
	int ix;

	iy = 0;
	ix = 0;
	while (ix < data->map.map_tile_size.x)
	{
		while (iy < data->map.map_tile_size.y)
		{
			dst = data->addr + ((y+iy) * data->line_length + (x + ix) * (data->bits_per_pixel / 8));
			if(iy == (int)data->map.map_tile_size.y - 1)
				*(unsigned int*)dst = 0x00654e32;
			else if(ix == (int)data->map.map_tile_size.x - 1)
				*(unsigned int*)dst = 0x00654e32;
			else
				*(unsigned int*)dst = color;
			iy++;
		}
		iy = 0;
		ix++;
	}
}

void	makesqre(t_game *data, int x, int y, int color)
{
	char *dst;
	int iy;
	int ix;

	iy = 0;
	ix = 0;
	while (ix < data->map.map_tile_size.x)
	{
		while (iy < data->map.map_tile_size.y)
		{
			dst = data->addr + ((y+iy) * data->line_length + (x + ix) * (data->bits_per_pixel / 8));
			*(unsigned int*)dst = color;
			iy++;
		}
		iy = 0;
		ix++;
	}
}

void castRays(t_game *data, int px, int py)
{
	 	double rayAngle = data->player.rotationAngle - (FOV_ANGLE / 2);
		int i = 0;

		while (i < data->size_x)
		{
			castRay(data, px, py, rayAngle);
			rayAngle += FOV_ANGLE / data->size_x;
			i++;
		}
		circleBres(data, ((data->player.pos.x+1) * data->map.map_tile_size.x+1), ((data->player.pos.y+1) * data->map.map_tile_size.y+1), data->map.map_tile_size.x / 4);
}

void renderPlayer(t_game *data)
{
	int px, py;

	px = 0;
	py = 0;
	px = ((data->player.pos.x) * data->map.map_tile_size.x);
	py = ((data->player.pos.y) * data->map.map_tile_size.y);
	castRays(data, px, py);
}

void draw_border(t_game *game, int width, int height, int x)
{
	drawLine(game, 0, 0, width, 0, 0x00000000);
	drawLine(game, x, x, width - (x + 1), x, 0x00000000);
	drawLine(game, width - x - 1, x, width - x - 1, height - x - 1, 0x00000000);
	drawLine(game, width - 1, 0, width - 1, height, 0x00000000);
	drawLine(game, 0, 0, 0, height, 0x00000000);
	drawLine(game, x, x, x, height - x - 1, 0x00000000);
	drawLine(game, 0, height - 1, width, height - 1, 0x00000000);
	drawLine(game, x, height - x - 1, width - x - 1, height - x - 1, 0x00000000);
}

void    load_map(t_game *game)
{
	static int map = 0;
    int x;
    int y;
	int i;
	static int map_height = 0;
	static int map_width = 0;
	i = 0;
    x = 0;
    y = 0;
	if(map == 0)
	{
		game->map.map_tile_size.x = floor((double)((double)300 / (double)game->map.col_map));
		game->map.map_tile_size.y = floor((double)((double)200 / (double)game->map.row_map));
		if(game->map.map_tile_size.x > game->map.map_tile_size.y)
			game->map.map_tile_size.x = game->map.map_tile_size.y;
		else
			game->map.map_tile_size.y = game->map.map_tile_size.x;
		map_height = (int)((game->map.map_tile_size.y * game->map.row_map) + game->map.map_tile_size.x * 2);
		map_width = (int)((game->map.map_tile_size.x * game->map.col_map) + game->map.map_tile_size.x * 2);
		game->image.map = mlx_new_image(game->init, (int)map_width, (int)map_height);
		game->addr = mlx_get_data_addr(game->image.map, &game->bits_per_pixel, &game->line_length, &game->endian);
		map++;
	}
	while (i < map_height)
	{
		if(i < game->map.map_tile_size.y)
		{
			if(i < game->map.map_tile_size.y / 2)
				drawLine(game, 0, i, game->map.map_tile_size.x * game->map.col_map + game->map.map_tile_size.x * 2, i, 0x00e0b856);
			else
				drawLine(game, 0, i, game->map.map_tile_size.x * game->map.col_map + game->map.map_tile_size.x * 2, i, 0x00d7903c);
		}
		else
			drawLine(game, game->map.map_tile_size.x, i, (map_width) - game->map.map_tile_size.x, i, 0x002f230e);
		drawLine(game, 0, i, game->map.map_tile_size.x - 1, i, 0x00e0b856);
		drawLine(game, (map_width) - game->map.map_tile_size.x, i, map_width, i, 0x00e0b856);
		if(i >= (map_height) - game->map.map_tile_size.y)
			drawLine(game, 0, i, (game->map.map_tile_size.x * game->map.col_map) +  game->map.map_tile_size.x * 2, i, 0x00e0b856);
		i++;
	}
	while(game->map.map_temp[y][x])
	{
            if(game->map.map_temp[y][x] == '1')
            {
               makewall(game, ((x+1) * game->map.map_tile_size.x), ((y+1) * game->map.map_tile_size.y), 0x00898989);
               x++;
            } else
            if(game->map.map_temp[y][x] == '0')
            {
                makesqre(game, ((x+1) * game->map.map_tile_size.x), ((y+1) * game->map.map_tile_size.y), 0x0000FF00);
                x++;
            } else
			if(ft_strchr("NSWE", game->map.map_temp[y][x]) != NULL)
			{
				makesqre(game, ((x+1) * game->map.map_tile_size.x), ((y+1) * game->map.map_tile_size.y), 0x0000FF00);
                x++;
            } else
			if(game->map.map_temp[y][x] == '\n')
            {
                y++;
				if(x >= (game->map.col_map) && y >= (game->map.row_map))
					break;
                x = 0;
            }
			else
			{
				x++;
			}
		}
		draw_border(game, map_width, map_height, game->map.map_tile_size.x);
}

static int ft_free_values(char *str1, char *str2, char *str3, int ret)
{
	if (str1 != NULL)
		free(str1);
	if (str2 != NULL)
		free(str2);
	if (str3 != NULL)
		free(str3);
	return (ret);
}

static int ft_all_number(char *str)
{
	int x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == ' ' || str[x] == '\t' || str[x] == '\n' || str[x] == '\r')
		{
			x++;
			continue;
		}
		else if (ft_isdigit(str[x]) == 0)
			return (1);
		x++;
	}
	return (0);
}

static int ft_skip_line(char **line, int fd)
{
	char *aux;

	aux = NULL;
	free(*line);
	*line = get_next_line(fd);
	aux = ft_strtrim(*line, "");
	while (aux != NULL && ft_strlen(aux) <= 2)
	{
		free(*line);
		*line = get_next_line(fd);
		free(aux);
		aux = ft_strtrim(*line, "");
	}
	free(aux);
	return (0);
}

int ft_get_textures(t_map *map, int *texture, char **line, int fd)
{
	char *aux;
	char *cardinal_points;
	char *path;

	path = NULL;
	aux = ft_strtrim(*line, " ");
	cardinal_points = ft_substr(aux, 0, 2);
	path = ft_substr(aux, ft_strlen(cardinal_points), (ft_strlen(aux) - ft_strlen(cardinal_points)));
	if (ft_strncmp(cardinal_points, "NO", 2) == 0)
		map->path_NO = ft_strtrim(path, " ");
	else if (ft_strncmp(cardinal_points, "SO", 2) == 0)
		map->path_SO = ft_strtrim(path, " ");
	else if (ft_strncmp(cardinal_points, "WE", 2) == 0)
		map->path_WE = ft_strtrim(path, " ");
	else if (ft_strncmp(cardinal_points, "EA", 2) == 0)
		map->path_EA = ft_strtrim(path, " ");
	else
	{
		ft_skip_line(line, fd);
		return (ft_free_values(path, cardinal_points, aux, 3));
	}
	*texture += 1;
	ft_skip_line(line, fd);
	return (ft_free_values(path, cardinal_points, aux, 0));
}

int ft_get_colors(t_map *map, int *colors, char **line, int fd)
{
	char *aux;
	char *rgb;
	char **temp;
	int x;

	x = 0;
	aux = ft_strtrim(*line, " ");
	rgb = ft_substr(aux, 1, (ft_strlen(aux) - 1));
	temp = ft_split(rgb, ',');
	x = -1;
	while (temp[++x] != NULL)
	{
		// printf("%s\n", temp[x]);
		if (ft_all_number(temp[x]) == 1)
			return (ft_free_values(aux, NULL, rgb, INVALID_COLORS));
		if (aux[0] == 'C')
			map->ceiling[x] = ft_atoi(temp[x]);
		else
			map->floor[x] = ft_atoi(temp[x]);
		free(temp[x]);
	}
	if(x != 3)
		return (INVALID_COLORS);
	free(temp);
	ft_skip_line(line, fd);
	*colors += 1;
	return (ft_free_values(aux, NULL, rgb, 0));
}