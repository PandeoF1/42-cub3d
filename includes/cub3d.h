/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 02:38:07 by tnard             #+#    #+#             */
/*   Updated: 2022/03/14 13:36:16 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __APPLE__
	# include "../mlbx-macos/mlx.h"
# else
	# include "../mlbx-linux/mlx.h"
# endif
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

# define EVENT_W 119
# define EVENT_A 97
# define EVENT_S 115
# define EVENT_D 100
# define EVENT_ESC 65307
# define WIDTH 1280
# define HEIGHT 720
# define NB_THREAD 16
# define DOOR_CHAR "ZBNM"
# define DOOR_LEN 4

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

typedef struct s_update
{
	float			end_y;
	float			start_y;
	struct s_img	*img;
	struct s_game	*game;
}				t_update;

typedef struct s_graphic
{
	void				*mlx;
	void				*win;
	struct s_game	*map_check;
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
	struct s_keyboard	keyboard;
	struct s_img		img_n;
	struct s_img		img_s;
	struct s_img		img_w;
	struct s_img		img_e;
	int					floor_color;
	int					ceiling_color;
	struct s_img		door_color[4];
	char				**map;
	int					nb_door;
	float				angle_z;
	float				angle_x;
	float				cos_z;
	float				cos_x;
	float				sin_z;
	float				sin_x;
	float				player_x;
	float				player_y;
	int					max_y;
	int					max_x;
	struct s_plan		**plan;
	struct s_rayon		**rayon;
	struct s_graphic	*graphic;
}	t_game;

typedef struct s_rayon
{
	float		x;
	float		y;
	float		z;
}				t_rayon;

/* Utils */
char	*ft_strnjoinf(char *s1, char *s2, int n); // free second
char	*ft_strnjoin(char *s1, char *s2, int n); // free first
void	ft_free_split(char **split);
int		ft_splitlen(char **split);
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
void 	ft_mouse(t_game *game);

#endif