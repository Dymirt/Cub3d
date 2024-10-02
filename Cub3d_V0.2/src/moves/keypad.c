/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 01:53:10 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/02 01:54:27 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_Left)
		data->player.rotate -= 1;
	if (key == XK_Right)
		data->player.rotate += 1;
	if (key == XK_w)
		data->player.move_y = 1;
	if (key == XK_d)
		data->player.move_x = -1;
	if (key == XK_s)
		data->player.move_y = -1;
	if (key == XK_a)
		data->player.move_x = 1;
	return (0);
}

static int	key_release_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_a || key == XK_d)
		data->player.move_x = 0;
	if (key == XK_w || key == XK_s)
		data->player.move_y = 0;
	if (key == XK_Left || key == XK_Right)
		data->player.rotate = 0;
	return (0);
}

static bool	validate_next_move(t_data *data, double x, double y)
{
    if (x < 0 || x >= data->map_info.width || y < 0 || y >= data->map_info.height)
        return (false);
    if (data->map[(int)y][(int)x] == '1') // Wall detected, disallow movement
        return (false);
    if (data->map[(int)y][(int)x] == '0')
        return (true);
    return (false);
}

void	listen_for_input(t_data *data)
{
	mlx_hook(data->win, ClientMessage, NoEventMask, quit_cub3d, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press_handler, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release_handler, data);
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
