#include "cub3d.h"


void init_img(t_data *data, t_img *image, int w, int h)
{
    init_img_clean(image);
    image->img = mlx_new_image(data->mlx, w, h);
    if (image->img == NULL)
        clean_exit(data, err_msg("mlx", ERR_MLX_IMG, 1));
    image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
                    &image->size_line, &image->end);
    return ;
}

void init_texture_img(t_data *data, t_img *image, char *path)
{
    init_img_clean(image);
    image->img = mlx_xpm_file_to_image(data->mlx, path, &data->texinfo.size,
                    &data->texinfo.size);
    if (image->img == NULL)
        clean_exit(data, err_msg("mlx", ERR_MLX_IMG, 1));
    image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
                        &image->size_line, &image->end);
    return ;
}

void init_mlx(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        clean_exit(data, err_msg("mlx", ERR_MLX_START, 1));
    data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
    if (!data->win)
        clean_exit(data, err_msg("mlx", ERR_MLX_WIN, 1));
    return ;
}