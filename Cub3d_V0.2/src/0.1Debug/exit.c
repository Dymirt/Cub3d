#include "cub3d.h"

void	clean_exit(t_data *data, int code)
{
	if (!data)
		exit(code);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		mlx_loop_end(data->mlx);
		free(data->mlx);
	}
	all_free(data);
	exit(code);
}

int	err_msg(char *detail, char *str, int code)
{
	ft_putstr_fd(RED "cub3D: Error", 2);
	if (detail)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(detail, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n" RESET, 2);
	return (code);
}

int	err_msg_val(int detail, char *str, int code)
{
	ft_putstr_fd(RED "cub3D: Error: ", 2);
	ft_putnbr_fd(detail, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n" RESET, 2);
	return (code);
}

int	parse_args(t_data *data, char **av)
{
	if (check_file(av[1], true) == FAILURE)
		clean_exit(data, FAILURE);
	parse_data(av[1], data);
	if (get_file_data(data, data->map_info.file) == FAILURE)
		return (all_free(data));
	if (check_map_validity(data, data->map) == FAILURE)
		return (all_free(data));
	if (check_textures_validity(data, &data->texinfo) == FAILURE)
		return (all_free(data));
	init_player_direction(data);
	if (DEBUG_MSG)
		debug_display_data(data);
	return (0);
}

int	quit_cub3d(t_data *data)
{
	clean_exit(data, 0);
	return (0);
}

