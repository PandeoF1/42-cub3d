/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/02/23 22:39:17 by tnard            ###   ########lyon.fr   */
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
	free(check);
}

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
}

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
}

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
	t_rayon	**rayon;

	rayon = check->rayon;
	ft_printf("test : %f\n", check->rayon[0][0].x);
	i = 0;
	while (i <= HEIGHT)
	{
		j = 0;
		while (j <= WIDTH)
		{
			r_h = 2 * tan((60 * PI / 180) * 0.5) / WIDTH;
			r_v = 2 * tan((60 * PI / 180) * HEIGHT / (WIDTH * 2)) / HEIGHT;
			ft_printf("uwu\n");
			printf("%p\n", check->rayon);
			rayon[i][j].x = ((j - WIDTH * 0.5) * r_h);
			rayon[i][j].y = -1.0;
			rayon[i][j].z = ((HEIGHT * 0.5 - i) * r_v);
			j++;
		}
		i++;
	}
}

void	ft_malloc_rayon(t_map_check *check)
{
	int		i;

	check->rayon = malloc(sizeof(t_rayon *) * HEIGHT + 1);
	i = 0;
	while (i <= HEIGHT)
	{
		check->rayon[i] = malloc(sizeof(t_rayon) * WIDTH + 1);
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

int main(int argc, char *argv[])
{
	int			x;
	t_plan		plan[4];
	t_map_check	*check;
	t_graphic	graphic;
	t_rayon		rayon[HEIGHT + 1][WIDTH + 1];

	x = 0;
	check = malloc(sizeof(t_map_check));
	if (ft_check_arg(argc, argv, check))
	{
		ft_get_pos(check);
		while (check->map[x])
			ft_printf("```%s```\n", check->map[x++]);
		check->graphic = &graphic;
		graphic.map_check = check;
		check->plan = plan;
		check->rayon = (t_rayon **)rayon;
		check->rayon[0][0].x = 123;
		printf("%p %p\n", rayon, check->rayon);
		ft_init_f(check);
		graphic.mlx = mlx_init();
		graphic.win = mlx_new_window(graphic.mlx, WIDTH, HEIGHT, "cub3d");
		//graphic->map_check = check;
		ft_create_plan(check);
		mlx_loop(graphic.mlx);
	}
	else
		ft_printf("Error\n");
	ft_free_check(check);
	return (0);
}
