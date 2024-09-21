#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
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
		free_tab((void **)data->map_info.file);
	if (data->map)
		free_tab((void **)data->map);
}

int	free_data(t_data *data)
{
	if (data->tex)
		free_tab((void **)data->tex);
	if (data->tex_pixels)
		free_tab((void **)data->tex_pixels);
	free_texinfo(&data->texinfo);
	free_map(data);
	return (FAILURE);
}
