/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/02/22 10:33:05 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int main(int argc, char *argv[])
{
	int			x;
	t_map_check *check;

	x = 0;
	check = malloc(sizeof(t_map_check));
	if (ft_check_arg(argc, argv, check))
	{
		while (check->map[x])
			ft_printf("```%s```\n", check->map[x++]);
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