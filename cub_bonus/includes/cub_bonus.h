/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:30:49 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/03 04:11:13 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../../../MLX42/include/MLX42/MLX42.h"

enum	e_macros
{
	BUFFER_SIZE = 42,
	HEIGHT = 1080,
	WIDTH = 1920
};

enum	e_textures
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
	DOOR = 4
};

# define INVALID_COLOR_FORMAT "Error: Invalid color format."
# define INVALID_COLOR "Error: Invalid color values."
# define INVALID_FILE "Error: Invalid file name."
# define FILE_NOT_FOUND "Error: File not found"
# define INVALID_MAP "Error: Invalid map!"

typedef struct s_gc
{
	void		*content;
	struct s_gc	*next;
}	t_gc;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_colors
{
	long long	c_ceiling;
	long long	c_floor;
}	t_colors;

typedef struct s_player
{
	bool	if_player_exist;
	double	rotation_speed;
	double	x_pos_map;
	double	y_pos_map;
	double	plane_x;
	double	plane_y;
	char	player;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_cast
{
	double	perpwalldist;
	double	deltadist_x;
	double	deltadist_y;
	double	sidedist_x;
	double	sidedist_y;
	int		lineheight;
	int		drawstart;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	tex_pos;
	int		tex_num;
	int		drawend;
	int		step_x;
	int		step_y;
	double	wall_x;
	int		map_x;
	int		map_y;
	int		tex_x;
	int		tex_y;
	int		side;
	double	step;
	int		hit;
}	t_cast;

typedef struct s_door
{
	float	progress;
	int		state;
	int		x;
	int		y;
}	t_door;

typedef struct s_map_data
{
	bool			animation_playing;
	mlx_texture_t	*textures[5];
	char			*frames[61];
	mlx_image_t		*img_frame;
	int				height_map;
	int				tex_height;
	int				width_map;
	int				tex_width;
	mlx_image_t		*mini_map;
	t_colors		*colors;
	t_player		*player;
	t_textures		*texts;
	mlx_image_t		*image;
	mlx_image_t		*frame;
	t_door			*door;
	mlx_texture_t	*text;
	char			**map;
	double			speed;
	t_cast			cast;
	mlx_t			*mlx;
}	t_map_data;

char	*ft_itoa(int n);
void	ft_err(char *err_msg);
void	animation(void *param);
char	*get_next_line(int fd);
void	my_keyhook(void *param);
size_t	ft_strlen(const char *c);
int		ft_atoi(const char *str);
int		save_fd(int fd, bool hold);
char	*ft_strchr(char *s, int c);
void	check_if_walls(char *line);
char	*ft_strdup(const char *s1);
char	**ft_split(char *s, char c);
void	pars_map(t_map_data **map_data);
char	*ft_strtok(char *str, char *sep);
void	raycasting(t_map_data *map_data);
void	*gcollector(size_t size, int mode);
void	cleanup_and_exit(t_map_data *data);
void	map_2d(t_map_data *map_data, int i);
int		ft_strcmp(const char *s1, char *s2);
void	ft_putstr_fd(const char *s, int fd);
void	start_textures(t_map_data *map_data);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strtrim(char *s1, char const *set);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	set_plane_rotation(t_map_data *map_data);
char	*ft_strjoin(const char *s1, const char *s2);
void	up_mvmnt(t_map_data *map_data, double speed);
void	parsing(char *file_name, t_map_data *map_data);
void	left_mvmnt(t_map_data *map_data, double speed);
void	down_mvmnt(t_map_data *map_data, double speed);
void	right_mvmnt(t_map_data *map_data, double speed);
void	open_door(t_map_data *map_data, t_player *player);
void	close_door(t_map_data *map_data, t_player *player);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	mouse_hook(double x_pos, double y_pos, void *param);
void	read_elements(int file_name, t_map_data **map_data);
void	hook_change(struct mlx_key_data keydata, void *param);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	is_open(t_map_data *map_data, int player_x, int player_y);
void	set_textures_data(t_cast *cast, t_map_data *map_data, int x, int y);
void	is_zero_next_to_space(char *l_curr, char *prev, char *next,
			t_map_data **map);

#endif