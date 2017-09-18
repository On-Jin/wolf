/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 19:03:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/18 15:56:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_map(t_env *e, int len_tile)
{
	int 		x;
	int			y;
	t_pxtopx	to;
	t_px		col;

	col.r = 155;
	col.g = 20;
	col.b = 10;
	y = 0;
	while (y < e->map.len_y)
	{
		x = 0;
		while (x < e->map.len_x)
		{
			if (e->map.map[y][x] == '1')
			{
				to.x1 = x * len_tile;
				to.x2 = (x + 1) * len_tile;
				to.y1 = y * len_tile;
				to.y2 = (y + 1) * len_tile;
				if (to.x1 < e->width &&
					to.y1 < e->height)
					mlxji_draw_case(e->img, &to, &col);
			}
			x++;
		}
		y++;
	}
}

static void draw_fov(t_env *e, t_player *player, int len_tile)
{
	t_px col;
	t_pxtopx to;

	col.r = 0;
	col.g = 190;
	col.b = 25;
	to.x1 = (player->pos_x) * len_tile;
	to.y1 = (player->pos_y) * len_tile;
	to.x2 = (player->pos_x + player->dir_x + player->plan_x) * len_tile;
	to.y2 = (player->pos_y + player->dir_y + player->plan_y) * len_tile;
	mlxji_draw_line(e->img, &col, &to);
	to.x1 = (player->pos_x) * len_tile;
	to.y1 = (player->pos_y) * len_tile;
	to.x2 = (player->pos_x + player->dir_x - player->plan_x) * len_tile;
	to.y2 = (player->pos_y + player->dir_y - player->plan_y) * len_tile;
	mlxji_draw_line(e->img, &col, &to);
}

static void draw_vector_dir(t_env *e, t_player *player, int len_tile)
{
	t_px col;
	t_pxtopx to;


	col.r = 255;
	col.g = 155;
	col.b = 20;
	to.x1 = player->pos_x * len_tile;
	to.y1 = player->pos_y * len_tile;
	to.x2 = (player->pos_x + player->dir_x) * len_tile;
	to.y2 = (player->pos_y + player->dir_y) * len_tile;
	mlxji_draw_line(e->img, &col, &to);
}

static void draw_pos_player(t_env *e, t_player *player, int len_tile)
{
	int coef;
	t_px col;
	t_pxtopx to;

	col.r = 20;
	col.g = 155;
	col.b = 255;
	coef = (int)(player->pos_x * 100) % 100;
	to.x1 = (int)player->pos_x * len_tile + (len_tile * coef / 100) - len_tile / 5;
	to.x2 = (int)player->pos_x * len_tile + (len_tile * coef / 100) + len_tile / 5;
	coef = (int)(player->pos_y * 100) % 100;
	to.y1 = (int)player->pos_y * len_tile + (len_tile * coef / 100) - len_tile / 5;
	to.y2 = (int)player->pos_y * len_tile + (len_tile * coef / 100) + len_tile / 5;
	mlxji_draw_case(e->img, &to, &col);
}

void	radar_full_screen(t_env *e)
{
	t_radar *radar;

	radar = &e->radar;
	draw_map(e, radar->len_tile_fs);
	draw_pos_player(e, &e->player, radar->len_tile_fs);
	draw_fov(e, &e->player, radar->len_tile_fs);
	draw_vector_dir(e, &e->player, radar->len_tile_fs);
}

void	radar(t_env *e)
{
	t_radar *radar;

	radar = &e->radar;
	draw_map(e, radar->len_tile);
	draw_pos_player(e, &e->player, radar->len_tile);
	draw_fov(e, &e->player, radar->len_tile);
	draw_vector_dir(e, &e->player, radar->len_tile);
}
