/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 01:53:10 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/03 00:43:03 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press_handler(int key, t_data *data)
{
	if (key == XK_ESCAPE)
		quit_cub3d(data);
	if (key == XK_LEFT)
		data->player.rotate -= 1;
	if (key == XK_RIGHT)
		data->player.rotate += 1;
	if (key == XK_W)
		data->player.move_y = 1;
	if (key == XK_D)
		data->player.move_x = -1;
	if (key == XK_S)
		data->player.move_y = -1;
	if (key == XK_A)
		data->player.move_x = 1;
	return (0);
}

static int	key_release_handler(int key, t_data *data)
{
	if (key == XK_ESCAPE)
		quit_cub3d(data);
	if (key == XK_A || key == XK_D)
		data->player.move_x = 0;
	if (key == XK_W || key == XK_S)
		data->player.move_y = 0;
	if (key == XK_LEFT || key == XK_RIGHT)
		data->player.rotate = 0;
	return (0);
}

static bool	validate_next_move(t_data *data, double x, double y)
{
	if (x < 1.2 || x >= data->map_info.width - 2)
		return (false);
	if (y < 1.2 || y >= data->map_info.height - 2)
		return (false);
	if (data->map[(int)y][(int)x] == '1')
		return (false);
	if (data->map[(int)y][(int)x] == '0')
		return (true);
	return (false);
}

void	listen_for_input(t_data *data)
{
	mlx_hook(data->win, CLIENT_MESSAGE, NO_EVENT_MASK, quit_cub3d, data);
	mlx_hook(data->win, KEY_PRESS, KEY_PRESS_MASK, key_press_handler, data);
	mlx_hook(data->win, KEY_RELEASE,
		KEY_RELEASE_MASK, key_release_handler, data);
}

int	validate_move(t_data *data, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (validate_next_move(data, new_x, data->player.pos_y))
	{
		data->player.pos_x = new_x;
		moved = 1;
	}
	if (validate_next_move(data, data->player.pos_x, new_y))
	{
		data->player.pos_y = new_y;
		moved = 1;
	}
	printf("x: %f, y: %f\n", data->player.pos_x, data->player.pos_y);
	printf(GREEN "moved: %d\n" RESET, moved);
	return (moved);
}
