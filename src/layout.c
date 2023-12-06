/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:18:02 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/10/16 16:16:36 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_check_map_char(char *str)
{
	int	x;
	int	valid_obj;

	x = 0;
	valid_obj = 0;
	if (ft_strlen(str) < 3)
		return (1);
	while (str[x] != '\0')
	{
		if (str[x] == '\n' || str[x] == '\r')
		{
			x++;
			continue;
		}
		if (ft_strchr("01NSEW ", str[x]) == NULL)
			return (1);
		if (ft_strchr("01NSEW", str[x]) != NULL)
			valid_obj++;
		x++;
	}
	if (valid_obj == 0)
		return (1);
	return (0);
}

int	ft_fill_layout_map(t_map *map, char *str, int col, int row)
{
	int		r;
	int		c;
	char	**split;
	
	r = -1;
	str = ft_clear_line(str);
	map->map_plan = (char **)malloc(sizeof(char *) * (row + 1));
	split = ft_split(str, '\n');
	if (split == NULL)
		return (1);
	while (++r < row)
	{
		c = -1;
		map->map_plan[r] = (char *)malloc(sizeof(char) * (col + 1));
		while (++c < col)
		{
			if (c < (int)ft_strlen(split[r]) && split[r][c] != '\0')
				map->map_plan[r][c] = split[r][c];
			else
				map->map_plan[r][c] = ' ';
		}
		map->map_plan[r][c] = '\0';
	}
	map->map_plan[r] = NULL;
	ft_free_split(split);
	free(str);
	return (0);
}

static void	flood_fill(t_map *map, int r, int c, int *check)
{
    if (r < 0 || r >= map->row_map || c < 0 || c >= map->col_map)
        return ;
    if (map->map_plan[r][c] == ' ' || (((r == 0 || r == (map->row_map - 1))
        || (c == 0 || c == (map->col_map - 1))) && map->map_plan[r][c] != '1'))
        *check = 1;
    if (*check == 1 || map->map_plan[r][c] == '1'
        || map->map_plan[r][c] == '+')
        return ;
    map->map_plan[r][c] = '+';
    flood_fill(map, (r + 1), c, check);
    flood_fill(map, (r - 1), c, check);
    flood_fill(map, r, (c + 1), check);
    flood_fill(map, r, (c - 1), check);
    return ;
}

int	ft_check_map_layout(t_map *map, int row, int col)
{
	int		r;
	int		c;
	int		check;
	char	pos;

	r = -1;
	check = 0;
	pos = '\0';
	map->row_map = row;
	map->col_map = col;
	while (map->map_plan[++r] != NULL)
	{
		c = -1;
		while (map->map_plan[r][++c] != '\0')
		{
			if (ft_strchr("NSWE", map->map_plan[r][c]) != NULL)
			{
				pos = map->map_plan[r][c];
				flood_fill(map, r, c, &check);
				map->map_plan[r][c] = pos;
				break;
			}
		}
	}
	return (check);
}
