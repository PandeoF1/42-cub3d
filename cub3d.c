/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/02/23 11:14:03 by tnard            ###   ########lyon.fr   */
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

void	ft_refresh(t_graphic *graphic, t_plan **plan)
{
	int		i;
	int		j;
	float	r_h;
	float	r_v;
	t_rayon	rayon[HEIGHT + 1][WIDTH + 1];

	i = 0;
	printf("Debug: refresh (debut calcul)\n");
	while (i <= HEIGHT)
	{
		j = 0;
		while (j <= WIDTH)
		{
			r_h = 2 * tan((60 * PI / 180) / 2) / WIDTH;
			r_v = 2 * tan((60 * PI / 180) * HEIGHT / (WIDTH * 2)) / HEIGHT;
			rayon[i][j].x = ((j - WIDTH * 0.5) * r_h);
			rayon[i][j].z = -1.0;
			rayon[i][j].y = ((HEIGHT * 0.5 - i) * r_v);
			j++;
		}
		i++;
		/*printf("---------------------------------\n");
		printf("r_h : (2 * tan((60 * %f / 180) / 2) / %d = %f\n", PI, WIDTH, r_h);
		printf("r_v : (2 * tan((60 * %f / 180) * %d / (%d * 2)) / %d) = %f\n", PI, HEIGHT, WIDTH, HEIGHT, r_v);
		printf("x : ((%d - %d * 0.5) * %f) = %f\n", j, WIDTH, r_h, rayon[i - 1][j - 1].x);
		printf("z : ((%d * 0.5 - %d) * %f) = %f\n", HEIGHT, i, r_v, rayon[i - 1][j - 1].y);
		printf("---------------------------------\n");*/
	}
	printf("Debug: fin calcul\n");
	/*printf("Vecteur 1 x : %f, %f, %f, %d %d\n", rayon[0][0].x, rayon[0][0].z, rayon[0][0].y, 0, 0);
	printf("Vecteur 2 x : %f, %f, %f, %d %d\n", rayon[0][WIDTH].x, rayon[0][WIDTH].z, rayon[0][WIDTH].y, 0, WIDTH);
	printf("Vecteur 3 x : %f, %f, %f, %d %d\n", rayon[HEIGHT][0].x, rayon[HEIGHT][0].z, rayon[HEIGHT][0].y, HEIGHT, 0);
	printf("Vecteur 4 x : %f, %f, %f, %d %d\n", rayon[HEIGHT][WIDTH].x, rayon[HEIGHT][WIDTH].z, rayon[HEIGHT][WIDTH].y, HEIGHT, WIDTH);*/
	printf("Debug: refresh (debut affichage)\n");
	
}

void	ft_get_pos(t_map_check *check)
{
	int	x;
	int	y;

	x = 0;
	while (check->map[x])
	{
		y = 0;
		while (check->map[x][y])
		{
			if (check->map[x][y] == 'N')
			{
				check->player_x = x;
				check->player_y = y;
			}
			y++;
		}
		x++;
	}
	check->max_y = ft_splitlen(check->map);
}

t_plan	**ft_malloc_plan(t_map_check *check)
{
	t_plan	**plan;
	int		i;

	plan = malloc(sizeof(t_plan *) * check->max_y);
	i = 0;
	while (i < check->max_y)
	{
		plan[i] = malloc(sizeof(t_plan) * check->max_x);
		i++;
	}
	return (plan);
}

void	ft_create_plan(t_map_check *check)
{
	t_plan	**plan;
	int		x;
	int		y;

	plan = ft_malloc_plan(check);
	y = 0;
	while (y < check->max_y)
	{
		x = 0;
		while (x < check->max_x)
		{
			plan[y][x].a = 1;
			plan[y][x].b = 0;
			plan[y][x].c = 0;
			if (check->map[y][x] == '1')
				plan[y][x].d = x;
			else
				plan[y][x].d = 0;
			x++;
		}
		y++;
	}
	ft_refresh(check->graphic, plan);
}

int main(int argc, char *argv[])
{
	int			x;
	t_map_check	*check;
	t_graphic	graphic;

	x = 0;
	check = malloc(sizeof(t_map_check));
	if (ft_check_arg(argc, argv, check))
	{
		ft_get_pos(check);
		while (check->map[x])
			ft_printf("```%s```\n", check->map[x++]);
		check->graphic = &graphic;
		graphic.mlx = mlx_init();
		ft_printf("uwu\n");
		graphic.win = mlx_new_window(graphic.mlx, WIDTH, HEIGHT, "cub3d");
		ft_printf("uwu\n");
		//graphic->map_check = check;
		ft_create_plan(check);
	}
	else
		ft_printf("Error\n");
	ft_free_check(check);
	return (0);
}
