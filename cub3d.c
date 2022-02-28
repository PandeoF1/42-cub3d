/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/02/28 15:24:22 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int64_t	g_fps;
int		g_frame;

void	ft_free_check(t_map_check *check)
{
	if (check->map)
		ft_free_split(check->map);
	if (check->n)
		free(check->n);
	if (check->s)
		free(check->s);
	if (check->e)
		free(check->e);
	if (check->w)
		free(check->w);
	if (check->f)
		free(check->f);
	if (check->c)
		free(check->c);
//	free(check);
}
/*
void	ft_refresh(t_graphic *graphic, t_plan *plan)
{
	int		i;
	int		j;
	float	r_h;
	float	r_v;
	float	t;
	float	x;
	float	y;
	float	point_x;
	float	point_y;
	float	point_z;

	t_rayon	rayon[HEIGHT + 1][WIDTH + 1];

	x = 0;
	y = 0;

	i = 0;
	printf("Debug: refresh (debut calcul)\n");
	while (i <= HEIGHT)
	{
		j = 0;
		while (j <= WIDTH)
		{
			r_h = 2 * tan((60 * PI / 180) * 0.5) / WIDTH;
			r_v = 2 * tan((60 * PI / 180) * HEIGHT / (WIDTH * 2)) / HEIGHT;
			rayon[i][j].x = ((j - WIDTH * 0.5) * r_h);
			rayon[i][j].y = -1.0;
			rayon[i][j].z = ((HEIGHT * 0.5 - i) * r_v);
			int	u;
			u = 0;
			while (u < 4)
			{
				t = (plan[u].a * rayon[i][j].x + plan[u].b * rayon[i][j].y + plan[u].c * rayon[i][j].z);
				if (t != 0) //Stock avant de refaire
				{
					t = -(plan[u].a * 0.0 + plan[u].b * 0.0 + plan[u].c * 0.5 + plan[u].d) / t;
					if (t > 0)
					{
						point_x = 0 + rayon[i][j].x * t;
						point_y = 0 + rayon[i][j].y * t;
						point_z = 0.5 + rayon[i][j].z * t; // Si pas besoin de le stocker le foutre directement dans le if
						if (point_z < 1 && point_z > 0)
						{
							if (u == 0)
								mlx_pixel_put(graphic->mlx, graphic->win, j, i, 0x0000FE);
							if (u == 1)
								mlx_pixel_put(graphic->mlx, graphic->win, j, i, 0xFE0000);
							if (u == 2)
								mlx_pixel_put(graphic->mlx, graphic->win, j, i, 0x00FF0F);
							if (u == 3)
								mlx_pixel_put(graphic->mlx, graphic->win, j, i, 0x00E8FF);
						}
					}
				}
				u++;
			}
			
			y = 0;
			t = 0;
			j++;
		}
		i++;
	}
	printf("rayon 0 0 : (%f, %f, %f)\n", rayon[0][0].x, rayon[0][0].y, rayon[0][0].z);
	printf("Debug: fin calcul\n");
	printf("Debug: refresh (debut affichage)\n");
	printf("Debug: refresh (fin affichage)\n");
}*/

void	ft_get_pos(t_map_check *check)
{
	int	x;
	int	y;

	y = 0;
	while (check->map[y])
	{
		x = 0;
		while (check->map[y][x])
		{
			if (check->map[y][x] == 'N')
			{
				check->player_x = x;
				check->player_y = y;
			}
			x++;
		}
		y++;
	}
	check->max_y = ft_splitlen(check->map);
}
/*
t_plan	**ft_malloc_plan(t_map_check *check)
{
	t_plan	**plan;
	int		i;

	plan = malloc(sizeof(t_plan *) * check->max_y + 1);
	i = 0;
	while (i <= check->max_y)
	{
		plan[i] = malloc(sizeof(t_plan) * check->max_x + 1);
		i++;
	}
	return (plan);
}*/

int	ft_create_plan(t_map_check *check)
{
	int	x;

	x = 0;
	check->plan = malloc (sizeof(t_plan *) * 2);
	if (!check->plan)
		return (0);
	check->plan[0] = malloc(sizeof(t_plan) * (check->max_y + 1));
	if (!check->plan[0])
		return (0);
	check->plan[1] = malloc(sizeof(t_plan) * (check->max_x + 1));
	if (!check->plan[1])
		return (0);
	while (x <= check->max_y)
	{
		check->plan[0][x].a = 0;
		check->plan[0][x].b = 1;
		check->plan[0][x].c = 0;
		check->plan[0][x].d = -x;
		x++;
	}
	x = 0;
	while (x <= check->max_x)
	{
		check->plan[1][x].a = 1;
		check->plan[1][x].b = 0;
		check->plan[1][x].c = 0;
		check->plan[1][x].d = -x;
		x++;
	}
	return (1);
	// check->plan[0] = (t_plan){0, 1, 0, 5};//bleu fonce
	// check->plan[2] = (t_plan){0, 1, 0, -15};//vert
	// check->plan[1] = (t_plan){1, 0, 0, -15};// rouge
	// check->plan[3] = (t_plan){1, 0, 0, -25};//bleu clair
}

void	ft_create_vector(t_map_check *check)
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
			check->rayon[i][j].x = ((j - WIDTH * 0.5) * r_h);
			check->rayon[i][j].y = -1.0;
			check->rayon[i][j].z = ((HEIGHT * 0.5 - i) * r_v);
			j++;
		}
		i++;
	}
}

void	ft_init_f(t_map_check *check)
{
	ft_create_vector(check);
	ft_printf("fin vector\n");
	if (ft_create_plan(check) == 0)
		return ;
	ft_printf("fin init\n");
}

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_update(t_map_check *check)
{
	int		i;
	int		j;
	int		u;
	int		v;
	float	r_h;
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

	img.img_ptr = mlx_new_image(check->graphic->mlx, WIDTH, HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
    //addr = mlx_get_data_addr(image, );
	x = 0;
	y = 0;
	i = 0;
	//dprintf(1, "Debug: refresh (debut calcul) %f %f %f %f\n", uwua, uwub, uwuc, uwud);
	//mlx_clear_window(check->graphic->mlx, check->graphic->win);
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			v = 0;
			rayon_temp.x = check->rayon[i][j].x * cos(check->angle_z) + check->rayon[i][j].y * -sin(check->angle_z) + check->rayon[i][j].z * 0; //z
			rayon_temp.y = check->rayon[i][j].x * sin(check->angle_z) + check->rayon[i][j].y * cos(check->angle_z) + check->rayon[i][j].z * 0;
			rayon_temp.z = check->rayon[i][j].x * 0 + check->rayon[i][j].y * 0 + check->rayon[i][j].z * 1;
			// rayon_temp.x = rayon_temp.x * 1 + rayon_temp.y * 0 + rayon_temp.z * 0; //x
			// rayon_temp.y = rayon_temp.x * 0 + rayon_temp.y * cos(check->angle_x) + rayon_temp.z * -sin(check->angle_x);
			// rayon_temp.z = rayon_temp.x * 0 + rayon_temp.y * sin(check->angle_x) + rayon_temp.z * cos(check->angle_x);
			while (v < 2)
			{
				if (v == 0)
					switch_plan = check->max_y;
				else
					switch_plan = check->max_x;
				u = 0;
				while (u <= switch_plan)
				{
					t = (check->plan[v][u].a * rayon_temp.x  + check->plan[v][u].b * rayon_temp.y + check->plan[v][u].c * rayon_temp.z);
					if (t != 0)
					{
						t = -(check->plan[v][u].a * check->player_x + check->plan[v][u].b * check->player_y + check->plan[v][u].c * 0.5 + check->plan[v][u].d) / t;
						if (t > 0)
						{
							point_x = rayon_temp.x * t;
							point_y = rayon_temp.y * t;
							point_z = 0.5 + rayon_temp.z * t; // Si pas besoin de le stocker le mettre directement dans le if
							if (point_z < 1 && point_z > 0 && (int)(check->player_x + point_x) >= 0 && (int)(check->player_y + point_y) >= 0 && (int)(check->player_x + point_x) < check->max_x && (int)(check->player_y + point_y) < check->max_y)
							{
								if (v == 0 && (check->player_y + point_y) < check->player_y && (int)(-check->plan[v][u].d - 1) < check->max_y && (int)(-check->plan[v][u].d - 1) >= 0 && check->map[(int)(-check->plan[v][u].d - 1)][(int)(check->player_x + point_x)] == '1')
								{
									img.data[i * WIDTH + j] = 0xfce5cd;
									u = switch_plan + 1;
									v = 2;
								}
								else if (v == 1 && (check->player_x + point_x) < check->player_x && (int)(-check->plan[v][u].d - 1) < check->max_x && (int)(-check->plan[v][u].d - 1) >= 0 && check->map[(int)(check->player_y + point_y)][(int)(-check->plan[v][u].d - 1)] == '1')
								{
									img.data[i * WIDTH + j] = 0xffb2b2;
									u = switch_plan + 1;
									v = 2;
								}
								else if (v == 0 && (check->player_y + point_y) > check->player_y && (int)(-check->plan[v][u].d) < check->max_y && (int)(-check->plan[v][u].d) >= 0 && check->map[(int)(-check->plan[v][u].d)][(int)(check->player_x + point_x)] == '1')
								{
									img.data[i * WIDTH + j] = 0x90fff2;
									u = switch_plan + 1;
									v = 2;
								}
								else if (v == 1 && (check->player_x + point_x) > check->player_x && (int)(-check->plan[v][u].d) < check->max_x && (int)(-check->plan[v][u].d) >= 0 && check->map[(int)(check->player_y + point_y)][(int)(-check->plan[v][u].d)] == '1')
								{
									img.data[i * WIDTH + j] = 0xcaffa0;
									u = switch_plan + 1;
									v = 2;
								}
							}
						}
					}
					u++;
				}
				v++;
			}
			y = 0;
			t = 0;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(check->graphic->mlx, check->graphic->win, img.img_ptr, 0, 0);
	mlx_destroy_image(check->graphic->mlx, img.img_ptr);
	if (get_time() - g_fps < 1000)
	{
		g_frame++;
	}
	else
	{
		ft_printf("\033[2K\rFPS: %d\e[0m", g_frame);
		g_fps = get_time();
		g_frame = 0;
	}
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

int	ft_win_event(int keycode, t_map_check *check)
{
	return (0);
}

int	ft_press(int keycode, t_map_check *check)
{
	//printf("angle: %f\n", check->angle_z);
	if (keycode == EVENT_W)
	{
		check->player_y -= 0.5;
		//check->player_x = check->player_x * cos(check->angle_z) + check->player_y * -sin(check->angle_z); //z
		//check->player_y = check->player_x * sin(check->angle_z) + check->player_y * cos(check->angle_z);
	}
	if (keycode == EVENT_S)
		check->player_y += 0.5;
	if (keycode == EVENT_A)
		check->player_x -= 0.5;
	if (keycode == EVENT_D)
		check->player_x += 0.5;
	if (keycode == 65363)
		check->angle_z += 0.07;
	if (keycode == 65361)
		check->angle_z -= 0.07;
	if (keycode == 65362) // bonus
		if (check->angle_x > -0.2)
			check->angle_x -= 0.01;
	if (keycode == 65364)
		if (check->angle_x < 0.2)
			check->angle_x += 0.01;
	return (0);
}

int	ft_unpress(int keycode, t_map_check *check)
{
	//ft_printf("unpress\n");
	return (0);
}

int main(int argc, char *argv[])
{
	int			x;
	t_map_check	check;
	//t_map_check	*check;
	t_graphic	graphic;
	t_rayon		**rayon;

	g_fps = get_time();
	x = 0;
	rayon = ft_malloc_rayon();
	check.rayon = rayon;
	check.angle_x = 0;
	check.angle_z = 0;
	if (ft_check_arg(argc, argv, &check))
	{
		ft_printf("error\n");
		ft_get_pos(&check);
		while (check.map[x])
			ft_printf("```%s```\n", check.map[x++]);
		check.graphic = &graphic;
		graphic.map_check = &check;
		ft_init_f(&check);
		graphic.mlx = mlx_init();
		graphic.win = mlx_new_window(graphic.mlx, WIDTH, HEIGHT, "cub3d");
		//mlx_key_hook(graphic.win, ft_win_event, &check);
		mlx_loop_hook(graphic.mlx, ft_update, &check);
		mlx_hook(graphic.win, 2, 2, ft_press, &check);
		mlx_hook(graphic.win, 3, 3, ft_unpress, &check);
		//ft_create_plan(&check);
		mlx_loop(graphic.mlx);
	}
	else
		ft_printf("Error\n");
	ft_free_check(&check);
	return (0);
}
