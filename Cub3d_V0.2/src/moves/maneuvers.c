/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maneuvers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 01:53:10 by maabdela          #+#    #+#             */
/*   Updated: 2024/10/06 21:43:00 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rotate_left_right(t_data *data, double rotspeed)
{
	t_player	*p;
	double		tmp_x;

	p = &data->player;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp_x * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
	return (1);
}

int	rotate_player(t_data *data, double rotdir)
{
	int		moved;
	double	rotspeed;

	moved = 0;
	rotspeed = ROTSPEED * rotdir;
	moved += rotate_left_right(data, rotspeed);
	return (moved);
}

int	move_player(t_data *data)
{
	double	new_x;
	double	new_y;
	int		moved;

	moved = 0;
	if (data->player.move_y != 0)
	{
		new_x = data->player.pos_x + data->player.dir_x
			* data->player.move_y * MOVESPEED;
		new_y = data->player.pos_y + data->player.dir_y
			* data->player.move_y * MOVESPEED;
	}
	if (data->player.move_x != 0)
	{
		new_x = data->player.pos_x + data->player.dir_y
			* data->player.move_x * MOVESPEED;
		new_y = data->player.pos_y - data->player.dir_x
			* data->player.move_x * MOVESPEED;
	}
	if (data->player.move_x != 0 || data->player.move_y != 0)
		moved += validate_move(data, new_x, new_y);
	if (data->player.rotate != 0)
		moved += rotate_player(data, data->player.rotate);
	return (moved);
}
