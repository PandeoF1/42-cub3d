/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/02/24 11:24:14 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

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

void	ft_create_plan(t_map_check *check)
{
	check->plan[0] = (t_plan){0, 1, 0, 10};
	check->plan[1] = (t_plan){1, 0, 0, 10};
	check->plan[2] = (t_plan){0, -1, 0, 10};
	check->plan[3] = (t_plan){-1, 0, 0, 10};
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
	ft_printf("debut vector\n");
	ft_create_vector(check);
	ft_printf("fin vector\n");
	ft_create_plan(check);
	ft_printf("fin init\n");
}

int	ft_update(t_map_check *check)
{
	int		i;
	int		j;
	int		u;
	float	r_h;
	float	r_v;
	float	t;
	float	x;
	float	y;
	float	point_x;
	float	point_y;
	float	point_z;

	x = 0;
	y = 0;
	i = 0;
	dprintf(1, "Debug: refresh (debut calcul)\n");
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			u = 0;
			while (u < 4)
			{
				t = (check->plan[u].a * check->rayon[i][j].x + check->plan[u].b * check->rayon[i][j].y + check->plan[u].c * check->rayon[i][j].z);
				if (t != 0) //Stock avant de refaire
				{
					t = -(check->plan[u].a * 0.0 + check->plan[u].b * 0.0 + check->plan[u].c * 0.5 + check->plan[u].d) / t;
					if (t > 0)
					{
						point_x = 0 + check->rayon[i][j].x * t;
						point_y = 0 + check->rayon[i][j].y * t;
						point_z = 0.5 + check->rayon[i][j].z * t; // Si pas besoin de le stocker le foutre directement dans le if
						if (point_z < 1 && point_z > 0)
						{
							if (u == 0)
								mlx_pixel_put(check->graphic->mlx, check->graphic->win, j, i, 0x0000FE);
							if (u == 1)
								mlx_pixel_put(check->graphic->mlx, check->graphic->win, j, i, 0xFE0000);
							if (u == 2)
								mlx_pixel_put(check->graphic->mlx, check->graphic->win, j, i, 0x00FF0F);
							if (u == 3)
								mlx_pixel_put(check->graphic->mlx, check->graphic->win, j, i, 0x00E8FF);
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

int main(int argc, char *argv[])
{
	int			x;
	t_plan		plan[4];
	t_map_check	check;
	//t_map_check	*check;
	t_graphic	graphic;
	t_rayon		**rayon;

	x = 0;
	rayon = ft_malloc_rayon();
	check.rayon = rayon;
	rayon[0][0].x = 123;
	printf("%p %p\n", rayon, check.rayon);
	printf("rayon : %f\n", rayon[0][0].x);
	printf("checkrayon : %f\n", check.rayon[0][0].x);
	//check = malloc(sizeof(t_map_check));
	if (ft_check_arg(argc, argv, &check))
	{
		ft_get_pos(&check);
		while (check.map[x])
			ft_printf("```%s```\n", check.map[x++]);
		check.graphic = &graphic;
		graphic.map_check = &check;
		check.plan = plan;
		ft_init_f(&check);
		graphic.mlx = mlx_init();
		graphic.win = mlx_new_window(graphic.mlx, WIDTH, HEIGHT, "cub3d");
		mlx_loop_hook(graphic.mlx, ft_update, &check);
		//ft_create_plan(&check);
		mlx_loop(graphic.mlx);
	}
	else
		ft_printf("Error\n");
	ft_free_check(&check);
	return (0);
}
