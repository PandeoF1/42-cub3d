/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/02/21 17:48:48 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void ft_sprite(void *graphi)
{
	t_graphic *graphic;
	t_map_check *check;
	int x;
	int y;
	int uwu;
	int uwuw;
	void	*mlx;
	void	*mlx_win;

	graphic = (t_graphic *)graphi;
	check = graphic->map_check;
	mlx = graphic->mlx;
	mlx_win = graphic->mlx_win;
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
				while (uwu != 15)
					uwu++;
				while (uwu != 40)
				{
					uwuw = 0;
					while (uwuw != 15)
						mlx_pixel_put(mlx, mlx_win, (x * 50) + uwuw++, (y * 50) + uwu, 0x123456);
					while (uwuw != 40)
						mlx_pixel_put(mlx, mlx_win, (x * 50) + uwuw++, (y * 50) + uwu, 0x33FF4C);
					while (uwuw != 50)
						mlx_pixel_put(mlx, mlx_win, (x * 50) + uwuw++, (y * 50) + uwu, 0x123456);
					uwu++;
				}
			}
		}
	}
	x = 0;
	while (check->map[x])
	{
		y = 0;
		while (check->map[x][y])
		{
			if (check->map[x][y] == 'N')
			{
				int r = 2;
				int b;
				b = -r;
				while (b < r + 1)
				{
					printf("%d %d\n", abs((b * b) + (y * y) - (r * r)), r / 2);
					if (abs((b * b) + (y * y) - (r * r)) <= (r / 2))
					{
						ft_printf("uwu\n");
						mlx_pixel_put(mlx, mlx_win, (x * 50) + b, (y * 50) + b, 0xFF33E6);
					}
					b++;
				}
				
				
			}
			y++;
		}
		x++;
	}
	
}

void	ft_win_event(int keycode, void	*graphi)
{
	t_graphic *graphic;
	int		x;
	int		y;

	graphic = (t_graphic *)graphi;
	if (keycode == EVENT_W)
	{
		x = 0;
		while(graphic->map_check->map[x])
		{
			y = 0;
			while(graphic->map_check->map[x][y])
			{
				if (graphic->map_check->map[x][y] == 'N')
				{
					graphic->map_check->map[x][y] = '0';
					graphic->map_check->map[x - 1][y] = 'N';
					return ;
				}
				y++;
			}
			x++;
		}
	}
	else if (keycode == EVENT_S)
	{
		x = 0;
		while(graphic->map_check->map[x])
		{
			y = 0;
			while(graphic->map_check->map[x][y])
			{
				if (graphic->map_check->map[x][y] == 'N')
				{
					graphic->map_check->map[x][y] = '0';
					graphic->map_check->map[x + 1][y] = 'N';
					return ;
				}
				y++;
			}
			x++;
		}
	}
	else if (keycode == EVENT_A)
	{
		x = 0;
		while(graphic->map_check->map[x])
		{
			y = 0;
			while(graphic->map_check->map[x][y])
			{
				if (graphic->map_check->map[x][y] == 'N')
				{
					graphic->map_check->map[x][y] = '0';
					graphic->map_check->map[x][y - 1] = 'N';
					return ;
				}
				y++;
			}
			x++;
		}
	}
	else if (keycode == EVENT_D)
	{
		x = 0;
		while(graphic->map_check->map[x])
		{
			y = 0;
			while(graphic->map_check->map[x][y])
			{
				if (graphic->map_check->map[x][y] == 'N')
				{
					graphic->map_check->map[x][y] = '0';
					graphic->map_check->map[x][y + 1] = 'N';
					return ;
				}
				y++;
			}
			x++;
		}
	}
}

int main(int argc, char *argv[])
{
	void *mlx;
	void *mlx_win;
	t_map_check *check;
	int x;
	int y;
	int uwu;
	int uwuw;
	t_graphic graphic;

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
		graphic.mlx = mlx;
		check->axis = 0;
		graphic.mlx_win = mlx_win;
		graphic.map_check = check;

		mlx_key_hook(graphic.mlx_win, ft_win_event, &graphic);
		mlx_loop_hook(graphic.mlx, ft_sprite, &graphic);

		mlx_loop(mlx);
	}
	else
		ft_printf("Error\n");
	free(check);
	return (0);
}
/* for (y = -r; y < r+1; y++)  {   
                printf("\n");       
                for (x = -r; x < r+1 ; x++) {            
                         if(abs((x * x) + (y * y)-(r * r)) <= (r/2)) {                     
                                printf(" * ");                                         
                        }
                         else  {                                              
                                printf("   ");                       
                        }         
                }                
            } */