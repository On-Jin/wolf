/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_aff_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 20:55:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 20:55:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	raycast_aff_floor(t_env *e, int nb_cast, int start)
{
	t_pxtopx	to;

	to.x1 = nb_cast + 1;
	to.y1 = start - 1;
	to.y2 = e->height - 1;
	mlxji_draw_y_line(e->img, &to, 0);
}
