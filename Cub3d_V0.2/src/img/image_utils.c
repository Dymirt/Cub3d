/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:56:42 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/03 01:21:25 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*by checking the X and Y fall within the image size constrainys 
Win_width and win_hight we making such that the coordinates are vailed 
before accessing the pixel data

and this makes  the renderening of texture smother 
and reduce the delays whike movement*/
void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel_index;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	pixel_index = y * (image->size_line / 4) + x;
	image->addr[pixel_index] = color;
}

void	set_default_ray_info(t_ray *ray)
{
	ray->map_x = 0;
	ray->map_y = 0;
	ray->deltadist_x = 0.0;
	ray->deltadist_y = 0.0;
}

// Calculate the camera position based on the current x-coordinate
double	calculate_camera_x(int x)
{
	return ((2 * x / (double)WIN_WIDTH) - 1);
}

// Calculate the ray direction based on player position and camera position
void	calculate_ray_direction(t_ray *ray, t_player *player, double camera_x)
{
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
}

bool	is_within_bounds(t_ray *ray, t_data *data)
{
	return (ray->map_x >= 0 && ray->map_x < data->map_info.width
		&& ray->map_y >= 0 && ray->map_y < data->map_info.height);
}
