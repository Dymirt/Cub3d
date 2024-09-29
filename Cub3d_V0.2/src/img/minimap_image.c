#include "cub3d.h"

/*https://en.wikipedia.org/wiki/Mini-map*/

/*Important: Key function: READ*/
static void	set_minimap_tile_pixels_and_gradient_effect(t_minimap *minimap, int x, int y, int color)
{
	int	i;
	int	j;
	int pixel_x;
	int pixel_y;

	// Ensure the tile does not go out of  minimap image if so we retun
	if (!minimap || !minimap->img || minimap->tile_size <= 0)
		return;
	i = 0;
	while (i < minimap->tile_size)
	{
		j = 0;
		while (j < minimap->tile_size)
		{
			pixel_x = x + j;//calc the pixel horizontaly -> on x axis
			pixel_y = y + i;//calc the pixel verticaly -> on y axis

			// Check if the pixel position is within the image boundaries before setting the pixel
			if (pixel_x >= 0 && pixel_x < WIN_WIDTH && pixel_y >= 0 && pixel_y < WIN_HEIGHT)
			{
				//adding gradient effect based on distance from the tile center (https://en.wikipedia.org/wiki/Gradient)
				int distance_to_center = abs((minimap->tile_size / 2) - j) + abs((minimap->tile_size / 2) - i); //each pixel (j, i) and we /2 cuz we want to give halgway point of the tile which is the center of the tile (x, y) direction
				int modified_color = color - (distance_to_center * 100); // Darken color as it moves away from center
				if (modified_color < 0) modified_color = 0; // Ensure color value does not go below 0
				set_image_pixel(minimap->img, pixel_x, pixel_y, modified_color);
			}
			j++;
		}
		i++;
	}
}

static void	draw_minimap_tile(t_minimap *minimap, int x, int y)
{
	if (minimap->map[y][x] == 'P')
		set_minimap_tile_pixels_and_gradient_effect(minimap, x * minimap->tile_size,
			y * minimap->tile_size, MMAP_COLOR_PLAYER);
	else if (minimap->map[y][x] == '1')
		set_minimap_tile_pixels_and_gradient_effect(minimap, x * minimap->tile_size,
			y * minimap->tile_size, MMAP_COLOR_WALL);
	else if (minimap->map[y][x] == '0')
		set_minimap_tile_pixels_and_gradient_effect(minimap, x * minimap->tile_size,
			y * minimap->tile_size, MMAP_COLOR_FLOOR);
	else if (minimap->map[y][x] == ' ')
		set_minimap_tile_pixels_and_gradient_effect(minimap, x * minimap->tile_size,
			y * minimap->tile_size, MMAP_COLOR_SPACE);
}


static void	set_minimap_border_image_pixels(t_minimap *minimap, int color)
{
	int	size;
	int	x;
	int	y;

	size = MMAP_PIXEL_SIZE + minimap->tile_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x <= size)
		{
			if (x < 5 || x > size - 5 || y < 5 || y > size - 5)
				set_image_pixel(minimap->img, x, y, color);
			x++;
		}
		y++;
	}
}



static void	draw_minimap(t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->size)
	{
		x = 0;
		while (x < minimap->size)
		{
			if (!minimap->map[y] || !minimap->map[y][x]
				|| minimap->map[y][x] == '\0')
				break ;
			draw_minimap_tile(minimap, x, y);
			x++;
		}
		y++;
	}
	set_minimap_border_image_pixels(minimap, MMAP_COLOR_SPACE);
}


void	render_minimap_image(t_data *data, t_minimap *minimap)
{
	int	img_size;

	img_size = MMAP_PIXEL_SIZE + minimap->tile_size;
	init_img(data, &data->minimap, img_size, img_size);//init_img_mlx
	draw_minimap(minimap);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img,
		minimap->tile_size, data->win_h
		- (MMAP_PIXEL_SIZE + (minimap->tile_size * 2)));
	mlx_destroy_image(data->mlx, data->minimap.img);
}
