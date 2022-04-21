/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:22:18 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/12 09:37:08 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_map_util_3(t_game *game)
{
	ft_draw_square(game->m_u->x + (game->twidth - (25 * 9)), \
		game->m_u->y + 25, 4, game);
}

void	ft_map_util_4(t_game *game)
{
	if (game->map[(int) \
	(game->m_u->j * 0.25)][(int)(game->m_u->i * 0.25)] == 'Z' \
	|| game->map[(int) \
	(game->m_u->j * 0.25)][(int)(game->m_u->i * 0.25)] == 'B' \
	|| game->map[(int) \
	(game->m_u->j * 0.25)][(int)(game->m_u->i * 0.25)] == 'V' \
	|| game->map[(int) \
	(game->m_u->j * 0.25)][(int)(game->m_u->i * 0.25)] == 'C')
	{
		game->map_color = 0xFF0000;
		ft_map_util_3(game);
	}
}

void	ft_map_util_2(t_game *game)
{
	if (game->map \
	[(int)(game->m_u->j * 0.25)][(int)(game->m_u->i * 0.25)] == '1')
	{
		game->map_color = 0x9000ff;
		ft_map_util_3(game);
	}
	else if (game->map[(int) \
	(game->m_u->j * 0.25)][(int)(game->m_u->i * 0.25)] == '0' \
	|| game->map[(int) \
	(game->m_u->j * 0.25)][(int)(game->m_u->i * 0.25)] == 'X')
	{
		game->map_color = 0x2205ff;
		ft_map_util_3(game);
	}
	else if (game->map[(int) \
	(game->m_u->j * 0.25)][(int)(game->m_u->i * 0.25)] == 'T')
	{
		game->map_color = 0x00FF00;
		ft_map_util_3(game);
	}
	else
		ft_map_util_4(game);
}

void	ft_map_util(t_game *game)
{
	if ((int)(game->m_u->i * 0.25) == (int)game->player_x \
	&& game->m_u->j * 0.25 == (int)game->player_y)
	{
		game->map_color = 0xffffff;
		ft_draw_square(game->m_u->x + (game->twidth - (25 * 9)), \
		game->m_u->y + 25, 4, game);
		game->m_u->j += 3;
		game->m_u->y += 3;
	}
	else
		ft_map_util_2(game);
	game->m_u->j++;
	game->m_u->y++;
}

void	ft_map(t_game *game, t_img img)
{
	t_map_util		map_util;

	game->m_u = &map_util;
	game->img_map = img;
	game->map_color = 0x5e5e5e;
	game->m_u->x = 0;
	game->m_u->y = 0;
	game->m_u->i = (game->player_x * 4) - 25 * 4;
	if (game->m_u->i < 0)
		game->m_u->i = 0;
	while (game->m_u->i < game->max_x * 4 \
	&& game->m_u->i < (game->player_x * 4) + 25 * 4)
	{
		game->m_u->j = (game->player_y * 4) - 25 * 4;
		if (game->m_u->j < 0)
			game->m_u->j = 0;
		game->m_u->y = 0;
		while (game->m_u->j < game->max_y * 4 \
		&& game->m_u->j < (game->player_y * 4) + 25 * 4)
			ft_map_util(game);
		game->m_u->x++;
		game->m_u->i++;
	}
}
