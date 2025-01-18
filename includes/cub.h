/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:30:49 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/18 22:41:17 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"

enum    e_macros
{
    WIDTH = 1800,
    HEIGHT = 1200,
    BUFFER_SIZE = 42
};

# define INVALID_FILE "Invalid file name. Example: file_name.cub"
# define FILE_NOT_FOUND "File not found"    
# define INVALID_MAP    "Invalid map!"
# define INVALID_COLOR "Error: Invalid color values. Each RGB component must be \
between 0 and 255."

# define INVALID_COLOR_FORMAT "Error: Invalid color format. A valid color must \
have exactly 3 components (R, G, B), each between 0 and 255."

typedef struct s_gc
{
    void        *content;
    struct s_gc    *next;
}    t_gc;

typedef struct s_textures
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
}    t_text_map;

typedef struct s_raytext
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
} t_raytext;

typedef struct s_colors
{
    int	c_floor;
    int	c_ceiling;
}    t_colors;

typedef struct s_mlx_data
{
    mlx_t			*mlx;
    mlx_image_t		*image;
	int				width;
	int				height;
}    t_mlx_data;


typedef struct s_player
{
    char	player;
    bool	if_player_exist;
	int		x_pos;
	int		y_pos;
	double	rotate_angle;
	double	rotation_speed;
	int		turn_dir;
	int		xc;
	int		yc;
    double  x_pos_map;
    double 	y_pos_map;
	double dirX;
    double dirY;
    double planeX;
    double planeY;
}	t_player;

typedef struct s_cast
{
    double	cameraX;
    double	rayDirX;
    double	rayDirY;
	int		mapX;
	int		mapY;
    double	sideDistX;
    double	sideDistY;
    double	deltaDistX;
    double	deltaDistY;
    double	perpWallDist;
    double	posX;
    int		stepX;
    int		stepY;
    int		hit;
    int		side;
    int		lineHeight;
    int		drawStart;
    int		drawEnd;
	double	wallX;
    int		texNum;
    int		texX;
	int		texY;
    double	step;
    double	texPos;
}	t_cast;

typedef struct s_map_data
{
    t_text_map		*texts;
    t_colors    	*colors;
    t_mlx_data		*data_mlx;
	t_player		*player;
    int             p_y_pos;
    int             p_x_pos;
    bool            wall;
    int				height_map;
    int				width_map;
    char			**map;
	int				**arr_text;
	// t_raytext		textures;
	mlx_texture_t	*textures[4];
	double			speed;
    int				tex_width;
    int				tex_height;
    t_cast          cast;
}    t_map_data;

typedef struct s_p
{
	int	x;
	int	y;
}	t_p;

typedef struct s_plotline
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_plotline;


void	*gcollector(size_t size, int mode);
void	*ft_calloc(size_t count, size_t size);

void	pars_map(t_map_data **map_data);
void	parsing(char *file_name, t_map_data *map_data);
void	read_elements(int file_name, t_map_data **map_data);

void	ft_err(char *err_msg);
char	*get_next_line(int fd);
void    my_keyhook(void *param);
size_t	ft_strlen(const char *c);
int		ft_atoi(const char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(const char *s1);
char	**ft_split(char *s, char c);
void	raycasting(t_map_data *map_data);
char	*ft_strtok(char *str, char *sep);
void	ft_putstr_fd(const char *s, int fd);
int		ft_strcmp(const char *s1, char *s2);
char	*ft_strtrim(char *s1, char const *set);
int		rgb_to_int(int r, int g, int b, int a);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
#endif