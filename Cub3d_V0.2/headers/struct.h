/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:45:05 by dkolida           #+#    #+#             */
/*   Updated: 2024/10/13 16:56:05 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*MACROS*/

# define CLIENT_MESSAGE      33
# define NO_EVENT_MASK       0L
# define KEY_PRESS           2
# define KEY_PRESS_MASK      1L
# define KEY_RELEASE         3
# define KEY_RELEASE_MASK    2L

//x11/keys
# define XK_ESCAPE           0xff1b
# define XK_LEFT             0xff51
# define XK_RIGHT            0xff53
# define XK_W                0x0077
# define XK_A                0x0061
# define XK_S                0x0073
# define XK_D                0x0064

# ifndef DEBUG_MSG
#  define DEBUG_MSG 1
# endif

/* # define WIN_WIDTH 960 */
/* # define WIN_HEIGHT 720 */
# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# define TEX_SIZE 64

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define MOVESPEED 0.0256
# define ROTSPEED 0.0256

# define DIST_EDGE_MOUSE_WRAP 20

/* MINIMAP MACROS */
# define MMAP_PIXEL_SIZE 128
# define MMAP_VIEW_DIST 4
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0x808080
# define MMAP_COLOR_FLOOR 0xE6E6E6
# define MMAP_COLOR_SPACE 0x404040

// ERROR MESSAGES
# define ERR_USAGE "usage: ./cub3d [Map.cub]"

//Custom macros
# ifndef LARGE_VALUE
#  define LARGE_VALUE 1e30
# endif

# ifndef MAX_LINES
#  define MAX_LINES 1000
# endif

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef unsigned long	t_ulong;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		end;
}	t_img;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	int				x;//x_axis
	int				y;//y_axis
	int				i;//index
	int				size;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	double			step;
	double			position;
	int				sizes[4];
}	t_texinfo;

typedef struct s_map_information
{
	int		height;
	int		width;
	char	**file;

}	t_map_information;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		move_x;
	int		move_y;
	int		rotate;
	int		has_moved;
}	t_player;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	int					win_h;
	int					win_w;
	int					**tex_pixels;
	int					**tex;
	t_map_information	map_info;
	char				**map;
	t_player			player;
	t_ray				ray;
	t_texinfo			texinfo;
	t_img				minimap;
}	t_data;

typedef enum e_direction
{
	X_DIR,
	Y_DIR
}	t_direction;

#endif
