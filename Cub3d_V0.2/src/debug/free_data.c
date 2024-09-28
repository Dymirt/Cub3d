#include "cub3d.h"

void	free_2Darray(void **AD)
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

static void	free_map(t_data *data)
{
	if (data->map_info.fd > 0)
		close(data->map_info.fd);
	if (data->map_info.file)
		free_2Darray((void **)data->map_info.file);
	if (data->map)
		free_2Darray((void **)data->map);
}

int	free_data(t_data *data)
{
	if (data->tex)
		free_2Darray((void **)data->tex);
	if (data->tex_pixels)
		free_2Darray((void **)data->tex_pixels);
	free_texinfo(&data->texinfo);
	free_map(data);
	return (FAILURE);
}
