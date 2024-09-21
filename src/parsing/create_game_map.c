#include "cub3d.h"

static int	count_map_lines(t_data *data, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
		|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	data->map_info.i_end_of_map = i;
	return (i - index_value);
}

static int	fill_map_tab(t_map_information *map_info, char **map_tab, int index)
{
	int		i;
	int		j;

	map_info->width = find_biggest_len(map_info, index);
	i = 0;
	while (i < map_info->height)
	{
		j = 0;
		map_tab[i] = malloc(sizeof(char) * (map_info->width + 1));
		if (!map_tab[i])
			return (err_msg(NULL, ERR_MALLOC, FAILURE));
		while (map_info->file[index][j] && map_info->file[index][j] != '\n')
		{
			map_tab[i][j] = map_info->file[index][j];
			j++;
		}	
		while (j < map_info->width)
			map_tab[i][j++] = '\0';
		i++;
		index++;
	}
	map_tab[i] = NULL;
	return (SUCCESS);
}

static int	get_map_info(t_data *data, char **file, int i)
{
	data->map_info.height = count_map_lines(data, file, i);
	data->map = malloc(sizeof(char *) * (data->map_info.height + 1));
	if (!data->map)
		return (err_msg(NULL, ERR_MALLOC, FAILURE));
	if (fill_map_tab(&data->map_info, data->map, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	change_space_into_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] == ' ' || data->map[i][j] == '\t'
		|| data->map[i][j] == '\r'
		|| data->map[i][j] == '\v' || data->map[i][j] == '\f')
			j++;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == ' '
				&& j != data->map[i][ft_strlen(data->map[i]) - 1])
				data->map[i][j] = '1';
		}
		i++;
	}
}

int	create_map(t_data *data, char **file, int i)
{
	if (get_map_info(data, file, i) == FAILURE)
		return (FAILURE);
	change_space_into_wall(data);
	return (SUCCESS);
}
