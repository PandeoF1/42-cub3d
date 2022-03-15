/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/03/14 12:57:39 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	ft_free_rayon(t_rayon **rayon)
{
	int			x;

	x = 0;
	while (x < HEIGHT)
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
	ft_free_rayon(game->rayon);
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

int	ft_is_door(char c)
{
	int	x;

	x = 0;
	while (x < DOOR_LEN)
	{
		if (c == DOOR_CHAR[x])
			return (x + 1);
		x++;
	}
	return (0);
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

int	ft_nb_of(t_game *game, char charset)
{
	int		x;
	int		y;
	int		total;

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

void	ft_create_door(t_game *game)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_is_door(game->map[y][x]) != 0)
			{
				game->plan[3][i].a = 0;
				game->plan[3][i].b = 1;
				game->plan[3][i].c = 0;
				game->plan[3][i].d = -y - 0.75;
				printf("plan created %d\n", i);
				i++;
				break ;
			}
			x++;
		}
		y++;
	}
}

int	ft_door_count(t_game *game)
{
	int		x;
	int		y;
	int		total;

	x = 0;
	total = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (ft_is_door(game->map[x][y]) != 0)
			{
				total++;
				break;
			}
			y++;
		}
		x++;
	}
	return (total);
}

int	ft_create_plan(t_game *game)
{
	int	x;
	int	next;

	game->nb_door = ft_door_count(game);
	printf("nb_door : %d\n", game->nb_door);
	next = 0;
	game->plan = malloc(sizeof(t_plan *) * 5);
	if (!game->plan)
		return (0);
	game->plan[0] = malloc(sizeof(t_plan) * (game->max_y + 1));
	if (!game->plan[0])
		return (0);
	game->plan[1] = malloc(sizeof(t_plan) * (game->max_x + 1));
	if (!game->plan[1])
		return (0);
	game->plan[3] = malloc(sizeof(t_plan) * game->nb_door);
	if (!game->plan[3])
		return (0);
	//game->plan[4] = malloc(sizeof(t_plan) * game->nb_door);
	//if (!game->plan[4])
	//	return (0);
	x = 0;
	ft_create_door(game);
	x = 1;
	while (x < game->max_y - 1)
	{
		if ((!ft_is_double_y(game->map, x)))
		{
			ft_printf("x : \033[0;32m%s - %d\e[0m\n", game->map[x], x);
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
			ft_printf("x : \033[0;31m%s - %d\e[0m\n", game->map[x], x);
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
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			r_h = 2 * tan((60 * PI / 180) * 0.5) / WIDTH;
			r_v = 2 * tan((60 * PI / 180) * HEIGHT / (WIDTH * 2)) / HEIGHT;
			game->rayon[i][j].x = ((j - WIDTH * 0.5) * r_h);
			game->rayon[i][j].y = -1.0;
			game->rayon[i][j].z = ((HEIGHT * 0.5 - i) * r_v);
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

void ft_draw_square(t_img img, int y, int x, int max_y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < max_y)
	{
		j = 0;
		while (j < max_y)
		{
			img.data[(i + x) * (WIDTH) + (j + y)] = color;
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

	//ft_draw_square(img, WIDTH - 25 * 10, 0, 25 * 10, 0x5e5e5e);
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
				ft_draw_square(img, x + (WIDTH - (25 * 9)), y + 25, 4, 0xffffff);
				j += 3;
				y += 3;
			}
			else if (game->map[(int)(j * 0.25)][(int)(i * 0.25)] == '1')
				ft_draw_square(img, x + (WIDTH - (25 * 9)), y + 25, 4, 0x9000ff);
			else if (game->map[(int)(j * 0.25)][(int)(i * 0.25)] == '0' || game->map[(int)(j * 0.25)][(int)(i * 0.25)] == 'X')
				ft_draw_square(img, x + (WIDTH - (25 * 9)), y + 25, 4, 0x2205ff);
			else if (ft_is_door(game->map[(int)(j * 0.25)][(int)(i * 0.25)]) != 0)
				ft_draw_square(img, x + (WIDTH - (25 * 9)), y + 25, 4, 0xFF20500);
			j++;
			y++;
		}
		x++;
		i++;
	}
}

void	ft_door(t_game *game)
{
	static int64_t	timer = 0;
	int				x;
	int				y;
	float			t_x;
	float			t_y;

	if (timer == 0 || get_time() - timer > 150)
		timer = get_time();
	else
		return ;
	y = 0;
	while (y < game->max_y)
	{
		x = 0;
		while (x < game->max_x)
		{
			t_x = x - game->player_x;
			t_y = y - game->player_y;
			if (t_x < 0)
				t_x = -t_x;
			if (t_y < 0)
				t_y = -t_y;
			if (t_x < 2.5 && t_y < 2.5)
			{
				if (game->map[y][x] == DOOR_CHAR[0])
					game->map[y][x] = DOOR_CHAR[1];
				else if (game->map[y][x] == DOOR_CHAR[1])
					game->map[y][x] = DOOR_CHAR[2];
				else if (game->map[y][x] == DOOR_CHAR[2])
					game->map[y][x] = DOOR_CHAR[3];
				else if (game->map[y][x] == DOOR_CHAR[3])
					game->map[y][x] = 'X';
			}
			else
			{
				if (game->map[y][x] == DOOR_CHAR[1])
					game->map[y][x] = DOOR_CHAR[0];
				else if (game->map[y][x] == DOOR_CHAR[2])
					game->map[y][x] = DOOR_CHAR[1];
				else if (game->map[y][x] == DOOR_CHAR[3])
					game->map[y][x] = DOOR_CHAR[2];
				else if (game->map[y][x] == 'X')
					game->map[y][x] = DOOR_CHAR[3];
				
			}
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
	float	r_h;
	float	best_t;
	int		v_plan;
	int		u_plan;
	int		switch_plan;
	int		add;
	float	r_v;
	float	t;
	int		x;
	int		y;
	float	point_x;
	float	point_y;
	float	point_z;
	int		door;
	
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
		while (j < WIDTH)
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
			while (v < 4)
			{
				if (v == 2) //car ton plan existe pas
					v++;
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
				else if (v == 3)
				{
					switch_plan = game->nb_door;
					u = 0;
				}
				add = 1;
				if (v == 0 && rayon_temp.y < 0)
					add = -1;
				else if (v == 1 && rayon_temp.x < 0)
					add = -1;
				else if (v == 3 && rayon_temp.y < 0)
				{
					add = -1;
					u = game->nb_door;
				}
				while (u <= switch_plan && u >= 0)
				{
					if (game->plan[v][u].a == 1 || game->plan[v][u].b == 1)
					{
						t = (game->plan[v][u].a * rayon_temp.x  + game->plan[v][u].b * rayon_temp.y + game->plan[v][u].c * rayon_temp.z);
						if (t != 0)
						{
							t = -(game->plan[v][u].a * game->player_x + game->plan[v][u].b * game->player_y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / t;
							if (t > best_t && best_t != 0)
								u = -8;
							else if (t > 0)
							{
								point_x = rayon_temp.x * t;
								point_y = rayon_temp.y * t;
								point_z = 0.5 + rayon_temp.z * t;
								if (point_z < 1 && point_z > 0 && (int)(game->player_x + point_x) >= 0 && (int)(game->player_y + point_y) >= 0 && (int)(game->player_x + point_x) < game->max_x && (int)(game->player_y + point_y) < game->max_y)
								{
									if ((best_t == 0 || t < best_t) && ((v == 0 && (game->player_y + point_y) < game->player_y && (int)(-game->plan[v][u].d) < game->max_y && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(-game->plan[v][u].d - 1)][(int)(game->player_x + point_x)] == '1')
									|| (v == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v][u].d - 1) < game->max_x && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v][u].d - 1)] == '1')
									|| (v == 0 && (game->player_y + point_y) > game->player_y && (int)(-game->plan[v][u].d) < game->max_y && (int)(-game->plan[v][u].d) >= 0 && game->map[(int)(-game->plan[v][u].d)][(int)(game->player_x + point_x)] == '1')
									|| (v == 1 && (game->player_x + point_x) > game->player_x && (int)(-game->plan[v][u].d) < game->max_x && (int)(-game->plan[v][u].d) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v][u].d)] == '1')
									|| (v == 3 && (game->player_y + point_y) > game->player_y && (int)(-game->plan[v][u].d) < game->max_y && (int)(-game->plan[v][u].d) >= 0 && ft_is_door(game->map[(int)(-game->plan[v][u].d)][(int)(game->player_x + point_x)]) != 0)
									|| (v == 3 && (game->player_y + point_y) < game->player_y && (int)(-game->plan[v][u].d) < game->max_y && (int)(-game->plan[v][u].d - 0.5) >= 0 && ft_is_door(game->map[(int)(-game->plan[v][u].d - 0.5)][(int)(game->player_x + point_x)]) != 0)))
									{
										if (v == 3)
										{
											door = 0;
											if ((game->player_y + point_y) > game->player_y && (int)(-game->plan[v][u].d) < game->max_y && (int)(-game->plan[v][u].d) >= 0 && ft_is_door(game->map[(int)(-game->plan[v][u].d)][(int)(game->player_x + point_x)]) != 0)
												door = ft_is_door(game->map[(int)(-game->plan[v][u].d)][(int)(game->player_x + point_x)]) - 1;
											else if ((game->player_y + point_y) < game->player_y && (int)(-game->plan[v][u].d) < game->max_y && (int)(-game->plan[v][u].d - 0.5) >= 0 && ft_is_door(game->map[(int)(-game->plan[v][u].d - 0.5)][(int)(game->player_x + point_x)]) != 0)
												door = ft_is_door(game->map[(int)(-game->plan[v][u].d - 0.5)][(int)(game->player_x + point_x)]) - 1;
											if (door != 4)
											{
												x = (int)(((game->player_x + point_x) - (int)(game->player_x + point_x)) * game->door_color[door].size_l * 0.25);
												y = (int)((point_z - (int)(point_z)) * game->door_color[door].size_l * 0.25);
												if (game->door_color[door].data[(int)(y * (game->door_color[door].size_l * 0.25) + x)] != -16777216)
												{
													best_t = t;
													v_plan = v;
													u_plan = u;
													u = -8;
												}
											}
										}
										else
										{
											best_t = t;
											v_plan = v;
											u_plan = u;
											u = -8;
										}
									}
								}
								else if (point_z > 1.0 || point_z < 0.0)
								{
									if (point_z > 1.0)
										update->img->data[i * WIDTH + j] = game->ceiling_color;
									else
										update->img->data[i * WIDTH + j] = game->floor_color;
									u = -8;
								}
							}
						}
					}
					u += add;
				}
				v++;
			}
			if (best_t != 0 && v_plan != 5 && u_plan != - 7)
			{
				point_x = rayon_temp.x * best_t;
				point_y = rayon_temp.y * best_t;
				point_z = 0.5 + rayon_temp.z * best_t; // Si pas besoin de le stocker le mettre directement dans le if
				if (v_plan == 3 && (game->player_y + point_y) > game->player_y && (int)(-game->plan[v_plan][u_plan].d) < game->max_y && (int)(-game->plan[v_plan][u_plan].d) >= 0 && ft_is_door(game->map[(int)(-game->plan[v_plan][u_plan].d)][(int)(game->player_x + point_x)]) != 0)
				{
					door = ft_is_door(game->map[(int)(-game->plan[v_plan][u_plan].d)][(int)(game->player_x + point_x)]) - 1;
					if (door != 4)
					{
						x = (int)(((game->player_x + point_x) - (int)(game->player_x + point_x)) * game->door_color[door].size_l * 0.25);
						y = (int)((point_z - (int)(point_z)) * game->door_color[door].size_l * 0.25);
						update->img->data[i * WIDTH + j] = game->door_color[door].data[(int)(y * (game->door_color[door].size_l * 0.25) + x)];
					}
				}
				else if (v_plan == 3 && (game->player_y + point_y) < game->player_y && (int)(-game->plan[v_plan][u_plan].d - 0.5) < game->max_y && (int)(-game->plan[v_plan][u_plan].d - 0.5) >= 0 && ft_is_door(game->map[(int)(-game->plan[v_plan][u_plan].d - 0.5)][(int)(game->player_x + point_x)]) != 0)
				{
					door = ft_is_door(game->map[(int)(-game->plan[v_plan][u_plan].d)][(int)(game->player_x + point_x)]) - 1;
					if (door != 4)
					{
						x = (int)(((game->player_x + point_x) - (int)(game->player_x + point_x)) * game->door_color[door].size_l * 0.25);
						y = (int)((point_z - (int)(point_z)) * game->door_color[door].size_l * 0.25);
						update->img->data[i * WIDTH + j] = game->door_color[door].data[(int)(y * (game->door_color[door].size_l * 0.25) + x)];
					}
				}
				else if (v_plan == 0 && (game->player_y + point_y) < game->player_y && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_y && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(-game->plan[v_plan][u_plan].d - 1)][(int)(game->player_x + point_x)] == '1')
				{
					x = (int)(((game->player_x + point_x) - (int)(game->player_x + point_x)) * game->img_n.size_l * 0.25);
					y = (int)((point_z - (int)(point_z)) * game->img_n.size_l * 0.25);
					update->img->data[i * WIDTH + j] = game->img_n.data[(int)(y * (game->img_n.size_l * 0.25) + x)];
				}
				else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == '1')
				{
					x = (int)(((game->player_y + point_y) - (int)(game->player_y + point_y)) * game->img_e.size_l * 0.25);
					y = (int)((point_z - (int)(point_z)) * game->img_e.size_l * 0.25);
					update->img->data[i * WIDTH + j] = game->img_e.data[(int)(y * (game->img_e.size_l * 0.25) + x)];
				}
				else if (v_plan == 0 && (game->player_y + point_y) > game->player_y && (int)(-game->plan[v_plan][u_plan].d) < game->max_y && (int)(-game->plan[v_plan][u_plan].d) >= 0 && game->map[(int)(-game->plan[v_plan][u_plan].d)][(int)(game->player_x + point_x)] == '1')
				{
					x = (int)(((game->player_x + point_x) - (int)(game->player_x + point_x)) * game->img_s.size_l * 0.25);
					y = (int)((point_z - (int)(point_z)) * game->img_s.size_l * 0.25);
					update->img->data[i * WIDTH + j] = game->img_s.data[(int)(y * (game->img_s.size_l * 0.25) + x)];
				}
				else if (v_plan == 0 || v_plan == 1)
				{
					x = (int)(((game->player_y + point_y) - (int)(game->player_y + point_y)) * game->img_w.size_l * 0.25);
					y = (int)((point_z - (int)(point_z)) * game->img_w.size_l * 0.25);
					update->img->data[i * WIDTH + j] = game->img_w.data[(int)(y * (game->img_w.size_l * 0.25) + x)];
				}
			}
			y = 0;
			t = 0;
			j++;
		}
		i++;
	}
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
	img.img_ptr = mlx_new_image(game->graphic->mlx, WIDTH, HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	x = 0;
	while (x < NB_THREAD)
	{
		update[x].img = &img;
		if (x == 0)
			update[x].start_y = 0;
		else
			update[x].start_y = (x * HEIGHT) / NB_THREAD;
		update[x].end_y = ((x + 1) * HEIGHT) / NB_THREAD;
		update[x].game = game;
		pthread_create(&thread[x], NULL, &ft_updater, &update[x]);
		x++;
	}
	x = 0;
	while (x < NB_THREAD)
		pthread_join(thread[x++], NULL);
	ft_map(game, img);
	mlx_put_image_to_window(game->graphic->mlx, game->graphic->win, img.img_ptr, 0, 0);
	mlx_string_put(game->graphic->mlx, game->graphic->win, (WIDTH * 0.5) - 2, (HEIGHT * 0.5) + 4, 0xFF0000, "+");
	ft_fps(game);
	mlx_destroy_image(game->graphic->mlx, img.img_ptr);
	return (0);
}

t_rayon **ft_malloc_rayon(void)
{
	t_rayon		**rayon;
	int			x;

	x = 0;
	rayon = malloc(sizeof(t_rayon *) * HEIGHT + 1);
	while (x < HEIGHT)
	{
		rayon[x] = malloc(sizeof(t_rayon) * WIDTH + 1);
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
	while (x < (game->img_n.size_l * 0.25 *  game->img_n.size_l * 0.25))
	{
		if (x == value)
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
	t = 0;
	value = game->img_w.size_l * 0.25;
	while (x < (game->img_w.size_l * 0.25 *  game->img_w.size_l * 0.25))
	{
		if (x == value)
		{
			x = value;
			t = 0;
			value += game->img_w.size_l * 0.25;
		}
		temp = game->img_w.data[x];
		game->img_w.data[x] = game->img_w.data[value - 1 - t];
		game->img_w.data[value - 1 - t] = temp;
		t++;
		x++;
	}
	game->door_color[0].img_ptr = ft_open_xpm(game, "./img/door/door1.xpm", game->door_color[0].size_l);
	game->door_color[1].img_ptr = ft_open_xpm(game, "./img/door/door2.xpm", game->door_color[1].size_l);
	game->door_color[2].img_ptr = ft_open_xpm(game, "./img/door/door3.xpm", game->door_color[2].size_l);
	game->door_color[3].img_ptr = ft_open_xpm(game, "./img/door/door4.xpm", game->door_color[3].size_l);
	game->door_color[0].data = (int *)mlx_get_data_addr(game->door_color[0].img_ptr, &game->door_color[0].bpp, &game->door_color[0].size_l, &game->door_color[0].endian);
	game->door_color[1].data = (int *)mlx_get_data_addr(game->door_color[1].img_ptr, &game->door_color[1].bpp, &game->door_color[1].size_l, &game->door_color[1].endian);
	game->door_color[2].data = (int *)mlx_get_data_addr(game->door_color[2].img_ptr, &game->door_color[2].bpp, &game->door_color[2].size_l, &game->door_color[2].endian);
	game->door_color[3].data = (int *)mlx_get_data_addr(game->door_color[3].img_ptr, &game->door_color[3].bpp, &game->door_color[3].size_l, &game->door_color[3].endian);
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
	if (x > WIDTH / 2)
		game->angle_z += 0.05;
	else if (x < WIDTH / 2)
		game->angle_z -= 0.05;
	if (y > HEIGHT / 2 && game->angle_x <= 0.75)
		game->angle_x += 0.025;
	else if (y < HEIGHT / 2 && game->angle_x >= -0.5)
		game->angle_x -= 0.025;
	mlx_mouse_move(game->graphic->mlx, game->graphic->win, WIDTH / 2, HEIGHT / 2);
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

	game.keyboard.w = 0;
	game.keyboard.a = 0;
	game.keyboard.s = 0;
	game.keyboard.d = 0;
	game.keyboard.up = 0;
	game.keyboard.down = 0;
	game.keyboard.left = 0;
	game.keyboard.right = 0;
	dprintf(1, "Welcome to the game\n");
	rayon = ft_malloc_rayon();
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
