/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/02/22 14:50:10 by tnard            ###   ########lyon.fr   */
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

void	ft_refresh(t_graphic *graphic)
{
	ft_printf("Debug: refresh\n");
}

int main(int argc, char *argv[])
{
	int			x;
	void		*mlx;
	void		*mlx_win;
	t_map_check	*check;
	t_graphic	graphic;

	x = 0;
	check = malloc(sizeof(t_map_check));
	if (ft_check_arg(argc, argv, check))
	{
		while (check->map[x])
			ft_printf("```%s```\n", check->map[x++]);

		mlx = mlx_init();
		
		mlx_win = mlx_new_window(mlx,
								50,
								 50, "so_long | v1.0");
		//ft_refresh(&graphic);
		ft_printf("uwu\n");
		mlx_loop(mlx);
		/*x = -1;
		y = -1;
		mlx = mlx_init();
		
		mlx_win = mlx_new_window(mlx,
								 check->max_x * 50,
								 (ft_splitlen(check->map)) * 50, "so_long | v1.0");
		graphic.mlx = mlx;
		check->axis = 0;
		graphic.mlx_win = mlx_win;
		graphic.map_check = check;

		mlx_key_hook(graphic.mlx_win, ft_win_event, &graphic);
		mlx_loop_hook(graphic.mlx, ft_sprite, &graphic);

		mlx_loop(mlx);*/
	}
	else
		ft_printf("Error\n");
	ft_free_check(check);
	return (0);
}
