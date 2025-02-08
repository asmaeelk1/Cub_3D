/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:30:49 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/08 06:23:12 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "/home/oel-feng/Desktop/MLX42/include/MLX42/MLX42.h"

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
	EAST = 3
};

# define INVALID_COLOR_FORMAT "Error: Invalid color format."
# define EMPTY_FILE "Error: Empty file."
# define INVALID_FILE "Error: Invalid file."
# define INVALID_COLOR "Error: Invalid color values."
# define FILE_NOT_FOUND "Error: File not found."
# define INVALID_MAP "Error: Invalid map."
# define INVALID_TEXTURE "Error: Failed to load textures."
# define INVALID_TEXTURE_SIZE "Error: Invalid texture size."
# define MALLOC_FAILURE "Error: Malloc Failure"

typedef struct s_memory
{
	void			*address;
	struct s_memory	*next;
}	t_memory;

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

typedef struct s_map_data
{
	mlx_texture_t	*textures[4];
	int				tex_height;
	int				height_map;
	int				width_map;
	int				tex_width;
	t_colors		*colors;
	t_player		*player;
	mlx_image_t		*image;
	mlx_image_t		*mini_map;
	t_textures		*texts;
	double			speed;
	char			**map;
	t_cast			cast;
	mlx_t			*mlx;
}	t_map_data;

void	ft_err(char *err_msg);
char	*get_next_line(int fd);
void	my_keyhook(void *param);
size_t	ft_strlen(const char *c);
int		ft_atoi(const char *str);
int		save_fd(int fd, bool hold);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(const char *s1);
char	**ft_split(char *s, char c);
void	pars_map(t_map_data **map_data);
char	*ft_strtok(char *str, char *sep);
void	raycasting(t_map_data *map_data);
void	*gcollector(size_t size, int mode);
void	ft_putstr_fd(const char *s, int fd);
int		ft_strcmp(const char *s1, char *s2);
void	start_textures(t_map_data *map_data);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strtrim(char *s1, char const *set);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	set_plane_rotation(t_map_data *map_data);
char	*ft_strjoin(const char *s1, const char *s2);
void	parsing(char *file_name, t_map_data *map_data);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	read_elements(int file_name, t_map_data **map_data);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	set_textures_data(t_cast *cast, t_map_data *map_data, int x, int y);

#endif
