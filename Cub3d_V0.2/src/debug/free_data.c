/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:07:01 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/12 19:56:07 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_array(void **AD)
{
	size_t	i;

	i = 0;
	while (AD[i])
	{
		free(AD[i]);
		i++;
	}
	if (AD)
	{
		free(AD);
		AD = NULL;
	}
}

static void	free_texinfo(t_texinfo *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
}

int	all_free(t_data *data)
{
	if (data->map_info.file)
		free_2d_array((void **)data->map_info.file);
	if (data->map)
		free_2d_array((void **)data->map);
	if (data->tex)
		free_2d_array((void **)data->tex);
	if (data->tex_pixels)
		free_2d_array((void **)data->tex_pixels);
	free_texinfo(&data->texinfo);
	return (FAILURE);
}
