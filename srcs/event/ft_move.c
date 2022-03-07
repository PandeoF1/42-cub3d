/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:52:09 by tnard             #+#    #+#             */
/*   Updated: 2022/03/05 22:52:09 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_move_next(int keycode, t_game *game)
{	
	if (keycode == EVENT_A)
	{
		if (game->map[(int)(game->player_y - sin(game->angle_z) * 0.20)]
			[(int)(game->player_x - cos(game->angle_z) * 0.20)] != '1')
		{
			game->player_x -= cos(game->angle_z) * 0.1;
			game->player_y -= sin(game->angle_z) * 0.1;
		}
	}
	if (keycode == EVENT_D)
	{
		if (game->map[(int)(game->player_y + sin(game->angle_z) * 0.20)]
			[(int)(game->player_x + cos(game->angle_z) * 0.20)] != '1')
		{
			game->player_x += cos(game->angle_z) * 0.1;
			game->player_y += sin(game->angle_z) * 0.1;
		}
	}
}
void	ft_move(int keycode, t_game *game)
{
	if (keycode == EVENT_W)
	{
		if (game->map[(int)(game->player_y - cos(game->angle_z) * 0.20)]
			[(int)(game->player_x + sin(game->angle_z) * 0.20)] != '1')
		{
			game->player_x += sin(game->angle_z) * 0.1;
			game->player_y -= cos(game->angle_z) * 0.1;
		}
	}
	if (keycode == EVENT_S)
	{
		if (game->map[(int)(game->player_y + cos(game->angle_z) * 0.20)]
			[(int)(game->player_x - sin(game->angle_z) * 0.20)] != '1')
		{
			game->player_x -= sin(game->angle_z) * 0.1;
			game->player_y += cos(game->angle_z) * 0.1;
		}
	}
	ft_move_next(keycode, game);
}
