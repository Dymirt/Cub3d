/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartData.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 01:53:10 by maabdela          #+#    #+#             */
/*   Updated: 2024/10/13 01:52:50 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	start_engin1(t_player *player, t_map_information *mapinfo)
{
	player->dir = '\0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->has_moved = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
	mapinfo->height = 0;
	mapinfo->width = 0;
	mapinfo->file = NULL;
}

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->end = 0;
}

void	ray_init(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	data_init(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->win_h = WIN_HEIGHT;
	data->win_w = WIN_WIDTH;
	start_engin1(&data->player, &data->map_info);
	init_texinfo(&data->texinfo);
	data->map = NULL;
	data->tex_pixels = NULL;
	data->tex = NULL;
}
