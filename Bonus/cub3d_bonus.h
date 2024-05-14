/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:13:48 by mel-jira          #+#    #+#             */
/*   Updated: 2024/03/08 12:41:52 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define SCREEN_HEIGHT 1000
# define SCREEN_WIDTH 1500
# define MINIMAP_WIDTH 275
# define MINIMAP_HEIGHT 275

# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define BLACK 0x000000
# define GREEN 0x2F5233
# define BLUE 0x0000FF
# define BACKGROUND 0xCDB79E

# define FOV 60
# define PLAYER_SPEED 4
# define ROTATING_SPEED 1

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include "mlx.h"

typedef struct s_leaks
{
	void			*ptr;
	struct s_leaks	*next;
}	t_leaks;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_m_pixel;
	int		line_length;
	int		line_width;
	int		line_heigth;
	int		size_len;
	int		endian;
}	t_data;

typedef struct s_animation
{
	void	*image[16];
}	t_animation;

typedef struct s_map
{
	t_data			img;
	t_data			no_txture;
	t_data			so_txture;
	t_data			we_txture;
	t_data			es_txture;
	t_data			door_texture;
	t_animation		ptr;
	int				click;
	int				i;
	int				height;
	int				width;
	void			*mlx;
	void			*win;
	void			*north;
	void			*south;
	void			*west;
	void			*east;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	int				floor[3];
	int				floor_color;
	int				ceiling_color;
	int				ceiling[3];
	char			**map;
	double			mini_x;
	double			mini_y;
	double			my;
	double			mx;
	double			player_x;
	double			player_y;
	double			pos_x;
	double			pos_y;
	double			xstep;
	double			ystep;
	double			intercept_x;
	double			intercept_y;
	double			horizontal_x;
	double			horizontal_y;
	double			vertical_x;
	double			vertical_y;
	int				horizontal;
	int				vertical;
	int				right;
	int				up;
	int				left;
	int				dawn;
	double			distance;
	double			true_distance;
	double			hitx;
	double			hity;
	int				verticalhit;
	int				horizontalhit;
	double			obj_distance;
	double			obj_height;
	double			move_speed;
	double			angle;
	double			rot_speed;
	double			fov;
	char			direction;
	double			num_rays;
	int				move_up;
	int				move_down;
	int				move_right;
	int				move_left;
	int				move_right_angle;
	int				move_left_angle;
	int				drawzy;
	int				offset_x;
	int				offset_y;
	unsigned int	*buffer;
	int				mouse_x;
	int				mouse_y;
	int				focus_mode;
	int				door;
	int				doorh;
	int				doorv;
}	t_map;

typedef struct s_mapheader
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	c;
	int	f;
}	t_mapheader;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

//parsing tools
int		check_name(char *str);
int		check_map(t_map *map, char *map_name);
char	**readfilecontant(char *mapname, int fd, int len, int i);
int		check_texture_and_colors(t_map *map, char **map_contant, int *i);
int		check_map_contant(t_map *map, char **map_contant, int i);
int		is_only_map(char **map, int i);
int		search_line(char *str, char *look);
char	**get_only_map(char **map, int i);
int		map_size(char **map, int i);
char	**make_it_bigger_square(char **map, int x, int y, int i);
int		get_biggest_x(char **map);
int		get_biggest_y(char **map);
char	*fill_it2(int x);
char	*fill_it1(char **map, int x, int y);
char	**create_cpy(char **map);
int		check_characters(char **map);
void	can_access(char **map, int x, int y, t_point limit);
void	only1player(char **map, t_map *info, int y, int x);
void	can_fall(char **map, int x, int y, t_point limit);
int		get_biggest_x2(char **map, t_map *info);
int		get_biggest_y2(char **map, t_map *info);
void	basic_init(t_mapheader *mapheader);
int		valid_colors(t_map *map, char *str, int f_or_c);
int		check_colors(t_map *map, char *line, t_mapheader *mapheader, int i);
int		path_exist(t_map *map, char *str, int direction);
int		check_texture(t_map *map, char *line, t_mapheader *mapheader, int i);
int		check_line(t_map *map, char *line, t_mapheader *mapheader, int i);
void	calc_minimap(t_map *map);

//execution tools
int		key_hook1(int keycode, t_map *map);
int		key_hook2(int keycode, t_map *map);
int		close_window(t_map *info);
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
void	my_mlx_m_pixel_put(t_data *data, int x, int y, int color);
int		ft_render_the_game(t_map *map);
void	put_player(t_map *info);
void	put_minimap(t_map *map);
void	put_map(t_map *map);
int		execution(t_map map);
void	horizontal_helper(t_map *map, double ray_angle);
void	vertical_helper(t_map *map, double ray_angle);

//general tools
int		ft_isnum(char *str);
char	*ft_strchr(char *str, char c);
int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(char *arg, int i);
int		ft_is_space(char c);
int		ft_strcmp(char *str1, char *str2);
int		parsing(t_map *map, char *map_name);
int		execution(t_map map);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *s);
char	*ft_strchr(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoinx(char *remain, char *buffer);
char	*get_next_line(int fd);
int		get_lines(int fd);
int		stop_here2(char *str);
double	normlize(double rayangle);

//errors
void	error1(void);
void	error2(void);
void	error3(void);
void	error4(void);
void	error5(void);
void	error43(void);
void	error_player(void);

//printing
void	print_map(char **map);

//garbage collactor
void	*ft_malloc(size_t a);

//execution it self
int		is_wall2(t_map *map, double horizontal_x, double horizontal_y);
int		is_what(t_map *map, double horizontal_x, double horizontal_y);
void	horizontal_helper(t_map *map, double ray_angle);
void	horizontal(t_map *map, double ray_angle);
void	vertical_helper(t_map *map, double ray_angle);
void	vertical(t_map *map, double ray_angle);
void	reset(t_map *map, double ray_angle);
double	distance_finder(double x1, double y1, double x2, double y2);
void	find_helper(t_map *map, double *hori_dis, double *vert_dis);
void	find_shortest(t_map *map);
void	rendering_helper(t_map *map, int *top, int *bottom, double ray_angle);
t_data	*img_found(t_map *map, double ray_angle);
void	img_helper(t_map *map, t_data *img);
void	rendering(t_map *map, int column, double ray_angle);
void	ray_casting(t_map *map, int column, double ray_angle);
void	put_map(t_map *map);
double	normlize(double rayangle);
void	put_weapon(t_map *map);
int		ft_render_the_game(t_map *map);
void	draw_minimap_line(t_map *map, double x, double y);
void	calc_minimap_line(t_map *map);
void	put_player(t_map *info);
int		is_wall(t_map *map, int lenx, int leny);
void	put_minimap(t_map *map);
void	ft_calc_right(t_map *map);
void	ft_calc_left(t_map *map);
void	ft_calc_front(t_map *map);
void	ft_calc_back(t_map *map);
void	ft_calc_right_angle(t_map *map);
void	ft_calc_left_angle(t_map *map);
int		ft_update(t_map *map);
int		ft_mouse_rotation(int x, int y, t_map *map);
int		mouse_click_hook(int keycode, int x, int y, t_map *map);
int		execution(t_map map);
void	help_set_texture(t_map *map);
void	set_important_values(t_map *info, int i, int j);
void	set_angle(t_map *map);
void	set_important_values2(t_map *map);

#endif
