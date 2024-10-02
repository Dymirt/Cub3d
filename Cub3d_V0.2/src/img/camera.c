#include "cub3d.h"

typedef enum e_direction {
    X_DIR,
    Y_DIR
} t_direction;

static void init_raycasting_info(int x, t_ray *ray, t_player *player)
{
    double camera_x;

    r_start(ray);
    set_default_ray_info(ray);
    camera_x = calculate_camera_x(x);
    calculate_ray_direction(ray, player, camera_x);

    // Set the map position based on player coordinates
    ray->map_x = (int)player->pos_x;
    ray->map_y = (int)player->pos_y;

    // Calculate delta distance for both axes
    if (ray->dir_x != 0) // checking the division by 0 (NOTE) anything divisable by 0 = 0 So in another word non mathematicaly unvalid
        ray->deltadist_x = fabs(1 / ray->dir_x);
    else
        ray->deltadist_x = DBL_MAX; // Set to a large value if dir_x is zero

    if (ray->dir_y != 0)
        ray->deltadist_y = fabs(1 / ray->dir_y);
    else
        ray->deltadist_y = DBL_MAX;
}

// https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
static void set_dda(t_ray *ray, t_player *player)
{
    ray->step_x = (ray->dir_x < 0) ? -1 : 1;
    ray->step_y = (ray->dir_y < 0) ? -1 : 1;

    ray->sidedist_x = (ray->dir_x < 0) ?
        (player->pos_x - ray->map_x) * ray->deltadist_x :
        (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;

    ray->sidedist_y = (ray->dir_y < 0) ?
        (player->pos_y - ray->map_y) * ray->deltadist_y :
        (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
}

/*
- Implementing the DDA algorithm:
- The loop will increment 1 square until we hit a wall.
- If sidedist_x < sidedist_y, x is the closest point from the ray.
*/

static void perform_dda(t_data *data, t_ray *ray) {
    int hit = 0;

    while (hit == 0) {
        if (ray->sidedist_x < ray->sidedist_y)
		{
            ray->sidedist_x += ray->deltadist_x;
            ray->map_x += ray->step_x;
            ray->side = X_DIR;  // Using enum for clarity
        } 
		else 
		{
            ray->sidedist_y += ray->deltadist_y;
            ray->map_y += ray->step_y;
            ray->side = Y_DIR;  // Using enum for clarity
        }
		// Check map
        if (!is_within_bounds(ray, data))
            break;
	if (data->map[ray->map_y][ray->map_x] > '0') 
            hit = 1;  // Wall hit
        
    }
}

static void calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
    if (ray->side == X_DIR)
        ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
    else
        ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
    ray->line_height = (int)(data->win_h / ray->wall_dist);
    ray->draw_start = -(ray->line_height) / 2 + data->win_h / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + data->win_h / 2;
    if (ray->draw_end >= data->win_h)
        ray->draw_end = data->win_h - 1;
    if (ray->side == X_DIR)
        ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
    else
        ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;

    ray->wall_x -= floor(ray->wall_x);
}

int raycasting(t_player *player, t_data *data) {
    t_ray ray;
    int x = 0;

    ray = data->ray;
    while (x < data->win_w) {
        init_raycasting_info(x, &ray, player);
        set_dda(&ray, player);
        perform_dda(data, &ray);
        calculate_line_height(&ray, data, player);
        update_texture_pixels(data, &data->texinfo, &ray, x);
        x++;
    }
    return (SUCCESS);
}