/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:49:23 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/11/23 10:54:17 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_init(t_game *game)
{
	game->init = mlx_init();
	ft_start_player_cords(&game->player, game->map.map_plan);
	game->size_x = 1280;
	game->size_y = 720;
	// game->player.rotationAngle = M_PI * 3 / 2;
	game->win = mlx_new_window(game->init, game->size_x, game->size_y, "Cub3d");
	if (ft_create_images(game) == 1)
		return;
	mlx_hook(game->win, 2, 1L<<0, ft_key_press, game);
	mlx_hook(game->win, 3, 1L<<1, ft_key_release, game);
	mlx_loop_hook(game->init, ft_render, game);
	mlx_hook(game->win, 17, 0, ft_close, game);
	mlx_loop(game->init);
}
