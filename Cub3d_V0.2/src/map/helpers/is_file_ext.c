/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_file_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:31:08 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/12 20:40:27 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_extension(char *file, char *ext);
static int	is_directory(char *path);

int	is_file_ext(char *arg, char *ext)
{
	int	fd;

	if (!is_extension(arg, ext))
		return (err_msg(arg, "Invalid file extension", 0));
	if (is_directory(arg))
		return (err_msg(arg, "Is a directory", 0));
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (err_msg(arg, strerror(errno), 0));
	else
		close(fd);
	return (1);
}

static int	is_directory(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}

static int	is_extension(char *file, char *ext)
{
	int	len;
	int	ext_len;

	len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (len > ext_len && ft_strncmp(&file[len - ext_len], ext, ext_len) == 0)
		return (1);
	return (0);
}
