

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
	if (key == XK_a)
		data->player.move_x = -1;
	if (key == XK_s)
		data->player.move_y = -1;
	if (key == XK_d)
		data->player.move_x = 1;
	//if (key == XK_space)
		//handle_jump(data); 
	return (0);
}

static int	key_release_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_w && data->player.move_y == 1)
		data->player.move_y = 0;
	if (key == XK_s && data->player.move_y == -1)
		data->player.move_y = 0;
	if (key == XK_a && data->player.move_x == -1)
		data->player.move_x += 1;
	if (key == XK_d && data->player.move_x == 1)
		data->player.move_x -= 1;
	if (key == XK_Left)
		data->player.rotate = 0;
	if (key == XK_Right)
		data->player.rotate = 0;
	
	return (0);
}

static bool validate_next_move(t_data *data, double x, double y)
{
	if (data->map[(int)y][(int)x] == '0')//zero so means free sapce (valid move)
		return (true);
	if (x < 0.25 || x >= data->map_info.width - 1.25)
		return (false);
	if (y < 0.25 || y >= data->map_info.height - 0.25)
		return (false);
	return (true);
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
	return (moved);
}
