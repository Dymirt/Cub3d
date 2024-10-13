/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_down_clours.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:23:51 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/13 14:06:09 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb);

int	set_up_down_clours(t_data *data, char *key, char *value)
{
	if (ft_strncmp(key, "F", 1) == 0)
	{
		if (data->texinfo.floor)
			return (err_msg(NULL, "Floor color already set", 0));
		data->texinfo.floor = set_rgb_colors(ft_strchr(value, 'F') + 1);
	}
	else if (ft_strncmp(key, "C", 1) == 0)
	{
		if (data->texinfo.ceiling)
			return (err_msg(NULL, "Ceiling color already set", 0));
		data->texinfo.ceiling = set_rgb_colors(ft_strchr(value, 'C') + 1);
	}
	return (1);
}

int	*set_rgb_colors(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_2d_array((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		err_msg(NULL, "Malloc: error", 0);
		return (0);
	}
	return (copy_into_rgb_array(rgb_to_convert, rgb));
}

static int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1 || no_digit(rgb_to_convert[i]) == true)
		{
			free_2d_array((void **)rgb_to_convert);
			free(rgb);
			return (0);
		}
	}
	free_2d_array((void **)rgb_to_convert);
	return (rgb);
}
