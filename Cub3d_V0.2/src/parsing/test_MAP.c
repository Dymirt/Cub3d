/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_MAP.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:25:49 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/13 01:59:00 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_elements(t_data *data, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	data->player.dir = '0';
	while (map_tab[i] != NULL)
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (data->map[i][j] == ' ' || data->map[i][j] == '\t'
			|| data->map[i][j] == '\r'
			|| data->map[i][j] == '\v' || data->map[i][j] == '\f')
				j++;
			if (!(ft_strchr("10NSEW", map_tab[i][j])))
				return (err_msg(NULL, "erro: letter", FAILURE));
			if (ft_strchr("NSEW", map_tab[i][j]) && data->player.dir != '0')
				return (err_msg(NULL, "erro: player", FAILURE));
			if (ft_strchr("NSEW", map_tab[i][j]) && data->player.dir == '0')
				data->player.dir = map_tab[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_position_is_valid(t_data *data, char **map_tab)
{
	int	i;
	int	j;

	i = (int)data->player.pos_y;
	j = (int)data->player.pos_x;
	if (ft_strlen(map_tab[i - 1]) < (size_t)j
		|| ft_strlen(map_tab[i + 1]) < (size_t)j)
		return (FAILURE);
	printf("Player position: (%d, %d)\n", i, j);
	printf("Surroundings: [%c, %c, %c, %c]\n",
		map_tab[i - 1][j], map_tab[i + 1][j],
		map_tab[i][j - 1], map_tab[i][j + 1]);
	if (i <= 0 || i >= (data->map_info.height - 1) || j <= 0
		|| j >= (int)ft_strlen(map_tab[i]) - 1)
		return (FAILURE);
	return (SUCCESS);
}

static int	check_player_position(t_data *data, char **map_tab)
{
	int	i;
	int	j;

	if (data->player.dir == '0')
		return (err_msg(NULL, "player: direction", FAILURE));
	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			if (ft_strchr("NSEW", map_tab[i][j]))
			{
				data->player.pos_x = (double)j + 0.5;
				data->player.pos_y = (double)i + 0.5;
				map_tab[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(data, map_tab) == FAILURE)
		return (err_msg(NULL, "player position", FAILURE));
	return (SUCCESS);
}

int	check_map_validity(t_data *data, char **map_tab)
{
	if (!data->map)
		return (err_msg(NULL, "map: error", FAILURE));
	if (check_map_sides(&data->map_info, map_tab) == FAILURE)
		return (err_msg(NULL, "map: without wall", FAILURE));
	if (data->map_info.height < 3)
		return (err_msg(NULL, "map is to small", FAILURE));
	if (check_map_elements(data, map_tab) == FAILURE)
		return (FAILURE);
	if (check_player_position(data, map_tab) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
