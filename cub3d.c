/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/02/21 17:01:33 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char *argv[])
{
	void		*mlx;
	void		*mlx_win;
	t_map_check	*check;
	int			x;
	int			y;
	int			uwu;
	int			uwuw;

	x = 0;
	check = malloc(sizeof(t_map_check));
	if (ft_check_arg(argc, argv, check))
	{
		while (check->map[x])
			ft_printf("```%s```\n", check->map[x++]);
		x = -1;
		y = -1;
		mlx = mlx_init();
		mlx_win = mlx_new_window(mlx,
				check->max_x * 50,
				(ft_splitlen(check->map)) * 50, "so_long | v1.0");
		while (++y * 50 < (ft_splitlen(check->map)) * 50)
		{
			x = -1;
			while (++x * 50 < check->max_x * 50)
			{
				if (check->map[y][x] == '1')
				{
					uwu = 0;
					while (uwu != 50)
					{
						uwuw = 0;
						while (uwuw != 50)
							mlx_pixel_put(mlx, mlx_win, (x * 50) + uwuw++, (y * 50) + uwu, 0xFFFFFF);
						uwu++;
					}
				}
				else if (check->map[y][x] == '0')
				{
					uwu = 0;
					while (uwu != 50)
					{
						uwuw = 0;
						while (uwuw != 50)
							mlx_pixel_put(mlx, mlx_win, (x * 50) + uwuw++, (y * 50) + uwu, 0x123456);
						uwu++;
					}
				}
				else if (check->map[y][x] == ' ')
				{
					uwu = 0;
					while (uwu != 50)
					{
						uwuw = 0;
						while (uwuw != 50)
							mlx_pixel_put(mlx, mlx_win, (x * 50) + uwuw++, (y * 50) + uwu, 0x543210);
						uwu++;
					}
				}
				else if (check->map[y][x] == 'N')
				{
					uwu = 0;
					while (uwu != 50)
					{
						uwuw = 0;
						while (uwuw != 50)
							mlx_pixel_put(mlx, mlx_win, (x * 50) + uwuw++, (y * 50) + uwu, 0x33FF4C);
						uwu++;
					}
				}
			}
		}
		mlx_loop(mlx);
	}
	else
		ft_printf("Error\n");
	free(check);
	return (0);
}
