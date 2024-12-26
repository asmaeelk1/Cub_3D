
#include "../../includes/cub.h"

void	rotation_hook(t_map_data *data)
{
	if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_RIGHT))
	{
		data->player->turn_dir = 1;
		data->player->rotate_angle += data->player->turn_dir * data->player->rotation_speed;
	}
	if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_LEFT))
	{
		data->player->turn_dir = -1;
		data->player->rotate_angle += data->player->turn_dir * data->player->rotation_speed;
	}
}

void	translation_hook(t_map_data *data)
{
    float pos_x = 0;
    float pos_y = 0;
    float movement_speed = 3; 

    if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_W)) 
    {
        pos_y = movement_speed * sin(data->player->rotate_angle);
        pos_x = movement_speed * cos(data->player->rotate_angle);
    }
    if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_A)) 
    {
        pos_x = -movement_speed * cos(data->player->rotate_angle + M_PI_2);
        pos_y = -movement_speed * sin(data->player->rotate_angle + M_PI_2);
    }
    if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_S))
    {
        pos_y = -movement_speed * sin(data->player->rotate_angle);
        pos_x = -movement_speed * cos(data->player->rotate_angle);
    }
    if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_D)) 
    {
        pos_x = movement_speed * cos(data->player->rotate_angle + M_PI_2);
        pos_y = movement_speed * sin(data->player->rotate_angle + M_PI_2);
    }
	if(!is_wall(&data, data->player->xc + pos_x, data->player->yc + pos_y))
	{
		data->p_x_pos += pos_x;
		data->p_y_pos += pos_y;
	}
}

void	my_keyhook(void *param) 
{
	t_map_data	**data;

	data = param;
	if (mlx_is_key_down((*data)->data_mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window((*data)->data_mlx->mlx);
	translation_hook(*data);
	rotation_hook(*data);

	mlx_delete_image((*data)->data_mlx->mlx, (*data)->data_mlx->image);
	(*data)->data_mlx->image = mlx_new_image((*data)->data_mlx->mlx, WIDTH, HEIGHT);
	map_2d(data);
	mlx_image_to_window((*data)->data_mlx->mlx, (*data)->data_mlx->image, 0, 0);
}
