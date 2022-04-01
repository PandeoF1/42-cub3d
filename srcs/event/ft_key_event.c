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
	if (keycode == EVENT_ESC)
		mlx_loop_end(game->graphic->mlx);
	if (keycode == EVENT_SPACE)
		game->keyboard.space = 1;
	if (keycode == EVENT_W)
		game->keyboard.w = 1;
	if (keycode == EVENT_S)
		game->keyboard.s = 1;
	if (keycode == EVENT_A)
		game->keyboard.a = 1;
	if (keycode == EVENT_D)
		game->keyboard.d = 1;
	if (keycode == 65362)
		game->keyboard.up = 1;
	if (keycode == 65364)
		game->keyboard.down = 1;
	if (keycode == 65363)
		game->keyboard.left = 1;
	if (keycode == 65361)
		game->keyboard.right = 1;
	if (keycode == 65505)
		game->size_p = SIZE_P_CROUCHING;
	if (keycode == 109)
		game->minimap *= -1;
	return (0);
}

int	ft_unpress(int keycode, t_game *game)
{
	if (keycode == EVENT_SPACE)
		game->keyboard.space = 0;
	if (keycode == EVENT_W)
		game->keyboard.w = 0;
	if (keycode == EVENT_S)
		game->keyboard.s = 0;
	if (keycode == EVENT_A)
		game->keyboard.a = 0;
	if (keycode == EVENT_D)
		game->keyboard.d = 0;
	if (keycode == 65362)
		game->keyboard.up = 0;
	if (keycode == 65364)
		game->keyboard.down = 0;
	if (keycode == 65363)
		game->keyboard.left = 0;
	if (keycode == 65361)
		game->keyboard.right = 0;
	if (keycode == 65505)
		game->size_p = SIZE_P_STANDING;
	return (0);
}

int	ft_exit_hook(t_game *game)
{
	mlx_loop_end(game->graphic->mlx);
	return (0);
}
