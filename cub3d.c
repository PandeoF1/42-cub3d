/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/03/08 13:26:31 by asaffroy         ###   ########lyon.fr   */
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

int	ft_create_plan(t_game *game)
{
	int	x;

	x = 0;
	game->plan = malloc(sizeof(t_plan *) * 2);
	if (!game->plan)
		return (0);
	game->plan[0] = malloc(sizeof(t_plan) * (game->max_y + 1));
	if (!game->plan[0])
		return (0);
	game->plan[1] = malloc(sizeof(t_plan) * (game->max_x + 1));
	if (!game->plan[1])
		return (0);
	while (x <= game->max_y)
	{
		game->plan[0][x].a = 0;
		game->plan[0][x].b = 1;
		game->plan[0][x].c = 0;
		game->plan[0][x].d = -x;
		x++;
	}
	x = 0;
	while (x <= game->max_x)
	{
		game->plan[1][x].a = 1;
		game->plan[1][x].b = 0;
		game->plan[1][x].c = 0;
		game->plan[1][x].d = -x;
		x++;
	}
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
		frame = 1;
	}
	test = ft_itoa(lframe);
	mlx_string_put(game->graphic->mlx, game->graphic->win, 2, 10, 0xffffff, "FPS: ");
	mlx_string_put(game->graphic->mlx, game->graphic->win, 30, 10, 0xffffff, test);
	free(test);
}

void ft_draw_square(t_img img, int y, int x, int max_y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
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

	i = 0;
	while (i < game->max_x * 1)
	{
		j = 0;
		while (j < game->max_y * 1)
		{
			if ((int)(i * 0.25) == (int)game->player_x && j * 0.25 == (int)game->player_y)
			{
				ft_draw_square(img, i + (WIDTH - game->max_x * 4 - 3) , j, game->max_x, 0xffffff);
				j += 3;
			}
			else if (game->map[(int)(j * 0.25)][(int)(i * 0.25)] == '1')
				ft_draw_square(img, i + (WIDTH - game->max_x * 4 - 3) , j, game->max_x, 0x9000ff);
			else if (game->map[(int)(j * 0.25)][(int)(i * 0.25)] == '0' || game->map[(int)(j * 0.25)][(int)(i * 0.25)] == 'N')
				ft_draw_square(img, i + (WIDTH - game->max_x * 4 - 3), j, game->max_x, 0x2205ff);
			else
				ft_draw_square(img, i + (WIDTH - game->max_x * 4 - 3), j, game->max_x, 0x5e5e5e);
			j++;
		}
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
	float	r_h;
	float	best_t;
	int		v_plan;
	int		u_plan;
	int		switch_plan;
	int		add;
	float	r_v;
	float	t;
	float	x;
	float	y;
	float	point_x;
	float	point_y;
	float	point_z;
	
	t_rayon	rayon_temp;
	t_img	img;
	t_update	*update;
	t_game		*game;

	update = (t_update *)data;
	game = update->game;
	x = 0;
	y = 0;
	while (update->status == -1)
		usleep(1);
	i = update->start_y;
	while (i < update->end_y)
	{
		j = 0;
		while (j < WIDTH)
		{
			rayon_temp.x = game->rayon[i][j].x * cos(game->angle_z) + game->rayon[i][j].y * -sin(game->angle_z); //z
			rayon_temp.y = game->rayon[i][j].x * sin(game->angle_z) + game->rayon[i][j].y * cos(game->angle_z);
			rayon_temp.z = game->rayon[i][j].z * 1;
			v = 0;
			best_t = 0;
			v_plan = 3;
			u_plan = -7;
			while (v < 2)
			{
				u = 0;
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
				add = 1;
				if (v == 0 && rayon_temp.y < 0)
					add = -1;
				else if (v == 1 && rayon_temp.x < 0)
					add = -1;
				while (u <= switch_plan && u >= 0)
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
							if (point_z < 1 && point_z > 0 && (int)(game->player_x + point_x) >= 0 && (int)(game->player_y + point_y) >= 0 && (int)(game->player_x + point_x) < game->max_x && (int)(game->player_y + point_y) < game->max_y)
							{
								if ((best_t == 0 || t < best_t) && ((v == 0 && (game->player_y + point_y) < game->player_y && (int)(-game->plan[v][u].d) < game->max_y && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(-game->plan[v][u].d - 1)][(int)(game->player_x + point_x)] == '1')
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
							else if (point_z > 1.0 || point_z < 0.0)
							{
								if (point_z > 1.0)
								{
									// int x, y;
									// x = (int)(((game->player_x + point_x) - (int)(game->player_x + point_x)) * game->img_n.size_l * 0.25);
									// y = (int)((point_z - (int)(point_z)) * game->img_n.size_l * 0.25);
									// update->img->data[i * WIDTH + j] = game->img_n.data[(int)(y * (game->img_n.size_l * 0.25) + x)];
									update->img->data[i * WIDTH + j] = game->ceiling_color;
								}
								else
									update->img->data[i * WIDTH + j] = game->floor_color;
								u = -8;
							}
						}
					}
					u += add;
				}
				v++;
			}
			if (best_t != 0 && v_plan != 3 && u_plan != - 7)
			{
				int	x, y;
				point_x = rayon_temp.x * best_t;
				point_y = rayon_temp.y * best_t;
				point_z = 0.5 + rayon_temp.z * best_t; // Si pas besoin de le stocker le mettre directement dans le if
				if (v_plan == 0 && (game->player_y + point_y) < game->player_y && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_y && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(-game->plan[v_plan][u_plan].d - 1)][(int)(game->player_x + point_x)] == '1')
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
				//else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 'A')
				//{
				//	update->img->data[i * WIDTH + j] = game->door_color[0];
				//}
				//else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 'B')
				//{
				//	update->img->data[i * WIDTH + j] = game->door_color[1];
				//}
				//else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 'C')
				//{
				//	update->img->data[i * WIDTH + j] = game->door_color[2];
				//}
				//else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 'D')
				//{
				//	update->img->data[i * WIDTH + j] = game->door_color[3];
				//}
				//else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 'E')
				//{
				//	update->img->data[i * WIDTH + j] = game->door_color[4];
				//}
				else if (v_plan == 0 && (game->player_y + point_y) > game->player_y && (int)(-game->plan[v_plan][u_plan].d) < game->max_y && (int)(-game->plan[v_plan][u_plan].d) >= 0 && game->map[(int)(-game->plan[v_plan][u_plan].d)][(int)(game->player_x + point_x)] == '1')
				{
					x = (int)(((game->player_x + point_x) - (int)(game->player_x + point_x)) * game->img_s.size_l * 0.25);
					y = (int)((point_z - (int)(point_z)) * game->img_s.size_l * 0.25);
					update->img->data[i * WIDTH + j] = game->img_s.data[(int)(y * (game->img_s.size_l * 0.25) + x)];
				}
				else
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
	update->status = 1;
}

int	ft_update(t_game *game)
{
	t_update	update[NB_THREAD];
	pthread_t	thread[NB_THREAD];
	t_img		img;
	int			x;

	ft_door(game);
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
		update[x].status = 0;
		update[x].game = game;
		pthread_create(&thread[x], NULL, &ft_updater, &update[x]);
		x++;
	}
	x = 0;
	while (x < NB_THREAD)
	{
		update[x].status = 0;
		pthread_join(thread[x], NULL);
		x++;
	}
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
	while (value < (game->img_w.size_l * 0.25 *  game->img_w.size_l * 0.25))
	{
		if (x == value)
		{
			x = value;
			t = 0;
			value += (game->img_w.size_l * 0.25);
		}
		temp = game->img_w.data[x];
		game->img_w.data[x] = game->img_w.data[value - 1 - t];
		game->img_w.data[value - 1 - t] = temp;
		t++;
		x++;
	}
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
	if (x == WIDTH / 2)
		game->angle_z += 0;
	else if (x > WIDTH / 2)
		game->angle_z += 0.025;
	else
		game->angle_z -= 0.025;
	mlx_mouse_move(game->graphic->mlx, game->graphic->win, WIDTH / 2, HEIGHT / 2);
}

int main(int argc, char *argv[])
{
	t_game		game;
	t_graphic	graphic;
	t_rayon		**rayon;

	game.door_color[0] = 0xFF0000;
	game.door_color[1] = 0x00FF00;
	game.door_color[2] = 0x0000FF;
	game.door_color[3] = 0xFFFF00;
	game.door_color[4] = 0x00FFFF;
	game.door_color[5] = 0xFF00FF;
	rayon = ft_malloc_rayon();
	game.rayon = rayon;
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
		ft_create_vector(&game);
		ft_create_plan(&game);
		mlx_loop_hook(graphic.mlx, ft_update, &game);
		mlx_hook(graphic.win, 2, 2, ft_press, &game);
		mlx_hook(graphic.win, 3, 3, ft_unpress, &game);
		mlx_mouse_hide(graphic.mlx, graphic.win);
		mlx_hook(graphic.win, 17, 1L << 17, ft_exit_hook, &game);
		mlx_loop(graphic.mlx);
	}
	else
		ft_printf("Error\n");
	ft_close(&game);
	return (0);
}
