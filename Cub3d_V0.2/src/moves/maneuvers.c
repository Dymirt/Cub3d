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

// Single function to handle all movement and rotation and jump (jump still need fixation)
int	move_player(t_data *data)
{
	double new_x;
	double new_y;
	int moved = 0;

	// Handle Jumping
	if (data->player.is_jumping)
	{
		data->player.z += data->player.z_vel;
		data->player.z_vel += GRAVITY;
		if (data->player.z <= 0) // Stop jumping when back on the ground
		{
			data->player.z = 0;
			data->player.is_jumping = 0;
			data->player.z_vel = 0;
		}
	}
	if (data->player.move_y != 0)
	{
		new_x = data->player.pos_x + data->player.dir_x * data->player.move_y * MOVESPEED;
		new_y = data->player.pos_y + data->player.dir_y * data->player.move_y * MOVESPEED;
		moved += validate_move(data, new_x, new_y);
	}
	if (data->player.move_x != 0)
	{
		new_x = data->player.pos_x + data->player.dir_y * data->player.move_x * MOVESPEED;
		new_y = data->player.pos_y - data->player.dir_x * data->player.move_x * MOVESPEED;
		moved += validate_move(data, new_x, new_y);
	}
	if (data->player.rotate != 0)
		moved += rotate_player(data, data->player.rotate);

	return moved;
}

void	handle_jump(t_data *data)
{
	if (!data->player.is_jumping && data->player.z == 0)
	{
		data->player.is_jumping = 1;
		data->player.z_vel = JUMP_SPEED;  // Initial jump velocity
	}
}



