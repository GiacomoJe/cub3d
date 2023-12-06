/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:32:41 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/11/23 13:46:42 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int ft_collision_wall(t_game *game, double posX, double posY)
{
	int			frame;
	t_vector	diffPos;
	t_vector	newPos;

	frame = 0;
	diffPos = ft_gen_vector((posX - game->player.pos.x) / 60, (posY - game->player.pos.y) / 60);
	newPos = ft_gen_vector(0.0, 0.0);
	while (frame <= (60 * 3))
	{
		if (frame % 3 == 0)
		{
			newPos.x = game->player.pos.x + (diffPos.x * 60000);
			newPos.y = game->player.pos.y + (diffPos.y * 60000);
			if (game->map.map_plan[(int)newPos.y][(int)newPos.x] == '1')
				return (1);
			game->player.pos.x += diffPos.x;
			game->player.pos.y += diffPos.y;
		}
		frame++;
	}
	return (0);
}

static int ft_left_right(t_game *game, double direction, int mult)
{
	t_vector	newPos;
	t_vector	strafe;

	strafe = ft_rotate_point(game->player.dir, (mult * (M_PI / 2)));
	strafe = ft_mult_vector(strafe, direction);
	newPos = ft_add_vector(game->player.pos, strafe);
	if (ft_collision_wall(game, newPos.x, newPos.y) == 1)
		return (1);
	return (0);
}

static int ft_up_down(t_game *game, double direction, int mult)
{
	double posX;
	double posY;

	posX = game->player.pos.x + (mult * (game->player.dir.x * direction));
	posY = game->player.pos.y + (mult * (game->player.dir.y * direction));
	if (ft_collision_wall(game, posX, posY) == 1)
		return (1);
	return (0);
}

static void ft_move_cam(t_game *game, double rotate_value, int aux)
{
	game->player.rotationAngle += aux * rotate_value;
	game->player.dir = ft_rotate_point(game->player.dir, (rotate_value * aux));
	game->player.angCam = ft_rotate_point(game->player.angCam, (rotate_value * aux));
}

int	ft_move_dir(t_game *game)
{
	int		ret;
	double	distance;

	ret = 0;
	distance = 0.00005;
	if (game->player.up == 1)
		ret = ft_up_down(game, distance, 1);
	if (game->player.down == 1)
		ret = ft_up_down(game, distance * (1 - 0.5), -1);
	if (game->player.left == 1)
		ret = ft_left_right(game, distance * (1 - 0.35), -1);
	if (game->player.right == 1)
		ret = ft_left_right(game, distance * (1 - 0.35), 1);
	if (game->player.camLeft == 1)
		ft_move_cam(game, (distance * (1 - 0.45) * (1.0 / sqrt(game->dda.perpendicularDist))), -1);
	if (game->player.camRight == 1)
		ft_move_cam(game, (distance * (1 - 0.45) * (1.0 / sqrt(game->dda.perpendicularDist))), 1);
	return (ret);
}
