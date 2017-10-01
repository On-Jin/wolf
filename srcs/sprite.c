/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:39:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/01 17:56:47 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** len_pp_x = len_per_pixel for one x / len_sprite_x
** len_pp_y
*/

static void	sprite_init_tool(t_env *e, t_sprite *sprite, t_ts *ts)
{
	ts->len_sprite_x = sprite->len_x / sprite->dist;
	ts->len_sprite_y = sprite->len_y / sprite->dist;
	e->to.x1 = (sprite->col - (ts->len_sprite_x >> 1));
	e->to.x2 = (sprite->col + (ts->len_sprite_x >> 1));
	e->to.y1 = (e->size_half_side - (ts->len_sprite_y >> 1));
	e->to.y2 = (e->size_half_side + (ts->len_sprite_y >> 1));
	if (e->to.x2 >= e->width)
		e->to.x2 = e->width - 1;
	if (e->to.y1 < 0)
		e->to.y1 = 0;
	e->to.y2 = e->to.y1;
	ts->len_y = 0;
	ts->x = 0;
	ts->start_y = e->to.y1;
	ts->len_pp_y = (float)ts->len_sprite_y / sprite->len_y;
	ts->len_pp_x = (float)sprite->len_x / ts->len_sprite_x;
}

static void	loop_w(t_env *e, t_sprite *sprite, t_ts *ts)
{
	while (e->to.x1 < e->to.x2)
	{
		if (e->to.x1 >= 0 && sprite->dist < e->dist[e->to.x1])
		{
			ts->i = 0;
			ts->len_y = 0;
			e->to.y2 = ts->start_y;
			while (ts->len_y < ts->len_sprite_y)
			{
				e->to.y1 = e->to.y2;
				e->to.y2 = ts->start_y + ts->len_y;
				if (e->to.y2 >= e->height)
					break ;
				ts->col = *((int *)&sprite->sprite[((int)ts->x << 2) +
						ts->i * (sprite->len_x << 2)]);
				if (ts->col != 0xFFFFFF)
				mlxji_draw_y_line(e->img, &e->to, ts->col);
				ts->len_y += ts->len_pp_y;
				ts->i++;
			}
		}
		e->to.x1++;
		ts->x += ts->len_pp_x;
	}
}

void		sprite_wolf(t_env *e, t_sprite *sprite)
{
	t_ts ts;

	if (!sprite->hit)
		return ;
	sprite_init_tool(e, sprite, &ts);
	loop_w(e, sprite, &ts);
}
