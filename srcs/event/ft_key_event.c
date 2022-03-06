/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:52:50 by tnard             #+#    #+#             */
/*   Updated: 2022/03/05 22:52:50 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_win_event(int keycode, t_game *game)
{
	return (0);
}

int	ft_unpress(int keycode, t_game *game)
{
	return (0);
}

int	ft_exit_hook(t_game *game)
{
	mlx_loop_end(game->graphic->mlx);
	return (0);
}

int	ft_press(int keycode, t_game *game)
{
	ft_move(keycode, game);
	if (keycode == 65363)
		game->angle_z += 0.07;
	if (keycode == 65361)
		game->angle_z -= 0.07;
	if (keycode == 65362) // bonus
		if (game->angle_x > -0.2)
			game->angle_x -= 0.01;
	if (keycode == 65364)
		if (game->angle_x < 0.2)
			game->angle_x += 0.01;
	if (game->angle_z >= PI * 2)
		game->angle_z -= PI * 2;
	if (game->angle_z <= 0)
		game->angle_z += PI * 2;
	if (keycode == EVENT_ESC)
	{
		mlx_loop_end(game->graphic->mlx);
		return (0);
	}
	return (0);
}
