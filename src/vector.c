/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:40:42 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/11/08 09:14:37 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector ft_gen_vector(double x, double y)
{
    t_vector v;

    v.x = x;
    v.y = y;
    return (v);
}

t_vector ft_mult_vector(t_vector v, double scale)
{
    t_vector new;

    new.x = v.x * scale;
    new.y = v.y * scale;
    return (new);
}

t_vector ft_add_vector(t_vector v1, t_vector v2)
{
    t_vector new;

    new.x = v1.x + v2.x;
    new.y = v1.y + v2.y;
    return (new);
}

t_vector ft_rotate_point(t_vector v, double angle)
{
    t_vector new;

    new.x = v.x * cos(angle) - v.y * sin(angle);
    new.y = v.x * sin(angle) + v.y * cos(angle);

    return (new);
}
