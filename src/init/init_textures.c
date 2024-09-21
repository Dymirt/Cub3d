#include "cub3d.h"



static int *xpm_to_img(t_data *data, char *path)
{
    t_img tmp;
    int *buffer;
    int x;
    int y;

     init_texture_img(data, &tmp, path);
     buffer = ft_calloc(1, sizeof * buffer * data->texinfo.size * data->texinfo.size);
     if (!buffer)
        clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
    y = 0;
    while (y < data->texinfo.size)
    {
        x = 0;
        while (x < data->texinfo.size)
        {
            buffer[y * data->texinfo.size + x]
                = tmp.addr[y * data->texinfo.size + x];
            ++x;
        }
        y++;
    }
    mlx_destroy_image(data->mlx, tmp.img);
    return (buffer);
}

void init_textures(t_data *data)
{
    data->tex = ft_calloc(5, sizeof * data->tex);
    if (!data->tex)
        clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
    data->tex[NORTH] = xpm_to_img(data, data->texinfo.north);
    data->tex[SOUTH] = xpm_to_img(data, data->texinfo.south);
    data->tex[EAST] = xpm_to_img(data, data->texinfo.east);
    data->tex[WEST] = xpm_to_img(data, data->texinfo.west);

}

void init_texinfo(t_texinfo *textures)
{
    textures->north = NULL;
    textures->south = NULL;
    textures->west = NULL;
    textures->east = NULL;
    textures->floor = 0;
    textures->ceiling = 0;
    textures->x = 0;
    textures->y = 0;
    textures->size = 0.0;
    textures->hex_floor = 0x0;
    textures->hex_ceiling = 0x0;
    textures->step = 0.0;
    textures->position = 0.0;
}