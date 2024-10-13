/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:31:43 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/13 13:18:28 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map);
int		read_file(char ***file, int fd);

int	read_map(t_data *data, char *path)
{
	int	fd;

	if (!is_file_ext(path, ".cub"))
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (err_msg(path, strerror(errno), 0));
	if (!read_file(&data->map_info.file, fd))
		return (err_msg(path, "Empty file", 0));
	close(fd);
	return (1);
}

int	read_file(char ***file, int fd)
{
	char	*line;
	int		row;

	row = 0;
	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	*file = ft_calloc(MAX_LINES, sizeof(char *));
	while (1)
	{
		while (line != NULL && ft_strlen(line) == 1 && line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
		if (line == NULL)
			break ;
		(*file)[row] = ft_strdup(line);
		row++;
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	file[row] = NULL;
	return (1);
}
