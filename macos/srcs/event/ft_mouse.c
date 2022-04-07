/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:36:58 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/07 10:54:36 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_mouse(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->graphic->win, &x, &y);
	mlx_mouse_hide(game->graphic->mlx, game->graphic->win);
	if (x > game->twidth / 2 || x < game->twidth / 2)
		game->angle_z += (x - game->twidth / 2) * 0.005;
	if ((y > game->theight / 2 && game->angle_x <= 0.75)
		|| (y < game->theight / 2 && game->angle_x >= -0.5))
		game->angle_x += (y - game->theight / 2) * 0.002;
	mlx_mouse_move(game->graphic->win,
		game->twidth / 2, game->theight / 2);
}
