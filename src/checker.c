/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:28:18 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/10/16 16:19:09 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	ft_file_reading(char **line, int fd, char ret)
{
	char	*aux;

	aux = ft_strtrim(*line, " ");
	while (aux != NULL && ft_strlen(aux) <= 2)
	{
		free(*line);
		free(aux);
		*line = get_next_line(fd);
		aux = ft_strtrim(*line, " ");
	}
	if (ft_strchr("NSWE", aux[0]) != NULL)
	{
		if (!ft_strnstr(aux, "NO ", 3) || !ft_strnstr(aux, "SO ", 3) || !ft_strnstr(aux, "WE ", 3) || !ft_strnstr(aux, "EA ", 3))
			ret = 'T';
	}
	else if (ft_strchr("CF", aux[0]) != NULL)
	{
		if (!ft_strnstr(aux, "F ", 2) || !ft_strnstr(aux, "C ", 2))
			ret = 'C';
	}
	free(aux);
	return (ret);
}
void	checkFile(t_game *game, int fd, int argc, char **argv)
{
	if(argc != 2)
		game->check = INVALID_ARGS;
	else if ((argc == 2 && ft_strnstr(argv[1], ".cub\0", ft_strlen(argv[1])) == NULL))
		game->check = INVALID_EXTENSION;
	else if (fd == -1)
		game->check = FILE_NOT_FOUNDED;
}

int check_colors(t_game *game)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if(game->map.ceiling[i] > 255 || game->map.floor[i] > 255
			|| game->map.ceiling[i] < 0 || game->map.floor[i] < 0)
			return (INVALID_COLORS);
		i++;
	}
	return (0);
}

void	ft_checker(t_game *game, int argc, char **argv)
{
	int		fd;
	char	*line;

	game->check = 0;
	fd = open(argv[1], O_RDONLY);
	checkFile(game, fd, argc, argv);
	if(game->check)
		showError(game->check, game);
	line = get_next_line(fd);
	while (line != NULL && game->check == 0)
	{
		if (game->map.n_texture < 4 && ft_file_reading(&line, fd, 'N') == 'T')
			game->check = ft_get_textures(&game->map, &game->map.n_texture, &line, fd);
		else if (game->map.n_texture <= 4 && game->map.n_colors < 2 && ft_file_reading(&line, fd, 'N') == 'C')
			game->check = ft_get_colors(&game->map, &game->map.n_colors, &line, fd);
		else if (game->map.n_texture == 4 && game->map.n_colors == 2)
			game->check = ft_get_map_plan(&game->map, &line, fd);
		else
			game->check = 1;
	}
	game->check = check_colors(game);
	if(game->map.n_texture < 4)
		game->check = INVALID_TEXTURE;
	free(line);
	if (game->check)
		showError(game->check, game);
	ft_init(game);
}

int	ft_get_map_plan(t_map *map, char **line, int fd)
{
	int		col;
	int		row;
	char	*aux;

	col = 0;
	row = 0;
	aux = NULL;
	int i = -1;
	while (*line)
	{
		*line = ft_clear_line(*line);
		if (ft_check_map_char(*line) == 1)
			return (1);
		if (ft_strrchr(*line, '\n') != NULL && (int)(ft_strlen(*line) - 1) > col)
			col = (ft_strlen(*line) - 1);
		else if (ft_strrchr(*line, '\n') == NULL && (int)ft_strlen(*line) > col)
			col = ft_strlen(*line);
		// printf("%s", *line);
		aux = ft_strjoin_mod(aux, *line);
		map->map_temp[row] = ft_calloc(col, sizeof(char));
		map->map_temp[row] = ft_strjoin_mod(map->map_temp[row], *line);
		free(*line);
		*line = get_next_line(fd);
		row++;
	}
	if (ft_fill_layout_map(map, aux, col, row) == 1)
		return (INVALID_MAP);
	if (ft_check_map_layout(map, row, col) == 1)
		return (INVALID_MAP);
	return (0);
}
