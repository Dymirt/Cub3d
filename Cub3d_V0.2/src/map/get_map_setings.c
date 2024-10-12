/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_setings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:04:52 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/13 01:37:47 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_tex(char **str, char *line);
static void	load_map_to_struct(t_data *data, int i);
static int	set_textures(t_data *data, char *key, char *value);
static void	fill_spaces(t_data *data);

int	load_map_settings(t_data *data)
{
	size_t	i;
	char	**arr;

	i = 0;
	while (data->map_info.file[i] && (!data->texinfo.north
			|| !data->texinfo.south || !data->texinfo.west
			|| !data->texinfo.east || !data->texinfo.floor
			|| !data->texinfo.ceiling))
	{
		arr = ft_split(data->map_info.file[i], ' ');
		if (!set_textures(data, arr[0], arr[1]))
			return (0);
		if (!set_up_down_clours(data, arr[0], data->map_info.file[i]))
			return (0);
		free_2d_array((void **)arr);
		i++;
	}
	load_map_to_struct(data, i);
	return (1);
}

static void	load_map_to_struct(t_data *data, int i)
{
	size_t	j;
	size_t	map_len;
	size_t	len;

	j = 0;
	map_len = 0;
	data->map = ft_calloc(MAX_LINES, sizeof(char *));
	while (data->map_info.file[i])
	{
		len = ft_strlen(data->map_info.file[i]);
		if (len > map_len)
			map_len = len;
		data->map[j] = ft_strdup(data->map_info.file[i]);
		if (data->map[j][len - 1])
			data->map[j][len - 1] = '\0';
		i++;
		j++;
	}
	data->map[j] = NULL;
	data->map_info.height = j;
	data->map_info.width = map_len;
	fill_spaces(data);
}

static int	set_tex(char **str, char *line)
{
	size_t	len;

	if (*str == NULL)
	{
		len = ft_strlen(line);
		*str = ft_strdup(line);
		if ((*str)[len - 1] == '\n')
			(*str)[len - 1] = '\0';
		return (0);
	}
	return (1);
}

static int	set_textures(t_data *data, char *key, char *value)
{
	if (ft_strncmp(key, "NO", 2) == 0 && set_tex(&data->texinfo.north, value))
		return (err_msg(key, "Already set", 0));
	else if (ft_strncmp(key, "SO", 2) == 0
		&& set_tex(&data->texinfo.south, value))
		return (err_msg(key, "Already set", 0));
	else if (ft_strncmp(key, "WE", 2) == 0
		&& set_tex(&data->texinfo.west, value))
		return (err_msg(key, "Already set", 0));
	else if (ft_strncmp(key, "EA", 2) == 0
		&& set_tex(&data->texinfo.east, value))
		return (err_msg(key, "Already set", 0));
	return (1);
}

static void	fill_spaces(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
				data->map[i][j] = '1';
			j++;
		}
		i++;
	}
}
