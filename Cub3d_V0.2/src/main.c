/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:16:41 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/06 21:34:34 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_number_of_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		err_msg(path, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

static void	fill_tab(t_data *data)
{
	char	*line;
	int		row;

	row = 0;
	line = get_next_line(data->map_info.fd);
	while (line != NULL)
	{
		data->map_info.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->map_info.file[row])
		{
			err_msg(NULL, "Malloc: erro", 0);
			return (free_2d_array((void **)data->map_info.file));
		}
		ft_strlcpy(data->map_info.file[row++], line, ft_strlen(line) + 1);
		free(line);
		line = get_next_line(data->map_info.fd);
	}
	data->map_info.file[row] = NULL;
}

void	parse_data(char *path, t_data *data)
{
	data->map_info.line_count = get_number_of_lines(path);
	data->map_info.path = path;
	data->map_info.file = ft_calloc(data->map_info.line_count \
			+ 1, sizeof(char *));
	if (!(data->map_info.file))
	{
		err_msg(NULL, "Malloc: error", 0);
		return ;
	}
	data->map_info.fd = open(path, O_RDONLY);
	if (data->map_info.fd < 0)
		err_msg(path, strerror(errno), FAILURE);
	else
	{
		fill_tab(data);
		close(data->map_info.fd);
	}
}

/*https://polyhaven.com/textures    -> source texture*/

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (err_msg("Usage", ERR_USAGE, 1));
	data_init(&data);
	if (parse_args(&data, av) != 0)
		return (1);
	start_mlxtex(&data);
	render_images(&data);
	listen_for_input(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
