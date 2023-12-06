/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:46:27 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/11/23 17:50:31 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

#include <mlx.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FOV_ANGLE 66 * (M_PI / 180)

enum errors
{
	VALID,
	INVALID_ARGS,
	INVALID_EXTENSION,
	FILE_NOT_FOUNDED,
	INVALID_MAP,
	CARDINAL_POINTS,
	INVALID_COLORS,
	INVALID_TEXTURE,
	INVALID_TEXTURE_WE,
	INVALID_TEXTURE_EA,
	INVALID_TEXTURE_SO,
	INVALID_TEXTURE_NO
} errors;

typedef struct  s_vector
{
	double	x;
	double	y;
    
}   t_vector;

typedef struct  s_algorithm
{
	int			hit;
	int			hitSide;
	int			texNum;
	int			texX;
	int			texY;
	double		mult;
	double		perpendicularDist;
	double		texStep;
	double		texPos;
	double		wallX;
	t_vector	camPixel;
	t_vector	deltaDist;
	t_vector	distSide;
	t_vector	mapPos;
	t_vector	rayDir;
	t_vector	step;
    
}   t_algorithm;


typedef struct  s_map
{
	char	**map_plan;
	char	**map_temp;
	char	*path_EA;
	char	*path_NO;
	char	*path_SO;
	char	*path_WE;
	int		*ceiling;
	t_vector	map_tile_size;
	int		*floor;
	int		n_colors;
	int		n_texture;
	int		col_map;
	int		row_map;
}	t_map;

typedef struct	s_image
{
	int		lineEnd;
	int		lineStart;
	int		sizeLine;
	void	*img_e;
	void	*img_n;
	void	*img_s;
	void	*img_w;
	void	**columns;
	void	*map;

}	t_image;

typedef struct	s_player
{
	int			down;
	int			left;
	int			right;
	int			up;
	int			camLeft;
	int			camRight;
	t_vector	angCam;
	t_vector	dir;
	t_vector	pos;
	double		rotationAngle;
}	t_player;

typedef struct	s_game
{
	int			size_x;
	int			size_y;
	double		oldTime;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	double		time;
	void		*init;
	void		*win;
	char		*addr;
	int			check;
	char		**errors;
	t_map		map;
	t_image		image;
	t_player	player;
	t_algorithm	dda;
}	t_game;

char		*ft_clear_line(char *line);
char		*ft_get_data_img(t_game *game, char type, int pixel);
int		 ft_close(t_game *game);
int		 ft_create_images(t_game *game);
int		 ft_check_map_char(char *str);
int		 ft_check_map_layout(t_map *map, int row, int col);
int		 ft_fill_layout_map(t_map *map, char *str, int col, int row);
int		 ft_get_colors(t_map *map, int *colors, char **line, int fd);
int		 ft_get_map_plan(t_map *map, char **line, int fd);
int		 ft_get_textures(t_map *map, int *texture, char **line, int fd);
int		 ft_key_press(int key, t_game *game);
int		 ft_key_release(int key, t_game *game);
int		 ft_move_dir(t_game *game);
int		 ft_render(t_game *game);
t_vector	ft_add_vector(t_vector v1, t_vector v2);
t_vector	ft_gen_vector(double x, double y);
t_vector	ft_mult_vector(t_vector v, double scale);
t_vector	ft_rotate_point(t_vector v, double angle);
void		ft_checker(t_game *game, int argc, char **argv);
void		ft_init(t_game *game);
void		ft_paint_column(t_game *game, int y, char *data_columns);
void		ft_start_player_cords(t_player *player, char **map);
void		load_map(t_game *game);
void		makesqre(t_game *data, int x, int y, int color);
void		load_errors(t_game *game);
void 		error_msg(t_game *game, int i);
void		showError(int i, t_game *game);
int			check_colors(t_game *game);
void		castRays(t_game *data, int px, int py);
void		renderPlayer(t_game *data);
void		castRay(t_game *data, int px, int py, double rayAngle);
double		normalizeAngle(double angle);
void		drawLine(t_game *data, int x0, int y0, int x1, int y1, int color);
double		distanceBetweenPoints(double x1, double y1, double x2, double y2);

#endif