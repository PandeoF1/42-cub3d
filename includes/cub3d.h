/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 02:38:07 by tnard             #+#    #+#             */
/*   Updated: 2022/02/22 15:09:12 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlbx/mlx.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdarg.h>

# define EVENT_W 119
# define EVENT_A 97
# define EVENT_S 115
# define EVENT_D 100
# define EVENT_ESC 65307
# define WIDTH 1024
# define HEIGHT 512

# define PI 3.14159265


typedef struct s_map_check
{
	char	*n;
	char	*s;
	char	*w;
	char	*e;
	char	*f;
	char	*c;
	char	**map;
	int		axis;
}	t_map_check;

typedef struct s_graphic
{
	void		*mlx;
	void		*win;
	t_map_check	*map_check;
}	t_graphic;

typedef struct s_rayon
{
	float		x;
	float		y;
	float		z;
}	t_rayon;

/* Utils */
char	*ft_strnjoinf(char *s1, char *s2, int n); // free second
char	*ft_strnjoin(char *s1, char *s2, int n); // free first
void	ft_free_split(char **split);
int		ft_splitlen(char **split);

/* Check - Parsing */
char	*ft_get_file(int fd, int size, int len);
int		ft_check_arg(int argc, char **argv, t_map_check *check);
int		ft_check_texture(char *str, t_map_check *check);
int		ft_check_map(t_map_check *check, int x, char *str, int i);
int		ft_max_len(char *str);


#endif