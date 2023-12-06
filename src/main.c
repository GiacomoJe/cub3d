/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:45:16 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/10/31 13:08:27 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
	t_game game;

	load_errors(&game);
	game.map.n_texture = 0;
	game.map.n_colors = 0;
	game.time = 0;
	game.oldTime = 0;
	game.map.floor = ft_calloc(3, sizeof(int));
	game.map.ceiling = ft_calloc(3, sizeof(int));
	ft_checker(&game, argc, argv);
}
