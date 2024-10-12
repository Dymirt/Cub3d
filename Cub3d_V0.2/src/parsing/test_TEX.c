/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_TEX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:44:24 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/13 01:43:10 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (err_msg_val(rgb[i], "RGB: error", FAILURE));
		i++;
	}
	return (SUCCESS);
}

int	fill_color_tex(t_data *data, t_texinfo *tex, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]))
		return (err_msg(data->map_info.path, "F: C: error", ERR));
	if (!tex->ceiling && line[j] == 'C')
	{
		tex->ceiling = set_rgb_colors(line + j + 1);
		if (tex->ceiling == 0)
			return (err_msg(data->map_info.path, "color: C", ERR));
	}
	else if (!tex->floor && line[j] == 'F')
	{
		tex->floor = set_rgb_colors(line + j + 1);
		if (tex->floor == 0)
			return (err_msg(data->map_info.path, "Color: F", ERR));
	}
	else
		return (err_msg(data->map_info.path, "F: C: error", ERR));
	return (SUCCESS);
}

int	check_textures_validity(t_data *data, t_texinfo *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (err_msg(data->map_info.path, "tex: error", FAILURE));
	if (!textures->floor || !textures->ceiling)
		return (err_msg(data->map_info.path, "color missing: error", FAILURE));
	if (!is_file_ext(textures->north, ".xpm")
		|| !is_file_ext(textures->south, ".xpm")
		|| !is_file_ext(textures->west, ".xpm")
		|| !is_file_ext(textures->east, ".xpm")
		|| check_valid_rgb(textures->floor) == FAILURE
		|| check_valid_rgb(textures->ceiling) == FAILURE)
		return (FAILURE);
	textures->hex_floor = convert_rgb_to_hex(textures->floor);
	textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	return (SUCCESS);
}
