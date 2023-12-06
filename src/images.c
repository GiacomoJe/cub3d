/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:27:33 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/11/07 13:14:55 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char *ft_swap_path_aux(char *new, char *old, char *c)
{
	char	*aux;

	aux = NULL;
	new = ft_strtrim(old, c);
	if (old != NULL)
		free(old);
	aux = ft_strtrim(new, "\r");
	free(new);
	return (aux);
}

static void	ft_validate_path_texture(t_map *map)
{
	char	*aux;

	aux = "";
	if (ft_strrchr(map->path_EA, '\n') != NULL)
		map->path_EA = ft_swap_path_aux(aux, map->path_EA, "\n");
	if (ft_strrchr(map->path_NO, '\n') != NULL)
		map->path_NO = ft_swap_path_aux(aux, map->path_NO, "\n");
	if (ft_strrchr(map->path_SO, '\n') != NULL)
		map->path_SO = ft_swap_path_aux(aux, map->path_SO, "\n");
	if (ft_strrchr(map->path_WE, '\n') != NULL)
		map->path_WE = ft_swap_path_aux(aux, map->path_WE, "\n");
}
void checkTextures(t_game *game)
{
	if (game->image.img_w == NULL)
		game->check = INVALID_TEXTURE_WE;
	if (game->image.img_e == NULL)
		game->check = INVALID_TEXTURE_EA;
	if (game->image.img_s == NULL)
		game->check = INVALID_TEXTURE_SO;
	if (game->image.img_n == NULL)
		game->check = INVALID_TEXTURE_NO;
}

// void	error_msg(int check)
// {
// 	ft_printf("Error\n");
	
// }

int	ft_create_images(t_game *game)
{
	int	x;
	int	width;
	int	height;

	x = -1;
	if (game->size_x <= 0 || game->size_y <= 0)
		return (1);
	else if (game->map.col_map <= 0 || game->map.row_map <= 0)
		return (1);
	width = 64;
	height = 64;
	ft_validate_path_texture(&game->map);
	game->image.columns = malloc(game->size_x * sizeof(void *));
	while (++x < game->size_x)
		game->image.columns[x] = mlx_new_image(game->init, 1, game->size_x);
	game->image.img_w = mlx_xpm_file_to_image(game->init, game->map.path_WE, &width, &height);
	game->image.img_n = mlx_xpm_file_to_image(game->init, game->map.path_NO, &width, &height);
	game->image.img_s = mlx_xpm_file_to_image(game->init, game->map.path_SO, &width, &height);
	game->image.img_e = mlx_xpm_file_to_image(game->init, game->map.path_EA, &width, &height);
	checkTextures(game);
	if(game->check)
		showError(game->check, game);
	if (game->image.img_w == NULL || game->image.img_e == NULL || game->image.img_s == NULL || game->image.img_n == NULL)
		return (ft_close(game));
	return (0);
}
