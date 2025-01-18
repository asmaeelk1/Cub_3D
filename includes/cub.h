/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:30:49 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/18 09:08:11 by oel-feng         ###   ########.fr       */
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
// # include "../minilibx-linux/mlx.h"

enum    e_macros
{
    WIDTH = 1800,
    HEIGHT = 1200,
    TILE_SIZE = 32,
    BUFFER_SIZE = 42,
    H = HEIGHT
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

typedef struct s_textures_img
{
    void    *image;
    int     pixels;
    int     line;
    int     endian;
    int     *address;
}    t_textures_img;

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
    int     x_pos_map;
    int     y_pos_map;
}	t_player;

typedef struct s_cast
{
    double   cameraX; // X pos dyal camera
    double   rayDirX; // Dir dyal ray f x
    double   rayDirY; // Dir dyal ray f y
    int     mapX;    // X pos f map 
    int     mapY;    // Y pos f map
    double   sideDistX; // Distance l a9rab x
    double   sideDistY; // Distance l a9rab y
    double   deltaDistX; // Distance dyal 1 tile f x
    double   deltaDistY; // Distance dyal 1 tile f y
    double   perpWallDist; // Distance dyal ray f wall (90 degree)
    double   posX; // X pos dyal player
    int     stepX; // Step dir f x (1 oula -1)
    int     stepY;  // Step dir f y (1 oula -1)
    int     hit; // Check ila t9as l wall oula la
    int     side; // ina jiha t9as l7ayt
    int     lineHeight; // Height dyal line
    int     drawStart; // Start dyal line
    int     drawEnd; // End dyal line
} t_cast;

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
	int				tile_size;
	mlx_texture_t *textures[4];
    int tex_width;
    int tex_height;
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

void	parsing(char *file_name, t_map_data **map_data);
void	read_elements(int file_name, t_map_data **map_data);
void	pars_map(t_map_data **map_data);

int		ft_strcmp(const char *s1, char *s2);
char	*ft_strchr(char *s, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	ft_putstr_fd(const char *s, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char *s1, char const *set);
char	*ft_strtok(char *str, char *sep);
int		ft_atoi(const char *str);
char	**ft_split(char *s, char c);
char	*get_next_line(int fd);
void	ft_err(char *err_msg);

// draw 2D map
void    plot_line(t_map_data **data, t_p p0, t_p p1, long color);
void    draw_square(t_map_data **map_data, int x, int y, long color);
void    map_2d(t_map_data **map_data);
// player movement
void    my_keyhook(void *param);
void	recheck_text(t_map_data **map_data);
// void	rendering(t_map_data **map_data);
void    start_raycast(t_map_data **map_data);
void	raycasting_init(t_cast *cast);
void	raycasting(t_map_data **map_data, t_cast *cast);

#endif