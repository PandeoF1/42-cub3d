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
		if (game->map[(int)(game->player_y - sin(game->angle_z) * 0.30)]
			[(int)(game->player_x - cos(game->angle_z) * 0.30)] != '1')
		{
			game->player_x -= cos(game->angle_z) * 0.2;
			game->player_y -= sin(game->angle_z) * 0.2;
		}
	}
	if (keycode == EVENT_D)
	{
		if (game->map[(int)(game->player_y + sin(game->angle_z) * 0.30)]
			[(int)(game->player_x + cos(game->angle_z) * 0.30)] != '1')
		{
			game->player_x += cos(game->angle_z) * 0.2;
			game->player_y += sin(game->angle_z) * 0.2;
		}
	}
}

void	ft_move(int keycode, t_game *game)
{
	if (keycode == EVENT_W)
	{
		if (game->map[(int)(game->player_y - cos(game->angle_z) * 0.30)]
			[(int)(game->player_x + sin(game->angle_z) * 0.30)] != '1')
		{
			game->player_x += sin(game->angle_z) * 0.2;
			game->player_y -= cos(game->angle_z) * 0.2;
		}
	}
	if (keycode == EVENT_S)
	{
		if (game->map[(int)(game->player_y + cos(game->angle_z) * 0.30)]
			[(int)(game->player_x - sin(game->angle_z) * 0.30)] != '1')
		{
			game->player_x -= sin(game->angle_z) * 0.2;
			game->player_y += cos(game->angle_z) * 0.2;
		}
	}
	ft_move_next(keycode, game);
}
