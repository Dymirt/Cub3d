/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ArgMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:27:39 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/06 21:23:45 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_top_or_bottom(char **map_tab, int i, int j)
{
	if (!map_tab || !map_tab[i] || !map_tab[i][j])
		return (FAILURE);
	while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
	|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
	|| map_tab[i][j] == '\f')
		j++;
	while (map_tab[i][j])
	{
		if (map_tab[i][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

static bool	xpm_cub_check(char *arg, bool is_cub)
{
	size_t	len;
	int		fd;

	len = ft_strlen(arg);
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		return (false);
	}
	if (is_cub && len > 4 && ft_strncmp(&arg[len - 4], ".cub", 4) == 0)
		return (true);
	if (!is_cub && len > 4 && ft_strncmp(&arg[len - 4], ".xpm", 4) == 0)
		return (true);
	return (false);
}

int	check_file(char *arg, bool is_cub)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (!xpm_cub_check(arg, is_cub))
	{
		if (is_cub)
			return (err_msg(arg, ".cub: error", FAILURE));
		else
			return (err_msg(arg, ".xpm: error", FAILURE));
	}
	if (fd == -1)
		return (err_msg(arg, strerror(errno), FAILURE));
	close(fd);
	return (SUCCESS);
}

int	check_map_sides(t_map_information *map, char **map_tab)
{
	int	i;
	int	j;

	if (check_top_or_bottom(map_tab, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_tab[i]) - 1;
		if (map_tab[i][j] != '1')
			return (FAILURE);
		i++;
	}
	if (check_top_or_bottom(map_tab, i, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

size_t	find_biggest_len(t_map_information *map, int i)
{
	size_t	biggest_len;

	biggest_len = ft_strlen(map->file[i]);
	while (map->file[i])
	{
		if (ft_strlen(map->file[i]) > biggest_len)
			biggest_len = ft_strlen(map->file[i]);
		i++;
	}
	return (biggest_len);
}
