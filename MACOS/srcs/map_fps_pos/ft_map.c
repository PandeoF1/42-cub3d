/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:22:18 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/06 11:41:19 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_draw_square(int y, int x, int max_y, t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < max_y)
	{
		j = 0;
		while (j < max_y)
		{
			game->img_map.data[(i + x) * (game->twidth) + \
			(j + y)] = game->map_color;
			j++;
		}
		i++;
	}
}

void	ft_map_util_2(t_game *game)
{
	if (game->map[(int) \
	(game->map_util.j * 0.25)][(int)(game->map_util.i * 0.25)] == '1')
	{
		game->map_color = 0x9000ff;
		ft_draw_square(game->map_util.x + (game->twidth - (25 * 9)), \
		game->map_util.y + 25, 4, game);
	}
	else if (game->map[(int) \
	(game->map_util.j * 0.25)][(int)(game->map_util.i * 0.25)] == '0' \
	|| ft_is_door(game->map \
	[(int)(game->map_util.j * 0.25)][(int)(game->map_util.i * 0.25)]) \
	|| game->map[(int) \
	(game->map_util.j * 0.25)][(int)(game->map_util.i * 0.25)] == 'X')
	{
		game->map_color = 0x2205ff;
		ft_draw_square(game->map_util.x + (game->twidth - (25 * 9)), \
		game->map_util.y + 25, \
		4, game);
	}
}

void	ft_map_util(t_game *game)
{
	if ((int)(game->map_util.i * 0.25) == (int)game->player_x \
	&& game->map_util.j * 0.25 == (int)game->player_y)
	{
		game->map_color = 0xffffff;
		ft_draw_square(game->map_util.x + (game->twidth - (25 * 9)), \
		game->map_util.y + 25, 4, game);
		game->map_util.j += 3;
		game->map_util.y += 3;
	}
	else
		ft_map_util_2(game);
	game->map_util.j++;
	game->map_util.y++;
}

void	ft_map(t_game *game, t_img img)
{
	t_map_util		map_util;

	game->map_util = map_util;
	game->img_map = img;
	game->map_color = 0x5e5e5e;
	game->map_util.x = 0;
	game->map_util.y = 0;
	// ft_draw_square(game->map_util.x + (game->twidth - (25 * 9)), \
	// game->map_util.y + 25, 25 * 10, game);
	game->map_util.i = (game->player_x * 4) - 25 * 4;
	if (game->map_util.i < 0)
		game->map_util.i = 0;
	while (game->map_util.i < game->max_x * 4 \
	&& game->map_util.i < (game->player_x * 4) + 25 * 4)
	{
		game->map_util.j = (game->player_y * 4) - 25 * 4;
		if (game->map_util.j < 0)
			game->map_util.j = 0;
		game->map_util.y = 0;
		while (game->map_util.j < game->max_y * 4 \
		&& game->map_util.j < (game->player_y * 4) + 25 * 4)
			ft_map_util(game);
		game->map_util.x++;
		game->map_util.i++;
	}
}
