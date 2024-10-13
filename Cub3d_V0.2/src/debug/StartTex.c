/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartTex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdela <maabdela@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 01:53:10 by maabdela          #+#    #+#             */
/*   Updated: 2024/10/02 01:54:27 by maabdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static int	*xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buff;
	int		x;
	int		y;

	data->texinfo.size = 0;
	init_textures_img(data, &tmp, path);
	buff = ft_calloc(1, sizeof(int) * data->texinfo.size * data->texinfo.size);
	if (!buff)
		clean_exit(data, err_msg(NULL, "Malloc: error", 1));
	y = 0;
	while (y < data->texinfo.size)
	{
		x = 0;
		while (x < data->texinfo.size)
		{
			buff[y * data->texinfo.size + x]
				= tmp.addr[y * data->texinfo.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buff);
}

void	start_mlxtex(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	data->tex = ft_calloc(5, sizeof * data->tex);
	if (!data->mlx)
		clean_exit(data, err_msg("mlx", "test", 1));
	if (!data->win)
		clean_exit(data, err_msg("mlx", "test", 1));
	if (!data->tex)
		clean_exit(data, err_msg(NULL, "Malloc: erro", 1));
	data->tex[NORTH] = xpm_to_img(data, data->texinfo.north);
	data->texinfo.sizes[NORTH] = data->texinfo.size;
	data->tex[SOUTH] = xpm_to_img(data, data->texinfo.south);
	data->texinfo.sizes[SOUTH] = data->texinfo.size;
	data->tex[EAST] = xpm_to_img(data, data->texinfo.east);
	data->texinfo.sizes[EAST] = data->texinfo.size;
	data->tex[WEST] = xpm_to_img(data, data->texinfo.west);
	data->texinfo.sizes[WEST] = data->texinfo.size;
	return ;
}

void	init_texinfo(t_texinfo *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->x = 0;
	textures->y = 0;
	textures->size = 0;
	textures->hex_floor = 0x0;
	textures->hex_ceiling = 0x0;
	textures->step = 0.0;
	textures->position = 0.0;
}

void	init_img(t_data *data, t_img *image, int w, int h)
{
	init_img_clean(image);
	image->img = mlx_new_image(data->mlx, w, h);
	if (image->img == NULL)
		clean_exit(data, err_msg("mlx", "MLX: image", 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->end);
	return ;
}

void	init_textures_img(t_data *data, t_img *image, char *path)
{
	init_img_clean(image);
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->texinfo.size,
			&data->texinfo.size);
	if (image->img == NULL)
		clean_exit(data, err_msg("mlx", "MLX: image", 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->end);
	return ;
}
