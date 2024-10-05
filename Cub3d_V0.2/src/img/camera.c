/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:22:25 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/05 01:02:46 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycasting_info(int x, t_ray *ray, t_player *player)
{
	double	camera_x;

	ray_init(ray);
	set_default_ray_info(ray);
	camera_x = calculate_camera_x(x);
	calculate_ray_direction(ray, player, camera_x);
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->dir_x != 0)
		ray->deltadist_x = fabs(1 / ray->dir_x);
	else
		ray->deltadist_x = LARGE_VALUE;
	if (ray->dir_y != 0)
		ray->deltadist_y = fabs(1 / ray->dir_y);
	else
		ray->deltadist_y = LARGE_VALUE;
}

static void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	if (ray->dir_x < 0)
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	else
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	if (ray->dir_y < 0)
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	else
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
}

/*
- Implementing the DDA algorithm:
- The loop will increment 1 square until we hit a wall.
- If sidedist_x < sidedist_y, x is the closest point from the ray.
*/

static void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = X_DIR;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = Y_DIR;
		}
		if (!is_within_bounds(ray, data))
			break ;
		if (data->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

static void	calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
	if (ray->side == X_DIR)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(data->win_h / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + data->win_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_h / 2;
	if (ray->draw_end >= data->win_h)
		ray->draw_end = data->win_h - 1;
	if (ray->side == X_DIR)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

int	raycasting(t_player *player, t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = data->ray;
	while (x < data->win_w)
	{
		init_raycasting_info(x, &ray, player);
		set_dda(&ray, player);
		perform_dda(data, &ray);
		calculate_line_height(&ray, data, player);
		update_texture_pixels(data, &data->texinfo, &ray, x);
		x++;
	}
	return (SUCCESS);
}
