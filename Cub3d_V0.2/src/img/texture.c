/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:20:17 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/13 16:58:04 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_pixels(t_data *data)
{
	int	i;

	if (data->tex_pixels)
		free_2d_array((void **)data->tex_pixels);
	data->tex_pixels = ft_calloc(data->win_h + 1,
			sizeof * data->tex_pixels);
	if (!data->tex_pixels)
		clean_exit(data, err_msg(NULL, "Malloc: error", 1));
	i = 0;
	while (i < data->win_h)
	{
		data->tex_pixels[i] = ft_calloc(data->win_w + 1,
				sizeof * data->tex_pixels);
		if (!data->tex_pixels[i])
			clean_exit(data, err_msg(NULL, "Malloc: error", 1));
		i++;
	}
}

static void	get_texture_index(t_data *data, t_ray *ray)
{
	printf("ray->side: %d\n", ray->side);
	printf("ray->dir_x: %f\n", ray->dir_x);
	printf("ray->dir_y: %f\n", ray->dir_y);
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->texinfo.i = WEST;
		else
			data->texinfo.i = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->texinfo.i = SOUTH;
		else
			data->texinfo.i = NORTH;
	}
}

void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	int			y;
	int			color;

	get_texture_index(data, ray);
	tex->size = data->texinfo.sizes[tex->i];
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->position = (ray->draw_start - data->win_h / 2 + ray->line_height / 2)
		* tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->position & (tex->size - 1);
		tex->position += tex->step;
		color = data->tex[tex->i][tex->size * tex->y + tex->x];
		if (tex->i == NORTH || tex->i == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->tex_pixels[y][x] = color;
		y++;
	}
}
