/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:24:41 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/11/23 15:18:12 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void ft_get_position(t_game *game)
{
    game->dda.texNum = game->map.map_plan[(int)game->dda.mapPos.y][(int)game->dda.mapPos.x] - 1;
    if (game->dda.hitSide == 0)
        game->dda.wallX = game->player.pos.y + game->dda.perpendicularDist * game->dda.rayDir.y;
    else
        game->dda.wallX = game->player.pos.x + game->dda.perpendicularDist * game->dda.rayDir.x;
    game->dda.wallX -= floor(game->dda.wallX);
    game->dda.texX = (int)(game->dda.wallX * (double)64);
    if (game->dda.hitSide == 0 && game->dda.rayDir.x > 0)
        game->dda.texX = 64 - game->dda.texX - 1;
    else if (game->dda.hitSide == 1 && game->dda.rayDir.y < 0)
        game->dda.texX = 64 - game->dda.texX - 1;
    game->dda.texStep = 1.0 * 64 / game->image.sizeLine;
    game->dda.texPos = (game->image.lineStart - game->size_y / 2 + game->image.sizeLine / 2) * game->dda.texStep;
}

static void ft_apply_texture(t_game *game, int *yPos, char type, char *data)
{
    int imgPos;
    int dataPos;
    char *img_data;

    img_data = NULL;
    img_data = ft_get_data_img(game, type, 0);
    ft_get_position(game);
    while (*yPos < game->image.lineEnd)
    {
        game->dda.texY = (int)game->dda.texPos & (64 - 1);
        game->dda.texPos += game->dda.texStep;
        dataPos = *yPos * 4;
        imgPos = (game->dda.texX + 64 * game->dda.texY) * 4;
        data[dataPos] = img_data[imgPos];   
        data[dataPos + 1] = img_data[imgPos + 1];
        data[dataPos + 2] = img_data[imgPos + 2];
        data[dataPos + 3] = img_data[imgPos + 3];
        *yPos += 1;
    }
}

static void ft_apply_ceiling_floor(t_game *game, int pos, char type, char *data)
{
    int newPos;

    newPos = pos * 4;
    if (type == 'F')
    {
        data[newPos] = game->map.floor[2];
        data[++newPos] = game->map.floor[1];
        data[++newPos] = game->map.floor[0];
    }
    else
    {
        data[newPos] = game->map.ceiling[2];
        data[++newPos] = game->map.ceiling[1];
        data[++newPos] = game->map.ceiling[0];
    }
    data[++newPos] = 0;
}
char* ft_get_data_img(t_game *game, char type, int pixel)
{
    int bpp;
    int size_line;
    int endian;
    char *data;

    data = NULL;
    if (type == 'E')
        data = mlx_get_data_addr(game->image.img_e, &bpp, &size_line, &endian);
    else if (type == 'N')
        data = mlx_get_data_addr(game->image.img_n, &bpp, &size_line, &endian);
    else if (type == 'S')
        data = mlx_get_data_addr(game->image.img_s, &bpp, &size_line, &endian);
    else if (type == 'W')
        data = mlx_get_data_addr(game->image.img_w, &bpp, &size_line, &endian);
    else
        data = mlx_get_data_addr(game->image.columns[pixel], &bpp, &size_line, &endian);
    return (data);
}

void ft_paint_column(t_game *game, int y, char *data_columns)
{
    while (++y < game->size_y)
    {
        if (y >= game->image.lineStart && y <= game->image.lineEnd)
        {
            if (game->dda.hitSide == 1 && game->dda.rayDir.y < 0)
                ft_apply_texture(game, &y, 'S', data_columns);
            else if (game->dda.hitSide == 1)
                ft_apply_texture(game, &y, 'N', data_columns);
            else if (game->dda.hitSide == 0 && game->dda.rayDir.x < 0)
                ft_apply_texture(game, &y, 'W', data_columns);
            else
                ft_apply_texture(game, &y, 'E', data_columns);
        }
        else
        {
            if (y < (game->size_y / 2))
                ft_apply_ceiling_floor(game, y, 'C', data_columns);
            else
                ft_apply_ceiling_floor(game, y, 'F', data_columns);
        }
    }
}
