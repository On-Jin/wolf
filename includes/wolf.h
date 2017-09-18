/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:48:56 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/18 18:17:08 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#include "../libft/includes/libft.h"
#include "../libmlxji/includes/mlxji.h"
#include <stdio.h> ////////////
#include "mlx.h"
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define B_VOID '0'
# define B_WALL '1'

# define SIZE_REALLOC_MAP 10

typedef struct	s_map
{
	char		**map;
	int			len_x;
	int			len_y;

}				t_map;

typedef struct	s_fvector2d
{
	float			x;
	float			y;
}				t_fvector2d;

typedef struct	s_ivector2d
{
	int			x;
	int			y;
}				t_ivector2d;

typedef struct	s_ray
{
	t_map		*map;
	t_fvector2d	dir;

	float		dist_wall;
	t_fvector2d	end;
	t_fvector2d	start;
	int			hit;

	t_fvector2d	delta_len;
	t_fvector2d	len;
	int			step_x;
	int			step_y;
	int			side;
	t_ivector2d	pos_map;
}				t_ray;

typedef struct	s_player
{
	int				cart_pos_y;
	int				cart_pos_x;
	float			pos_y;
	float			pos_x;
	float			dir_y;
	float			dir_x;
	float			plan_x;
	float			plan_y;
	float			angle;
	float			move_speed;
	float			rotate_speed;
	float			jump;
	int				len_screen;
}				t_player;

typedef struct	s_radar
{
	int			len_tile;
	int			len_tile_fs;
	int			len_x;
	int			len_y;
}				t_radar;

typedef struct	s_fps
{
	struct timeval	step;
	struct timeval	cur;
	int				fps;
	int				ret_fps;
}				t_fps;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_px		col;
	int			flag;

	int			height;
	int			width;

	int			key[269];

	t_fps		fps;
	t_map		map;
	t_radar		radar;
	t_player	player;
	int			size_side;
	int			size_half_side;
}				t_env;

int				loop(t_env *e);

void			update_key_event(t_env *e);

void			move_player(t_env *e, int dir);

int				end_of_program(t_env *e, char *str);
int				event_key_on(int keycode, t_env *e);
int				event_key_off(int keycode, t_env *e);

void			radar(t_env *e);
void			radar_full_screen(t_env *e);
void			raycast_wolf(t_env *e, t_player *player);

int				raycast(t_ray *ray, t_map *map, t_fvector2d start, t_fvector2d dir);
void			init_raycast(t_ray *ray, t_map *map, t_fvector2d start, t_fvector2d dir);

int				round_to_inf(float nb);
int				round_to_up(float nb);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
void			mlxji_draw_case(t_img *img, t_pxtopx *px, t_px *col);
void			vector_rotation(float *x, float *y, float rotation);
#endif
