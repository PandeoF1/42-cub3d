/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/03/17 16:00:01 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	ft_free_rayon(t_rayon **rayon, t_game *game)
{
	int			x;

	x = 0;
	while (x < game->theight)
	{
		free(rayon[x]);
		x++;
	}
	free(rayon);
}

void	ft_close(t_game *game)
{
	if (game->map)
		ft_free_split(game->map);
	if (game->n)
		free(game->n);
	if (game->s)
		free(game->s);
	if (game->e)
		free(game->e);
	if (game->w)
		free(game->w);
	if (game->f)
		free(game->f);
	if (game->c)
		free(game->c);
	ft_free_rayon(game->rayon, game);
	mlx_destroy_image(game->graphic->mlx, game->img_n.img_ptr);
	mlx_destroy_image(game->graphic->mlx, game->img_s.img_ptr);
	mlx_destroy_image(game->graphic->mlx, game->img_e.img_ptr);
	mlx_destroy_image(game->graphic->mlx, game->img_w.img_ptr);
	mlx_destroy_window(game->graphic->mlx, game->graphic->win);
	mlx_destroy_display(game->graphic->mlx);
	printf("Cub3d: exit\n");
}

int	ft_select_pos(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'N')
		game->angle_z = 0;
	else if (game->map[y][x] == 'S')
		game->angle_z = 3.14;
	else if (game->map[y][x] == 'W')
		game->angle_z = 3.14 * 0.5;
	else if (game->map[y][x] == 'E')
		game->angle_z = 3.14 * 0.5 + 3.14;
	else
		return (1);
	if (game->player_x != -1 || game->player_y != -1)
		return (0);
	game->player_x = x + 0.5;
	game->player_y = y + 0.5;
	game->map[y][x] = '0';
	return (1);
}

int	ft_get_pos(t_game *game)
{
	int			x;
	int			y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (!ft_select_pos(game, x, y))
				return (0);
			x++;
		}
		y++;
	}
	game->max_y = ft_splitlen(game->map);
	if (game->player_x == -1 || game->player_y == -1)
		return (0);
	return (1);
}

int	ft_is_double_y(char	**str, int y)
{
	int	x;

	x = 0;
	if (ft_strlen(str[y]) != ft_strlen(str[y - 1]))
		return (0);
	while (str[y][x] && str[y - 1][x])
	{
		if (str[y][x] != str[y - 1][x])
			return (0);
		x++;
	}
	return (1);
}

int	ft_is_double_x(char	**str, int x)
{
	int	y;

	y = 0;
	while (str[y] && str[y][x] && str[y][x - 1])
	{
		//printf("y : %d %d - %c %c\n", y, x, str[y][x], str[y][x + 1]);
		//if (str[y][x] != ' ' && str[y][x + 1] != ' ')
		if (str[y][x] != str[y][x - 1])
			return (0);
		y++;
	}
	return (1);
}

int	ft_nb_of(t_game *game, char	charset)
{
	int	x;
	int	y;
	int	total;

	x = 0;
	total = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == charset)
				total++;
			y++;
		}
		x++;
	}
	return (total);
}

void	ft_create_sprite(t_game *game, char *charset)
{
	int a;
	int	b;
	int	x;
	int	y;
	
	a = 0;
	b = 0;
    while (a < ft_strlen(charset))
    {
		y = 0;
        while (game->map[y])
		{
			x = 0;
			while (game->map[y][x])
			{
				if (game->map[y][x] == charset[a])
				{
					game->sprites[b].sx = x + 0.5;
					game->sprites[b].sy = y + 0.5;
					game->plan[2][b].a = 0;
					game->plan[2][b].b = 0;
					game->plan[2][b].c = 0;
					game->plan[2][b].d = 0;
					b++;
				}
				x++;
			}
			y++;
		}
		a++;
    }
}

int	ft_create_plan(t_game *game)
{
	int	x;
	int	next;

	x = 1;
	next = 0;
	game->plan = malloc(sizeof(t_plan *) * 3);
	if (!game->plan)
		return (0);
	game->plan[0] = malloc(sizeof(t_plan) * (game->max_y + 1));
	if (!game->plan[0])
		return (0);
	game->plan[1] = malloc(sizeof(t_plan) * (game->max_x + 1));
	if (!game->plan[1])
		return (0);
	game->nb_sprites = ft_nb_of(game, 'W') + ft_nb_of(game, 'T') + ft_nb_of(game, 'U') + ft_nb_of(game, 'V');
	if (game->nb_sprites != 0)
	{
		game->plan[2] = malloc(sizeof(t_plan) * game->nb_sprites);
		if (!game->plan[2])
			return (0);
		game->sprites = malloc(sizeof(t_sprite) * game->nb_sprites);
		if (!game->sprites)
			return (0);
		ft_create_sprite(game, "TUVW");
	}
	while (x < game->max_y - 1)
	{
		if ((!ft_is_double_y(game->map, x)))
		{
			dprintf(1, "x : \033[0;32m%s - %d\e[0m\n", game->map[x], x);
			//game->plan[0][x].a = 0;
			//game->plan[0][x].b = 0;
			//game->plan[0][x].c = 0;
			//game->plan[0][x].d = 0;
			//game->plan_x++;
			game->plan[0][x].a = 0;
			game->plan[0][x].b = 1;
			game->plan[0][x].c = 0;
			game->plan[0][x].d = -x;
		}
		else
		{
			dprintf(1, "x : \033[0;31m%s - %d\e[0m\n", game->map[x], x);
			game->plan[0][x].a = 0;
			game->plan[0][x].b = 0;
			game->plan[0][x].c = 0;
			game->plan[0][x].d = 0;			
			//game->plan[0][x].a = 0;
			//game->plan[0][x].b = 1;
			//game->plan[0][x].c = 0;
			//game->plan[0][x].d = -x;
		}
		x++;
	}
	x = 1;
	ft_printf("y :  ");
	while (x < game->max_x - 1)
	{
		if ((!ft_is_double_x(game->map, x)))
		{
			ft_printf("+");
			//game->plan[1][x].a = 0;
			//game->plan[1][x].b = 0;
			//game->plan[1][x].c = 0;
			//game->plan[1][x].d = 0;
			game->plan[1][x].a = 1;
			game->plan[1][x].b = 0;
			game->plan[1][x].c = 0;
			game->plan[1][x].d = -x;
			//game->plan_x++;
		}
		else
		{
			ft_printf("-");
			//game->plan[1][x].a = 1;
			//game->plan[1][x].b = 0;
			//game->plan[1][x].c = 0;
			//game->plan[1][x].d = -x;
			game->plan[1][x].a = 0;
			game->plan[1][x].b = 0;
			game->plan[1][x].c = 0;
			game->plan[1][x].d = 0;
		}
		x++;
	}
	ft_printf("\n");
	//while (x < game->max_x - 1)
	//{
	//	game->plan[1][x].a = 1;
	//	game->plan[1][x].b = 0;
	//	game->plan[1][x].c = 0;
	//	game->plan[1][x].d = -x;
	//	x++;
	//}
	/*x = 1;
	while (x < game->max_x - 1)
	{
		game->plan[1][x].a = 1;
		game->plan[1][x].b = 0;
		game->plan[1][x].c = 0;
		game->plan[1][x].d = -x;
		x++;
	}*/
	return (1);
}

void	ft_create_vector(t_game *game)
{
	int		i;
	int		j;
	float	r_h;
	float	r_v;

	i = 0;
	while (i < game->theight)
	{
		j = 0;
		while (j < game->twidth)
		{
			r_h = 2 * tan((60 * PI / 180) * 0.5) / game->twidth;
			r_v = 2 * tan((60 * PI / 180) * game->theight / (game->twidth * 2)) / game->theight;
			game->rayon[i][j].x = ((j - game->twidth * 0.5) * r_h);
			game->rayon[i][j].y = -1.0;
			game->rayon[i][j].z = ((game->theight * 0.5 - i) * r_v);
			j++;
		}
		i++;
	}
}

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

void ft_fps(t_game *game)
{
	static int	lframe = 0;
	static int	frame = 0;
	static int	total_frame = 0;
	static int	total_second = -1;
	static int64_t	fps = 0;
	char		*test;

	if (get_time() - fps < 1000)
	{
		frame++;
	}
	else
	{
		lframe = frame;
		fps = get_time();
		total_frame += frame;
		total_second += 1;
		frame = 1;
	}
	test = ft_itoa(lframe);
	mlx_string_put(game->graphic->mlx, game->graphic->win, 2, 10, 0xffffff, "FPS: ");
	mlx_string_put(game->graphic->mlx, game->graphic->win, 30, 10, 0xffffff, test);
	if (total_second > 1)
	{
		free(test);
		test = ft_itoa(total_frame / total_second);
		mlx_string_put(game->graphic->mlx, game->graphic->win, 2, 30, 0xffffff, "Moy FPS : ");
		mlx_string_put(game->graphic->mlx, game->graphic->win, 60, 30, 0xffffff, test);
	}
	free(test);
}

void ft_draw_square(t_img img, int y, int x, int max_y, int color, t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < max_y)
	{
		j = 0;
		while (j < max_y)
		{
			img.data[(i + x) * (game->twidth) + (j + y)] = color;
			j++;
		}
		i++;
	}
}

void ft_map(t_game *game, t_img img)
{
	int		i;
	int		j;
	int		x;
	int		y;

	//ft_draw_square(img, game->twidth - 25 * 10, 0, 25 * 10, 0x5e5e5e);
	i = (game->player_x * 4) - 25 * 4;
	if (i < 0)
		i = 0;
	x = 0;
	while (i < game->max_x * 4 && i < (game->player_x * 4) + 25 * 4)
	{
		j = (game->player_y * 4) - 25 * 4;
		if (j < 0)
			j = 0;
		y = 0;
		while (j < game->max_y * 4 && j < (game->player_y * 4) + 25 * 4)
		{
			if ((int)(i * 0.25) == (int)game->player_x && j * 0.25 == (int)game->player_y)
			{
				ft_draw_square(img, x + (game->twidth - (25 * 9)), y + 25, 4, 0xffffff, game);
				j += 3;
				y += 3;
			}
			else if (game->map[(int)(j * 0.25)][(int)(i * 0.25)] == '1')
				ft_draw_square(img, x + (game->twidth - (25 * 9)), y + 25, 4, 0x9000ff, game);
			else if (game->map[(int)(j * 0.25)][(int)(i * 0.25)] == '0')
				ft_draw_square(img, x + (game->twidth - (25 * 9)), y + 25, 4, 0x2205ff, game);
			//else
			//	ft_draw_square(img, x + (game->twidth - (25 * 9)), y + 25, 4, 0x5e5e5e);
			j++;
			y++;
		}
		x++;
		i++;
	}
}

void	ft_door(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->max_y)
	{
		x = 0;
		while (x < game->max_x)
		{
			if (game->map[y][x] == 'A')
				game->map[y][x] = 'B';
			else if (game->map[y][x] == 'B')
				game->map[y][x] = 'C';
			else if (game->map[y][x] == 'C')
				game->map[y][x] = 'D';
			else if (game->map[y][x] == 'D')
				game->map[y][x] = 'E';
			else if (game->map[y][x] == 'E')
				game->map[y][x] = 'A';
			x++;
		}
		y++;
	}
}

void	*ft_updater(void	*data)
{
	int		i;
	int		j;
	int		u;
	int		v;
	float	r;
	float	r_h;
	float	best_t;
	int		v_plan;
	int		u_plan;
	int		best_x;
	int		best_y;
	int		switch_plan;
	int		add;
	float	r_v;
	float	t;
	int		x;
	int		y;
	float	point_x;
	float	point_y;
	float	point_z;
	
	t_rayon	rayon_temp;
	t_rayon	rayon_tempp;
	t_img	img;
	t_update	*update;
	t_game		*game;

	update = (t_update *)data;
	game = update->game;
	x = 0;
	y = 0;
	i = update->start_y;
	while (i < update->end_y)
	{
		j = 0;
		while (j < game->twidth)
		{
			rayon_tempp.y = game->rayon[i][j].y * game->cos_x + game->rayon[i][j].z * -game->sin_x;
			rayon_tempp.z = game->rayon[i][j].y * game->sin_x + game->rayon[i][j].z * game->cos_x;
			rayon_temp.x = game->rayon[i][j].x  * game->cos_z + rayon_tempp.y * -game->sin_z;
			rayon_temp.y = game->rayon[i][j].x  * game->sin_z + rayon_tempp.y * game->cos_z;
			rayon_temp.z = game->rayon[i][j].y * game->sin_x + game->rayon[i][j].z * game->cos_x;
			v = 0;
			best_t = 0;
			v_plan = 4;
			u_plan = -7;
			best_x = -7;
			best_y = -7;
			while (v < 3)
			{
				if (v == 0)
				{
					switch_plan = game->max_y;
					u = game->player_y;
				}
				else if (v == 1)
				{
					switch_plan = game->max_x;
					u = game->player_x;
				}
				else if (v == 2)
				{
					switch_plan = game->nb_sprites - 1;
					u = 0;
				}
				add = 1;
				if ((v == 0 && rayon_temp.y < 0) || (v == 1 && rayon_temp.x < 0))
					add = -1;
				while (u <= switch_plan && u >= 0)
				{
					if (game->plan[v][u].a == 1 || game->plan[v][u].b == 1 || v == 2)
					{
						t = (game->plan[v][u].a * rayon_temp.x  + game->plan[v][u].b * rayon_temp.y + game->plan[v][u].c * rayon_temp.z);
						if (t != 0)
						{
							t = -(game->plan[v][u].a * game->player_x + game->plan[v][u].b * game->player_y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / t;
							if (t > 0)
							{
								point_x = rayon_temp.x * t;
								point_y = rayon_temp.y * t;
								point_z = 0.5 + rayon_temp.z * t;
								if (v != 2 && point_z < 1 && point_z > 0 && (int)(game->player_x + point_x) >= 0 && (int)(game->player_y + point_y) >= 0 && (int)(game->player_x + point_x) < game->max_x && (int)(game->player_y + point_y) < game->max_y)
								{
									if ((best_t == 0 || t < best_t) && ((v == 0 && (game->player_y + point_y) < game->player_y && (int)(-game->plan[v][u].d - 1) < game->max_y && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(-game->plan[v][u].d - 1)][(int)(game->player_x + point_x)] == '1')
									|| (v == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v][u].d - 1) < game->max_x && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v][u].d - 1)] == '1')
									|| (v == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v][u].d - 1) < game->max_x && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v][u].d - 1)] == 'A') //Porte
									|| (v == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v][u].d - 1) < game->max_x && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v][u].d - 1)] == 'B') //Porte
									|| (v == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v][u].d - 1) < game->max_x && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v][u].d - 1)] == 'C') //Porte
									|| (v == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v][u].d - 1) < game->max_x && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v][u].d - 1)] == 'D') //Porte
									|| (v == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v][u].d - 1) < game->max_x && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v][u].d - 1)] == 'E') //Porte
									|| (v == 0 && (game->player_y + point_y) > game->player_y && (int)(-game->plan[v][u].d) < game->max_y && (int)(-game->plan[v][u].d) >= 0 && game->map[(int)(-game->plan[v][u].d)][(int)(game->player_x + point_x)] == '1')
									|| (v == 1 && (game->player_x + point_x) > game->player_x && (int)(-game->plan[v][u].d) < game->max_x && (int)(-game->plan[v][u].d) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v][u].d)] == '1')))
									{
										best_t = t;
										v_plan = v;
										u_plan = u;
										u = -8;
									}
								}
								else if (v == 2)
								{
									if ((best_t == 0 || t < best_t) && point_z < 1.0 && point_z > 0.0 && (int)(game->player_x + point_x) >= 0 && (int)(game->player_y + point_y) >= 0 && (int)(game->player_x + point_x) < game->max_x && (int)(game->player_y + point_y) < game->max_y && game->map[(int)(game->player_y + point_y)][(int)(game->player_x + point_x)] == 'T')
									{
										float	ux, uy, sqrt1;
										ux = ((game->player_x + point_x) - game->sprites[u].sx);
										uy = ((game->player_y + point_y) - game->sprites[u].sy);
										sqrt1 = sqrt(pow(game->plan[v][u].b, 2) + pow(-game->plan[v][u].a, 2));
										r = ((ux * (game->plan[v][u].b / sqrt1)) + (uy * (-game->plan[v][u].a / sqrt1)) + 0.5);
										if (r >= 0 && r < 1)
										{
											x = r * game->img_s.size_l * 0.25;
											y = (int)((point_z - (int)(point_z)) * game->img_s.size_l * 0.25);
											if (game->img_s.data[(int)(y * (game->img_s.size_l * 0.25) + x)] != -16777216)
											{
												best_t = t;
												best_x = x;
												best_y = y;
												v_plan = v;
												u_plan = u;
											}
										}
									}
								}
								else if (point_z > 1.0 || point_z < 0.0)
								{
									if (point_z > 1.0)
										update->img->data[i * game->twidth + j] = game->ceiling_color;
									else
										update->img->data[i * game->twidth + j] = game->floor_color;
									u = -8;
								}
							}
						}
					}
					u += add;
				}
				v++;
			}
			if (best_t != 0 && v_plan != 4 && u_plan != - 7)
			{
				point_x = rayon_temp.x * best_t;
				point_y = rayon_temp.y * best_t;
				point_z = 0.5 + rayon_temp.z * best_t; // Si pas besoin de le stocker le mettre directement dans le if
				if (v_plan == 2 && best_x != - 7 && best_x != -7)
				{
					x = best_x;
					y = best_y;
					update->img->data[i * game->twidth + j] = game->img_s.data[(int)(y * (game->img_s.size_l * 0.25) + x)];
				}
				else if (v_plan == 0 && (game->player_y + point_y) < game->player_y && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_y && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(-game->plan[v_plan][u_plan].d - 1)][(int)(game->player_x + point_x)] == '1')
				{
					x = (int)(((game->player_x + point_x) - (int)(game->player_x + point_x)) * game->img_n.size_l * 0.25);
					y = (int)((point_z - (int)(point_z)) * game->img_n.size_l * 0.25);
					update->img->data[i * game->twidth + j] = game->img_n.data[(int)(y * (game->img_n.size_l * 0.25) + x)];
				}
				else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == '1')
				{
					x = (int)(((game->player_y + point_y) - (int)(game->player_y + point_y)) * game->img_w.size_l * 0.25);
					y = (int)((point_z - (int)(point_z)) * game->img_w.size_l * 0.25);
					update->img->data[i * game->twidth + j] = game->img_w.data[(int)(y * (game->img_w.size_l * 0.25) + x)];
				}
				// else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 'A')
				// {
				// 	update->img->data[i * game->twidth + j] = game->door_color[0];
				// }
				// else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 'B')
				// {
				// 	update->img->data[i * game->twidth + j] = game->door_color[1];
				// }
				// else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 'C')
				// {
				// 	update->img->data[i * game->twidth + j] = game->door_color[2];
				// }
				// else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 'D')
				// {
				// 	update->img->data[i * game->twidth + j] = game->door_color[3];
				// }
				// else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 'E')
				// {
				// 	update->img->data[i * game->twidth + j] = game->door_color[4];
				// }
				else if (v_plan == 0 && (game->player_y + point_y) > game->player_y && (int)(-game->plan[v_plan][u_plan].d) < game->max_y && (int)(-game->plan[v_plan][u_plan].d) >= 0 && game->map[(int)(-game->plan[v_plan][u_plan].d)][(int)(game->player_x + point_x)] == '1')
				{
					x = (int)(((game->player_x + point_x) - (int)(game->player_x + point_x)) * game->img_s.size_l * 0.25);
					y = (int)((point_z - (int)(point_z)) * game->img_s.size_l * 0.25);
					update->img->data[i * game->twidth + j] = game->img_s.data[(int)(y * (game->img_s.size_l * 0.25) + x)];
				}
				else
				{
					x = (int)(((game->player_y + point_y) - (int)(game->player_y + point_y)) * game->img_e.size_l * 0.25);
					y = (int)((point_z - (int)(point_z)) * game->img_e.size_l * 0.25);
					update->img->data[i * game->twidth + j] = game->img_e.data[(int)(y * (game->img_e.size_l * 0.25) + x)];
				}
			}
			y = 0;
			t = 0;
			j++;
		}
		i++;
	}
}

void	ft_set_sprites(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->nb_sprites)
	{
		game->plan[2][x].a = game->sprites[x].sx - game->player_x;
		game->plan[2][x].b = game->sprites[x].sy - game->player_y;
		game->plan[2][x].c = 0;
		game->plan[2][x].d = -(game->plan[2][x].a * game->sprites[x].sx) - (game->plan[2][x].b * game->sprites[x].sy);
		x++;
	}
}

void ft_put_image(t_game *game, t_img img2)
{
    int    i;
    int    j;
    t_img        img;

    img.img_ptr = mlx_new_image(game->graphic->mlx, WIDTH, HEIGHT);
    img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	i = 0;
    while (i < game->theight)
    {
        j = 0;
        while (j < game->twidth)
        {
            img.data[(i * 2) * WIDTH + (j * 2)] = img2.data[i * game->twidth + j];
			img.data[(i * 2) * WIDTH + (j * 2 + 1)] = img2.data[i * game->twidth + j];
			img.data[(i * 2 + 1) * WIDTH + (j * 2)] = img2.data[i * game->twidth + j];
			img.data[(i * 2 + 1) * WIDTH + (j * 2 + 1)] = img2.data[i * game->twidth + j];
			j++;
        }
		i++;
    }
    mlx_put_image_to_window(game->graphic->mlx, game->graphic->win, img.img_ptr, 0, 0);
    mlx_destroy_image(game->graphic->mlx, img.img_ptr);
}

int	ft_update(t_game *game)
{
	t_update	update[NB_THREAD];
	pthread_t	thread[NB_THREAD];
	t_img		img;
	int			x;

	ft_door(game);
	ft_move(game);
	ft_mouse(game);
	ft_set_sprites(game);
	img.img_ptr = mlx_new_image(game->graphic->mlx, game->twidth, game->theight);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	x = 0;
	while (x < NB_THREAD)
	{
		update[x].img = &img;
		if (x == 0)
			update[x].start_y = 0;
		else
			update[x].start_y = (x * game->theight) / NB_THREAD;
		update[x].end_y = ((x + 1) * game->theight) / NB_THREAD;
		update[x].game = game;
		pthread_create(&thread[x], NULL, &ft_updater, &update[x]);
		x++;
	}
	x = 0;
	while (x < NB_THREAD)
		pthread_join(thread[x++], NULL);
	ft_map(game, img);
	ft_put_image(game, img);
	//mlx_put_image_to_window(game->graphic->mlx, game->graphic->win, img.img_ptr, 0, 0);
	mlx_string_put(game->graphic->mlx, game->graphic->win, (WIDTH * 0.5) - 2, (HEIGHT * 0.5) + 4, 0xFF0000, "+");
	ft_fps(game);
	mlx_destroy_image(game->graphic->mlx, img.img_ptr);
	return (0);
}

t_rayon **ft_malloc_rayon(t_game *game)
{
	t_rayon		**rayon;
	int			x;

	x = 0;
	rayon = malloc(sizeof(t_rayon *) * game->theight + 1);
	while (x < game->theight)
	{
		rayon[x] = malloc(sizeof(t_rayon) * game->twidth + 1);
		x++;
	}
	return (rayon);
}

int	ft_image_len(char *str, int y)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (x > y - 1)
			if (x == y && str[x] != ' ')
				return (0);
		x++;
	}
	if (str[x - 1] == ' ' || x < y + 2)
		return (0);
	return (x);
}

int	ft_check_image(char *path)
{
	char	*ext;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	ext = ft_strrchr(path, '.');
	if (ext == NULL || ft_strncmp(".xpm", ext, ft_strlen(".xpm")) != 0)
		return (0);
	return (1);
}

void	*ft_open_xpm(t_game *game, char *str, int size_x)
{
	return (mlx_xpm_file_to_image(
			game->graphic->mlx, str, &size_x,
			&size_x));
}

int	ft_split_number(char **split)
{
	int	x;
	int	y;

	x = 0;
	while (split[x])
	{
		y = 0;
		while (split[x][y])
		{
			if (split[x][y] < '0' || split[x][y] > '9')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	ft_color_format(char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (ft_splitlen(split) != 3 || !ft_split_number(split))
	{
		ft_free_split(split);
		return (-1);
	}
	return ((ft_atoi(split[0]) << 16) + (ft_atoi(split[1]) << 8) + ft_atoi(split[2]));
}

int	ft_data_image(t_game *game)
{
	int	x;
	int	temp;
	int	t;
	int	value;

	if (ft_image_len(game->f, 1) == 0)
		return (0);
	game->floor_color = ft_color_format(game->f + 2);
	if (game->floor_color == -1)
		return (0);
	if (ft_image_len(game->c, 1) == 0)
		return (0);
	game->ceiling_color = ft_color_format(game->c + 2);
	if (game->ceiling_color == -1)
		return (0);
	x = 0;
	game->img_n.data = (int *)mlx_get_data_addr(game->img_n.img_ptr, &game->img_n.bpp, &game->img_n.size_l, &game->img_n.endian);
	value = game->img_n.size_l * 0.25 * game->img_n.size_l * 0.25;
	while (x < value / 2)
	{
		temp = game->img_n.data[x];
		game->img_n.data[x] = game->img_n.data[value - 1 - x];
		game->img_n.data[value - 1 - x] = temp;
		x++;
	}
	x = 0;
	t = 0;
	value = game->img_n.size_l * 0.25;
	while (x < (game->img_n.size_l * 0.25 * game->img_n.size_l * 0.25 - (game->img_n.size_l * 0.25 / 2)))
	{
		if (x >= value - game->img_n.size_l * 0.25 / 2)
		{
			x = value;
			t = 0;
			value += game->img_n.size_l * 0.25;
		}
		temp = game->img_n.data[x];
		game->img_n.data[x] = game->img_n.data[value - 1 - t];
		game->img_n.data[value - 1 - t] = temp;
		t++;
		x++;
	}
	x = 0;
	game->img_s.data = (int *)mlx_get_data_addr(game->img_s.img_ptr, &game->img_s.bpp, &game->img_s.size_l, &game->img_s.endian);
	value = game->img_s.size_l * 0.25 * game->img_s.size_l * 0.25;
	while (x < value / 2)
	{
		temp = game->img_s.data[x];
		game->img_s.data[x] = game->img_s.data[value - 1 - x];
		game->img_s.data[value - 1 - x] = temp;
		x++;
	}
	x = 0;
	game->img_e.data = (int *)mlx_get_data_addr(game->img_e.img_ptr, &game->img_e.bpp, &game->img_e.size_l, &game->img_e.endian);
	value = game->img_e.size_l * 0.25 * game->img_e.size_l * 0.25;
	while (x < value / 2)
	{
		temp = game->img_e.data[x];
		game->img_e.data[x] = game->img_e.data[value - 1 - x];
		game->img_e.data[value - 1 - x] = temp;
		x++;
	}
	x = 0;
	t = 0;
	value = game->img_e.size_l * 0.25;
	while (x < (game->img_e.size_l * 0.25 * game->img_e.size_l * 0.25 - (game->img_e.size_l * 0.25 / 2)))
	{
		if (x >= value - game->img_e.size_l * 0.25 / 2)
		{
			x = value;
			t = 0;
			value += game->img_e.size_l * 0.25;
		}
		temp = game->img_e.data[x];
		game->img_e.data[x] = game->img_e.data[value - 1 - t];
		game->img_e.data[value - 1 - t] = temp;
		t++;
		x++;
	}
	x = 0;
	game->img_w.data = (int *)mlx_get_data_addr(game->img_w.img_ptr, &game->img_w.bpp, &game->img_w.size_l, &game->img_w.endian);
	value = game->img_w.size_l * 0.25 * game->img_w.size_l * 0.25;
	while (x < value / 2)
	{
		temp = game->img_w.data[x];
		game->img_w.data[x] = game->img_w.data[value - 1 - x];
		game->img_w.data[value - 1 - x] = temp;
		x++;
	}
	x = 0;
	// t = 0;
	// value = game->img_w.size_l * 0.25;
	// while (x < (game->img_w.size_l * 0.25 * game->img_w.size_l * 0.25 - (game->img_w.size_l * 0.25 / 2)))
	// {
	// 	if (x >= value - game->img_w.size_l * 0.25 / 2)
	// 	{
	// 		x = value;
	// 		t = 0;
	// 		value += game->img_w.size_l * 0.25;
	// 	}
	// 	temp = game->img_w.data[x];
	// 	game->img_w.data[x] = game->img_w.data[value - 1 - t];
	// 	game->img_w.data[value - 1 - t] = temp;
	// 	t++;
	// 	x++;
	// }
	return (1);
}
int	ft_create_image(t_game *game)
{
	if (ft_image_len(game->n, 2) == 0)
		return (0);
	if (ft_check_image(game->n + 3))
		game->img_n.img_ptr = ft_open_xpm(game, game->n + 3, game->img_n.size_l);
	else
		return (0);
	if (ft_image_len(game->n, 2) == 0)
		return (0);
	if (ft_check_image(game->s + 3))
		game->img_s.img_ptr = ft_open_xpm(game, game->s + 3, game->img_s.size_l);
	else
		return (0);
	if (ft_image_len(game->n, 2) == 0)
		return (0);
	if (ft_check_image(game->w + 3))
		game->img_w.img_ptr = ft_open_xpm(game, game->w + 3, game->img_w.size_l);
	else
		return (0);
	if (ft_image_len(game->n, 2) == 0)
		return (0);
	if (ft_check_image(game->e + 3))
		game->img_e.img_ptr = ft_open_xpm(game, game->e + 3, game->img_e.size_l);
	else
		return (0);
	return (ft_data_image(game));
}

void ft_mouse(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->graphic->mlx, game->graphic->win, &x, &y);
	mlx_mouse_hide(game->graphic->mlx, game->graphic->win);
	if (x > game->twidth / 2)
		game->angle_z += 0.05;
	else if (x < game->twidth / 2)
		game->angle_z -= 0.05;
	if (y > game->theight / 2 && game->angle_x <= 0.75)
		game->angle_x += 0.025;
	else if (y < game->theight / 2 && game->angle_x >= -0.5)
		game->angle_x -= 0.025;
	mlx_mouse_move(game->graphic->mlx, game->graphic->win, game->twidth / 2, game->theight / 2);
}

void	*ft_music(void *data)
{
	t_game *game;

	game = (t_game *)data;
	while (42)
		system("afplay music.mp3");
}

void	ft_start_music(t_game *game, pthread_t music)
{
	if (MUSIC)
	{
		pthread_create(&music, NULL, ft_music, game);
		pthread_detach(music);
	}
}

void	ft_stop_music(t_game *game, pthread_t music)
{
	if (MUSIC)
		pthread_cancel(music);
}

int main(int argc, char *argv[])
{
	t_game		game;
	t_graphic	graphic;
	pthread_t	music;
	t_rayon		**rayon;

	game.twidth = WIDTH / 2;
	game.theight = HEIGHT / 2;
	game.keyboard.w = 0;
	game.keyboard.a = 0;
	game.keyboard.s = 0;
	game.keyboard.d = 0;
	game.keyboard.up = 0;
	game.keyboard.down = 0;
	game.keyboard.left = 0;
	game.keyboard.right = 0;
	game.door_color[0] = 0xFF0000;
	game.door_color[1] = 0x00FF00;
	game.door_color[2] = 0x0000FF;
	game.door_color[3] = 0xFFFF00;
	game.door_color[4] = 0x00FFFF;
	game.door_color[5] = 0xFF00FF;
	rayon = ft_malloc_rayon(&game);
	game.rayon = rayon;
	game.angle_x = 0;
	game.angle_z = 0;
	game.player_x = -1;
	game.player_y = -1;
	game.graphic = &graphic;
	graphic.map_check = &game;
	graphic.mlx = mlx_init();
	graphic.win = mlx_new_window(graphic.mlx, WIDTH, HEIGHT, "cub3d");
	if (ft_check_arg(argc, argv, &game)
		&& ft_create_image(&game) && ft_get_pos(&game))
	{
		ft_start_music(&game, music);
		ft_create_vector(&game);
		ft_create_plan(&game);
		mlx_loop_hook(graphic.mlx, ft_update, &game);
		mlx_mouse_hide(graphic.mlx, graphic.win);
		mlx_hook(graphic.win, 17, 1L << 17, ft_exit_hook, &game);
		mlx_hook(graphic.win, 02, 1L << 0, ft_win_event, &game);
		mlx_hook(graphic.win, 03, 1L << 1, ft_unpress, &game);
		mlx_mouse_hide(graphic.mlx, graphic.win);
		mlx_loop(graphic.mlx);
	}
	else
		ft_printf("Error\n");
	ft_stop_music(&game, music);
	ft_close(&game);
	return (0);
}
