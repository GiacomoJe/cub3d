/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:04:04 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/11/07 09:41:12 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void ft_clear_by_loop(t_game *game)
{
	int x;

	x = -1;
	while (++x < game->size_x)
		if (game->image.columns[x] != NULL)
			mlx_destroy_image(game->init, game->image.columns[x]);
	x = -1;
	while (game->map.map_plan[++x] != NULL)
		free(game->map.map_plan[x]);
	free(game->map.map_plan);	
}

static void ft_clear_windown(t_game *game)
{
	ft_clear_by_loop(game);
	if (game->image.columns != NULL)
		free(game->image.columns);
	if (game->map.floor != NULL)
		free(game->map.floor);
	if (game->map.ceiling != NULL)
		free(game->map.ceiling);
	if (game->map.path_EA != NULL)
		free(game->map.path_EA);
	if (game->map.path_NO != NULL)
		free(game->map.path_NO);
	if (game->map.path_SO != NULL)
		free(game->map.path_SO);
	if (game->map.path_WE != NULL)
		free(game->map.path_WE);
	if (game->image.img_w != NULL)
		mlx_destroy_image(game->init, game->image.img_w);
	if (game->image.img_n != NULL)
		mlx_destroy_image(game->init, game->image.img_n);
	if (game->image.img_s != NULL)
		mlx_destroy_image(game->init, game->image.img_s);
	if (game->image.img_e != NULL)
		mlx_destroy_image(game->init, game->image.img_e);
	mlx_clear_window(game->init, game->win);
	mlx_destroy_window(game->init, game->win);
	// mlx_destroy_display(game->init);
	free(game->init);
}

int ft_close(t_game *game)
{
	ft_clear_windown(game);
	exit(1);
}

char *ft_clear_line(char *line)
{
	char *aux;
	char *auxAscii13;

	aux = ft_strjoin_mod(line, "");
	auxAscii13 = "";
	if (ft_strrchr(aux, '\r') != NULL)
	{
		auxAscii13 = ft_strjoin_mod(ft_strtrim(aux, "\r"), auxAscii13);
		free(aux);
		aux = ft_strdup(auxAscii13);
	}
	if (auxAscii13 != NULL && ft_strlen(auxAscii13) > 0)
		free(auxAscii13);
	return (aux);
}
