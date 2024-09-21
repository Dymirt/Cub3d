#include "cub3d.h"

static void	print_manual(void)
{
	printf(GREEN "\n");
	printf("_________      ___.   ________ ________       _____                             .__   \n");
	printf("\\_   ___ \\ __ _\\_ |__ \\_____  \\\\______ \\     /     \\ _____    ____  __ _______  |  |  \n");
	printf("/    \\  \\/|  |  \\ __ \\  _(__  < |    |  \\   /  \\ /  \\\\__  \\  /    \\|  |  \\__  \\ |  |  \n");
	printf("\\     \\___|  |  / \\_\\ \\/       \\|    `   \\ /    Y    \\/ __ \\|   |  \\  |  // __ \\|  |__\n");
	printf(" \\______  /____/|___  /______  /_______  / \\____|__  (____  /___|  /____/(____  /____/ \n");
	printf("        \\/          \\/       \\/        \\/          \\/     \\/     \\/           \\/       \n");                                                           
	printf(RESET "\n");
	printf(CYAN "\tW" RESET ": move forward\t");
	printf(CYAN "\tS" RESET ": move backward\n");
	printf(CYAN "\tA" RESET ": strafe left\t");
	printf(CYAN "\tD" RESET ": strafe right\n");
	printf(CYAN "\t<" RESET ": rotate left\t");
	printf(CYAN "\t>" RESET ": rotate right\n");
	printf(YELLOW "Made by 42-warsaw\n" RESET);
	printf("\n");
}


static int	parse_args(t_data *data, char **av)
{
	if (check_file(av[1], true) == FAILURE)
		clean_exit(data, FAILURE);
	parse_data(av[1], data);
	if (get_file_data(data, data->map_info.file) == FAILURE)
		return (free_data(data));
	if (check_map_validity(data, data->map) == FAILURE)
		return (free_data(data));
	if (check_textures_validity(data, &data->texinfo) == FAILURE)
		return (free_data(data));
	init_player_direction(data);
	if (DEBUG_MSG)
		debug_display_data(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (err_msg("Usage", ERR_USAGE, 1));
	init_data(&data);
	if (parse_args(&data, av) != 0)
		return (1);
	init_mlx(&data);
	init_textures(&data);
	print_manual();
	render_images(&data);
	listen_for_input(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
