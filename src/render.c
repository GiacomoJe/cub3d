/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:48:55 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/11/16 08:47:48 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void ft_third_step(t_game *game)
{
    game->dda.hit = 0;
    while (game->dda.hit == 0)
    {
        if (game->dda.distSide.x < game->dda.distSide.y)
        {
            game->dda.distSide.x += game->dda.deltaDist.x;
            game->dda.mapPos.x += game->dda.step.x;
            game->dda.hitSide = 0;
        }
        else
        {
            game->dda.distSide.y += game->dda.deltaDist.y;
            game->dda.mapPos.y += game->dda.step.y;
            game->dda.hitSide = 1;
        }
        if (game->map.map_plan[(int)game->dda.mapPos.y][(int)game->dda.mapPos.x] == '1')
            game->dda.hit = 1;
    }
}

static void ft_second_step(t_game *game)
{
    if (game->dda.rayDir.x < 0)
    {
        game->dda.distSide.x = (game->player.pos.x - game->dda.mapPos.x) * game->dda.deltaDist.x;
        game->dda.step.x = -1;
    }
    else
    {
        game->dda.distSide.x = (game->dda.mapPos.x + 1.0 - game->player.pos.x) * game->dda.deltaDist.x;
        game->dda.step.x = 1;
    }
    if (game->dda.rayDir.y < 0)
    {
        game->dda.distSide.y = (game->player.pos.y - game->dda.mapPos.y) * game->dda.deltaDist.y;
        game->dda.step.y = -1;
    }
    else
    {
        game->dda.distSide.y = (game->dda.mapPos.y + 1.0 - game->player.pos.y) * game->dda.deltaDist.y;
        game->dda.step.y = 1;
    }
}

static void ft_first_step(t_game *game, int pixelX)
{
    game->dda.mult = 2 * pixelX / (double)game->size_x - 1;
    if (game->dda.mult == 0)
        game->dda.mult = 0.000001;
    game->dda.camPixel = ft_mult_vector(game->player.angCam, game->dda.mult);
    game->dda.rayDir = ft_add_vector(game->player.dir, game->dda.camPixel);
    game->dda.mapPos = ft_gen_vector(floor(game->player.pos.x), floor(game->player.pos.y));
    if (game->dda.rayDir.x != 0 && game->dda.rayDir.y != 0)
        game->dda.deltaDist = ft_gen_vector(fabs(1 / game->dda.rayDir.x), fabs(1 / game->dda.rayDir.y));
    else
    {
        if (game->dda.rayDir.x == 0)
            game->dda.deltaDist = ft_gen_vector(1.0, 30.0);
        else
            game->dda.deltaDist = ft_gen_vector(30.0, 1.0);
    }
}

static void ft_create_column_apply(t_game *game, int pixelX)
{
    int y;
    char *data_columns;

    y = -1;
    data_columns = NULL;
    game->image.sizeLine = (int)(game->size_y / game->dda.perpendicularDist);
    game->image.lineStart = -game->image.sizeLine / 2 + game->size_y / 2;
    if (game->image.lineStart < 0)
        game->image.lineStart = 0;
    game->image.lineEnd = game->image.sizeLine / 2 + game->size_y / 2;
    if(game->image.lineEnd >= game->size_y)
      game->image.lineEnd = game->size_y - 1;
    data_columns = ft_get_data_img(game, 'C', pixelX);
    ft_paint_column(game, y, data_columns);
    mlx_put_image_to_window(game->init, game->win, game->image.columns[pixelX], pixelX, 0);
    ft_move_dir(game);
}

int ft_render(t_game *game)
{
    double pixelX;
	static int x = 0;

    pixelX = -1;
    while (++pixelX < game->size_x)
    {
        ft_first_step(game, pixelX);
        ft_second_step(game);
        ft_third_step(game);
        if (game->dda.hitSide == 0)
            game->dda.perpendicularDist = (game->dda.distSide.x - game->dda.deltaDist.x);
        else
            game->dda.perpendicularDist = (game->dda.distSide.y - game->dda.deltaDist.y);
        ft_create_column_apply(game, pixelX);
    }
	if(x == 0 || game->player.up || game->player.down || game->player.camLeft || game->player.camRight)
	{
		load_map(game);
		renderPlayer(game);
		x++;
	}
	mlx_put_image_to_window(game->init, game->win, game->image.map, 0, 0);
    return (1);
}
