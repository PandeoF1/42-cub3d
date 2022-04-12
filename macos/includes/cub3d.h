/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 02:38:07 by tnard             #+#    #+#             */
/*   Updated: 2022/04/12 10:55:26 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/time.h>
# include <pthread.h>

# define PI 3.14159265

# define EVENT_W 13
# define EVENT_A 0
# define EVENT_S 1
# define EVENT_D 2
# define EVENT_SPACE 49
# define EVENT_SHIFT 257
# define EVENT_ESC 53
# define WIDTH 1280
# define HEIGHT 720
# define NB_THREAD 16
# define SIZE_P_STANDING 0.5
# define SIZE_P_CROUCHING 0.25
# define DOOR_CHAR "ZBVC"
# define DOOR_LEN 4
# define SPRITE_CHAR "T"
# define SPRITE_LEN 1
# define PERF 2

# define MUSIC 0

# ifdef __APPLE__
#  define MUSIC 0
# endif

typedef struct s_keyboard
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	space;
	int	up;
	int	down;
	int	right;
	int	left;
}				t_keyboard;

typedef struct s_plan
{
	float	a;
	float	b;
	float	c;
	float	d;
}				t_plan;

typedef struct s_map_util
{
	int		i;
	int		j;
	int		x;
	int		y;
}				t_map_util;
typedef struct s_sprite
{
	float	sx;
	float	sy;
}				t_sprite;

typedef struct s_rayon
{
	float		x;
	float		y;
	float		z;
}				t_rayon;

typedef struct s_update
{
	int				i;
	int				j;
	float			point_x;
	float			point_y;
	float			point_z;
	int				switch_plan;
	int				u;
	int				v;
	float			r;
	int				x;
	int				y;
	float			t;
	int				add;
	int				door;
	float			py_py;
	float			px_px;
	float			best_t;
	int				v_plan;
	int				u_plan;
	t_rayon			rayon_temp;
	t_rayon			rayon_tempp;
	int				best_x;
	int				best_y;
	float			end_y;
	float			start_y;
	struct s_img	*img;
	struct s_game	*game;
}				t_update;

typedef struct s_graphic
{
	void				*mlx;
	void				*win;
	struct s_game		*map_check;
}				t_graphic;

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_game
{
	char				*n;
	char				*s;
	char				*w;
	char				*e;
	char				*f;
	char				*c;
	char				*z[DOOR_LEN];
	char				*t;
	char				*put_fps;
	struct s_keyboard	keyboard;
	struct s_img		img_n;
	struct s_img		img_s;
	struct s_img		img_w;
	struct s_img		img_e;
	struct s_img		img_t;
	int					s_color;
	struct s_img		img_map;
	int					map_color;
	int					floor_color;
	int					ceiling_color;
	struct s_img		door_color[4];
	int					nb_door;
	char				**map;
	float				angle_z;
	float				angle_x;
	float				cos_z;
	float				cos_x;
	float				sin_z;
	float				sin_x;
	float				player_x;
	float				player_y;
	float				dist_x;
	float				dist_y;
	float				size_p;
	int					max_y;
	int					max_x;
	int					nb_sprites;
	int					twidth;
	int					theight;
	struct s_plan		**plan;
	struct s_sprite		*sprites;
	struct s_rayon		**rayon;
	struct s_graphic	*graphic;
	struct s_map_util	*m_u;
	int					minimap;
	pthread_t			music;
}	t_game;

/* Utils */
char	*ft_strnjoinf(char *s1, char *s2, int n); // free second
char	*ft_strnjoin(char *s1, char *s2, int n); // free first
void	ft_free_split(char **split);
int		ft_splitlen(char **split);
int		ft_split_number(char **split);
int		ft_atoi_base(char *str, char *base);

/* Check - Parsing */
char	*ft_get_file(int fd, int size, int len);
int		ft_check_arg(int argc, char **argv, t_game *game);
int		ft_check_texture(char *str, t_game *game);
int		ft_check_map(t_game *game, int x, char *str, int i);
int		ft_max_len(char *str);

/* Event */

int		ft_win_event(int keycode, t_game *game);
int		ft_unpress(int keycode, t_game *game);
void	ft_move_next(t_game *game);
void	ft_move(t_game *game);
int		ft_exit_hook(t_game *game);
void	ft_mouse(t_game *game);

/* Set var */

t_rayon	**ft_malloc_rayon(t_game *game);
void	ft_init_struct(t_game *game, t_graphic *graphic);
void	ft_set_rayons(t_update *update, t_game *game);
void	ft_set_switch(t_update *update, t_game *game);
void	ft_set_points(t_update *update, t_game *game, float t);
void	ft_set_var(t_update *update);
void	ft_set_sprites(t_game *game);

/* put texture */

int		ft_put_s_e_wall(t_update *u, t_game *g);
int		ft_put_n_w_wall(t_update *u, t_game *g);
int		ft_put_sprite(t_update *update, t_game *game);
int		ft_put_door(t_update *u, t_game *g);
int		ft_put_door_2(t_update *update, t_game *game);

/* check */

int		ft_is_door(char c);
int		ft_is_sprite(char c);
int		ft_is_double_x(char	**str, int x);
int		ft_is_double_y(char	**str, int y);

/* create plan */

int		ft_create_plan(t_game *game);
void	ft_create_plan_n_s(t_game *game, int x);
void	ft_create_plan_e_w(t_game *game, int x);
int		ft_create_plan_sprite_door(t_game *game);

/* door */

void	ft_door(t_game *game);
void	ft_door_open(t_game *game, int x, int y);
void	ft_door_close(t_game *game, int x, int y);
int		ft_door_count(t_game *game);
void	ft_create_door(t_game *game);

/* map and fps */

void	ft_fps(t_game *game);
void	ft_put_fps(t_game *game, int lframe, int total_second, int total_frame);
void	ft_map(t_game *game, t_img img);
void	ft_draw_square(int y, int x, int max_y, t_game *game);

/* music */

void	*ft_music(void *data);
void	ft_start_music(t_game *game, pthread_t music);
void	ft_stop_music(pthread_t music);

/* img */

int		ft_create_image_n_s(t_game *game);
int		ft_create_image_e_w(t_game *game);
int		ft_data_image(t_game *game);
void	ft_flip_img(t_img *img, int x, int temp, int check);
void	ft_reverse_img(t_img *img, int t, int x, int temp);
int		ft_image_len(char *str, int y);
void	*ft_open_xpm(t_game *game, char *str, int size_x);
int		ft_check_image(char *path);
void	ft_put_image(t_game *game, t_img img2);

/* position */

int		ft_get_pos(t_game *game);
int		ft_select_pos(t_game *game, int x, int y);

/* end */

void	ft_free_rayon(t_rayon **rayon, t_game *game);
void	ft_close(t_game *game);

/* update */

int		ft_case_one(t_update *u, t_game *g);
int		ft_case_two(t_update *update, t_game *game);
void	ft_case_two_util(t_update *update, t_game *game);
void	ft_updater_2(t_update *update, t_game *game);
void	ft_updater_3(t_update *u, t_game *g);
void	ft_updater_4(t_update *u, t_game *g);
void	ft_updater_4_util(t_update *update);
void	ft_updater_5(t_update *update, t_game *game);
float	ft_best_var(t_update *update);

/* jsp encore */

int		ft_nb_of(t_game *game, char charset);
void	ft_create_sprite(t_game *game, char *charset);
int64_t	get_time(void);

void	ft_create_vector(t_game *game);
int		ft_init_sprite(t_game *game, int b, int x, int y);
void	ft_create_sprite(t_game *game, char *charset);
int		ft_color_format(char *str);
void	ft_draw_square(int y, int x, int max_y, t_game *game);
#endif