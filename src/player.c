/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 08:18:24 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/11/23 16:57:54 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void ft_start_moves_player(t_player *player)
{
    player->up = 0;
    player->down = 0;
    player->left = 0;
    player->right = 0;
    player->camRight = 0;
    player->camLeft = 0;
}
static void ft_get_rot(t_player *player, char direction)
{
    if (direction == 'N')
        player->rotationAngle =  M_PI * 3 / 2;
    else if (direction == 'S')
        player->rotationAngle =  M_PI / 2;
    else if (direction == 'E')
        player->rotationAngle =  M_PI;
    else
        player->rotationAngle =  M_PI * 2;
}

static void ft_get_dir(t_player *player, char direction)
{
    if (direction == 'N')
        player->dir = ft_gen_vector(0, -1);
    else if (direction == 'S')
        player->dir = ft_gen_vector(0, 1);
    else if (direction == 'E')
        player->dir = ft_gen_vector(-1, 0);
    else
        player->dir = ft_gen_vector(1, 0);
    if (direction == 'N')
		player->angCam = ft_gen_vector(0.66, 0);
    else if (direction == 'S')
        player->angCam = ft_gen_vector(-0.66, 0);
    else if (direction == 'E')
        player->angCam = ft_gen_vector(0, -0.66);
    else
        player->angCam = ft_gen_vector(0, 0.66);
}

void ft_start_player_cords(t_player *player, char **map)
{
    int y;
    int x;

    y = -1;
    ft_start_moves_player(player);
    while (map[++y] != NULL)
    {
        x = -1;
        while (map[y][++x] != '\0')
        {
			// printf("%c", map[y][x]);
            if (ft_strchr("NWSE", map[y][x]) != NULL)
            {
                player->pos = ft_gen_vector(x + 0.5, y + 0.5);
                ft_get_dir(player, map[y][x]);
				ft_get_rot(player, map[y][x]);
				return ;
            }
			// if(map[y][x] == "\n")
			// 	player->map_row++;
        }
    }
}

int ft_key_press(int key, t_game *game)
{
	// printf("%d\n", key);
    if (key == 13)
        game->player.up = 1;
    if (key == 1)
        game->player.down = 1;
    if (key == 0)
        game->player.left = 1;
    if (key == 2)
        game->player.right = 1;
    if (key == 123)
        game->player.camLeft = 1;
    if (key == 124)
        game->player.camRight = 1;
    if (key == 65307)
		ft_close(game);
	return (0);
}

int ft_key_release(int key, t_game *game)
{
    if (key == 13)
        game->player.up = 0;
    if (key == 1)
        game->player.down = 0;
    if (key == 0)
        game->player.left = 0;
    if (key == 2)
        game->player.right = 0;
    if (key == 123)
        game->player.camLeft = 0;
    if (key == 124)
        game->player.camRight = 0;
    return (0);
}
