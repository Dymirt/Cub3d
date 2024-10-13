/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:41:21 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/13 01:57:42 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "struct.h"

# define RESET	"\e[0m"
# define BLACK	"\e[30m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELLOW	"\e[33m"

/* init directory*/
void	data_init(t_data *data);
void	ray_init(t_ray *ray);
void	init_img_clean(t_img *img);
void	start_mlxtex(t_data *data);
void	init_img(t_data *data, t_img *image, int width, int height);
void	init_textures_img(t_data *data, t_img *image, char *path);
void	init_texinfo(t_texinfo *textures);

/* parsing directory*/

int		check_textures_validity(t_texinfo *textures);
int		check_map_validity(t_data *data, char **map_tab);
int		check_map_sides(t_map_information *map, char **map_tab);
int		is_a_white_space(char c);

/* render directory*/
int		render(t_data *data);
void	render_images(t_data *data);
int		raycasting(t_player *player, t_data *data);
void	init_texture_pixels(t_data *data);
void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x);
void	set_image_pixel(t_img *image, int x, int y, int color);
void	set_default_ray_info(t_ray *ray);
double	calculate_camera_x(int x);
void	calculate_ray_direction(t_ray *ray, t_player *player, double camera_x);
bool	is_within_bounds(t_ray *ray, t_data *data);

/* movement directory*/
void	listen_for_input(t_data *data);
void	init_player_direction(t_data *data);
int		validate_move(t_data *data, double new_x, double new_y);
int		move_player(t_data *data);
int		rotate_player(t_data *data, double rotdir);

/* exit directory*/
void	clean_exit(t_data *data, int code);
int		quit_cub3d(t_data *data);
void	free_2d_array(void **AD);
int		all_free(t_data *data);

/* debug directory*/
int		err_msg(char *detail, char *str, int code);
int		err_msg_val(int detail, char *str, int code);
void	debug_display_data(t_data *data);
void	debug_display_player(t_data *data);
void	debug_print_char_tab(char **tab);
int		parse_args(t_data *data);

int		read_map(t_data *data, char *path);
int		load_map_settings(t_data *data);
int		set_up_down_clours(t_data *data, char *key, char *value);

//Helpers functions
int		is_file_ext(char *arg, char *ext);
int		*set_rgb_colors(char *line);

#endif
