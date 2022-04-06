/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:36:58 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/04 10:37:08 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_mouse(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->graphic->mlx, game->graphic->win, &x, &y);
	mlx_mouse_hide(game->graphic->mlx, game->graphic->win);
	game->angle_z += (x - game->twidth / 2) * 0.005;
	game->angle_x += (y - game->theight / 2) * 0.0025;
	mlx_mouse_move(game->graphic->mlx, game->graphic->win,
		game->twidth / 2, game->theight / 2);
}
