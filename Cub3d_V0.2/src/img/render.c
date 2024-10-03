/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:35:24 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/02 23:17:58 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->tex_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->tex_pixels[y][x]);
	else if (y < data->win_h / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else if (y < data->win_h -1)
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

static void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->win_w, data->win_h);
	y = 0;
	while (y < data->win_h)
	{
		x = 0;
		while (x < data->win_w)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

void	render_images(t_data *data)
{
	init_texture_pixels(data);
	ray_init(&data->ray);
	raycasting(&data->player, data);
	render_frame(data);
}

int	render(t_data *data)
{
	data->player.has_moved += move_player(data);
	render_images(data);
	return (0);
}
