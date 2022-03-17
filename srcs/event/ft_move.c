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

void	ft_move_camera(t_game *game)
{
	if (game->keyboard.up)
		if (game->angle_x >= -0.5)
			game->angle_x -= 0.015;
	if (game->keyboard.down)
		if (game->angle_x <= 0.75)
			game->angle_x += 0.015;
	if (game->keyboard.left)
		game->angle_z += 0.04;
	if (game->keyboard.right)
		game->angle_z -= 0.04;
	if (game->angle_z >= PI * 2)
		game->angle_z -= PI * 2;
	if (game->angle_z <= 0)
		game->angle_z += PI * 2;
	game->cos_z = cos(game->angle_z);
	game->cos_x = cos(game->angle_x);
	game->sin_z = sin(game->angle_z);
	game->sin_x = sin(game->angle_x);
}

void	ft_move_next(t_game *game)
{	
	if (game->keyboard.a)
	{
		if (game->map[(int)(game->player_y - sin(game->angle_z) * 0.30)]
			[(int)(game->player_x - cos(game->angle_z) * 0.30)] == '0'
			|| game->map[(int)(game->player_y - sin(game->angle_z) * 0.30)]
			[(int)(game->player_x - cos(game->angle_z) * 0.30)] == 'X')
		{
			game->player_x -= cos(game->angle_z) * 0.05;
			game->player_y -= sin(game->angle_z) * 0.05;
		}
	}
	if (game->keyboard.d)
	{
		if (game->map[(int)(game->player_y + sin(game->angle_z) * 0.30)]
			[(int)(game->player_x + cos(game->angle_z) * 0.30)] == '0'
			|| game->map[(int)(game->player_y + sin(game->angle_z) * 0.30)]
			[(int)(game->player_x + cos(game->angle_z) * 0.30)] == 'X')
		{
			game->player_x += cos(game->angle_z) * 0.05;
			game->player_y += sin(game->angle_z) * 0.05;
		}
	}
	ft_move_camera(game);
}

void	ft_move(t_game *game)
{
	if (game->keyboard.w)
	{
		if (game->map[(int)(game->player_y - cos(game->angle_z) * 0.30)]
			[(int)(game->player_x + sin(game->angle_z) * 0.30)] == '0'
			|| game->map[(int)(game->player_y - cos(game->angle_z) * 0.30)]
			[(int)(game->player_x + sin(game->angle_z) * 0.30)] == 'X')
		{
			game->player_x += sin(game->angle_z) * 0.075;
			game->player_y -= cos(game->angle_z) * 0.075;
		}
	}
	if (game->keyboard.s)
	{
		if (game->map[(int)(game->player_y + cos(game->angle_z) * 0.30)]
			[(int)(game->player_x - sin(game->angle_z) * 0.30)] == '0'
			|| game->map[(int)(game->player_y + cos(game->angle_z) * 0.30)]
			[(int)(game->player_x - sin(game->angle_z) * 0.30)] == 'X')
		{
			game->player_x -= sin(game->angle_z) * 0.075;
			game->player_y += cos(game->angle_z) * 0.075;
		}
	}
	ft_move_next(game);
}
