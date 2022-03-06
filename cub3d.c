/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/03/06 07:50:17 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int64_t	g_fps;
int		g_frame;
int		g_lframe;

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
	printf("\nCub3d: exit\n");
}

void	ft_get_pos(t_game *game)
{
	int			x;
	int			y;
	double		var;

	y = -1;
	while (game->map[++y])
	{
		x = 0;
		while (game->map[y][x])
		{	
			//if (game->map[y][x] == 'N')
			//	var = -3.14 / 2;
			//else if (game->map[y][x] == 'S')
			//	var = 3.14 / 2;
			//else if (game->map[y][x] == 'W')
			//	var = 3.14;
			if (game->map[y][x] == 'N')
			{
				game->player_x = x + 0.5;
				game->player_y = y + 0.5;
			}
			x++;
		}
	}
	game->max_y = ft_splitlen(game->map);
}

int	ft_create_plan(t_game *game)
{
	int	x;

	x = 0;
	game->plan = malloc (sizeof(t_plan *) * 2);
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
	if (!game->plan[1])
		return (0);
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

int	ft_update(t_game *game)
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
	float	r_v;
	float	t;
	float	x;
	float	y;
	float	point_x;
	float	point_y;
	float	point_z;
	
	t_rayon	rayon_temp;
	t_img	img;

	ft_mouse(game);
	img.img_ptr = mlx_new_image(game->graphic->mlx, WIDTH, HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	x = 0;
	y = 0;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			rayon_temp.x = game->rayon[i][j].x * cos(game->angle_z) + game->rayon[i][j].y * -sin(game->angle_z) + game->rayon[i][j].z * 0; //z
			rayon_temp.y = game->rayon[i][j].x * sin(game->angle_z) + game->rayon[i][j].y * cos(game->angle_z) + game->rayon[i][j].z * 0;
			rayon_temp.z = game->rayon[i][j].x * 0 + game->rayon[i][j].y * 0 + game->rayon[i][j].z * 1;
			//rayon_temp.x = rayon_temp.x * 1 + rayon_temp.y * 0 + rayon_temp.z * 0; //x
			//rayon_temp.y = rayon_temp.x * 0 + rayon_temp.y * cos(game->angle_x) + rayon_temp.z * -sin(game->angle_x);
			//rayon_temp.z = rayon_temp.x * 0 + rayon_temp.y * sin(game->angle_x) + rayon_temp.z * cos(game->angle_x);
			v = 0;
			best_t = 0;
			v_plan = 3;
			u_plan = -7;
			while (v < 2)
			{
				if (v == 0)
					switch_plan = game->max_y;
				else
					switch_plan = game->max_x;
				u = 0;
				while (u <= switch_plan)
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
								|| (v == 0 && (game->player_y + point_y) > game->player_y && (int)(-game->plan[v][u].d) < game->max_y && (int)(-game->plan[v][u].d) >= 0 && game->map[(int)(-game->plan[v][u].d)][(int)(game->player_x + point_x)] == '1')
								|| (v == 1 && (game->player_x + point_x) > game->player_x && (int)(-game->plan[v][u].d) < game->max_x && (int)(-game->plan[v][u].d) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v][u].d)] == '1')))
								{
									best_t = t;
									v_plan = v;
									u_plan = u;
								}
							}
						}
					}
					u++;
				}
				v++;
			}
			if (best_t != 0 && v_plan != 3 && u_plan != - 7)
			{
				point_x = rayon_temp.x * best_t;
				point_y = rayon_temp.y * best_t;
				point_z = 0.5 + rayon_temp.z * best_t; // Si pas besoin de le stocker le mettre directement dans le if
				if (v_plan == 0 && (game->player_y + point_y) < game->player_y && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_y && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(-game->plan[v_plan][u_plan].d - 1)][(int)(game->player_x + point_x)] == '1')
				{
					//ft_get_pixel
					img.data[i * WIDTH + j] = 0xfce5cd; //beige
				}
				else if (v_plan == 1 && (game->player_x + point_x) < game->player_x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->max_x && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->player_y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == '1')
				{
					int	x, y;
					float	fx, fy;
					x = (int)(((int)(point_y) - point_y) * game->img_n.size_l * 0.25); // * 0.25 car y a 64 * 4 pixels
					y = (int)(((int)(point_z) - point_z) * game->img_n.size_l * 0.25);
					y = -y;
					x = -x;
					//printf("x : %d y : %d | size : %d | color : 0x%08.8X\n", x, y, (int)(game->img_n.size_l * 0.25), game->img_n.data[(int)(x * (game->img_n.size_l * 0.25) + y)]);
					img.data[i * WIDTH + j] = game->img_n.data[(int)(y * (game->img_n.size_l * 0.25) + x)];
				}
				else if (v_plan == 0 && (game->player_y + point_y) > game->player_y && (int)(-game->plan[v_plan][u_plan].d) < game->max_y && (int)(-game->plan[v_plan][u_plan].d) >= 0 && game->map[(int)(-game->plan[v_plan][u_plan].d)][(int)(game->player_x + point_x)] == '1')
					img.data[i * WIDTH + j] = 0x90fff2; // bleu clair
				else
					img.data[i * WIDTH + j] = 0xcaffa0; //vert clair
			}
			y = 0;
			t = 0;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->graphic->mlx, game->graphic->win, img.img_ptr, 0, 0);
	mlx_destroy_image(game->graphic->mlx, img.img_ptr);
	if (get_time() - g_fps < 1000)
	{
		g_frame++;
	}
	else
	{
		ft_printf("\033[2K\r");
		dprintf(1, "FPS: %d - POS: x - %f | y - %f - Angle : %f", g_frame, game->player_x, game->player_y, game->angle_z);
		ft_printf("\e[0m");
		g_lframe = g_frame;
		g_fps = get_time();
		g_frame = 0;
	}
	char *test;
	test = ft_itoa(g_lframe);
	mlx_string_put(game->graphic->mlx, game->graphic->win, 2, 10, 0xffffff, "FPS: ");
	mlx_string_put(game->graphic->mlx, game->graphic->win, 30, 10, 0xffffff, test);
	free(test);
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

int	ft_image_len(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (x > 1)
			if (x == 2 && str[x] != ' ')
				return (0);
		x++;
	}
	if (str[x - 1] == ' ' || x < 4)
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

int	ft_data_image(t_game *game)
{
	game->img_n.data = (int *)mlx_get_data_addr(game->img_n.img_ptr, &game->img_n.bpp, &game->img_n.size_l, &game->img_n.endian);
	game->img_s.data = (int *)mlx_get_data_addr(game->img_s.img_ptr, &game->img_s.bpp, &game->img_s.size_l, &game->img_s.endian);
	game->img_e.data = (int *)mlx_get_data_addr(game->img_e.img_ptr, &game->img_e.bpp, &game->img_e.size_l, &game->img_e.endian);
	game->img_w.data = (int *)mlx_get_data_addr(game->img_w.img_ptr, &game->img_w.bpp, &game->img_w.size_l, &game->img_w.endian);
	return (1);
}

int	ft_create_image(t_game *game)
{
	if (ft_image_len(game->n) == 0)
		return (0);
	if (ft_check_image(game->n + 3))
		game->img_n.img_ptr = ft_open_xpm(game, game->n + 3, game->img_n.size_l);
	else
		return (0);
	if (ft_image_len(game->n) == 0)
		return (0);
	if (ft_check_image(game->s + 3))
		game->img_s.img_ptr = ft_open_xpm(game, game->s + 3, game->img_s.size_l);
	else
		return (0);
	if (ft_image_len(game->n) == 0)
		return (0);
	if (ft_check_image(game->w + 3))
		game->img_w.img_ptr = ft_open_xpm(game, game->w + 3, game->img_w.size_l);
	else
		return (0);
	if (ft_image_len(game->n) == 0)
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
		game->angle_z += 0.1;
	else
		game->angle_z -= 0.1;
	mlx_mouse_move(game->graphic->mlx, game->graphic->win, WIDTH / 2, HEIGHT / 2);
}

int main(int argc, char *argv[])
{
	t_game		game;
	t_graphic	graphic;
	t_rayon		**rayon;

	g_fps = get_time();
	rayon = ft_malloc_rayon();
	game.rayon = rayon;
	game.angle_x = 0;
	game.angle_z = 0;
	game.graphic = &graphic;
	graphic.map_check = &game;
	graphic.mlx = mlx_init();
	graphic.win = mlx_new_window(graphic.mlx, WIDTH, HEIGHT, "cub3d");
	if (ft_check_arg(argc, argv, &game) && ft_create_image(&game))
	{
		ft_get_pos(&game);
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
