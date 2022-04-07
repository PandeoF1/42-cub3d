/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_door.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:15:41 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/01 12:16:27 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_create_door(t_game *game)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_is_door(game->map[y][x]) != 0)
			{
				game->plan[3][i].a = 0;
				game->plan[3][i].b = 1;
				game->plan[3][i].c = 0;
				game->plan[3][i].d = -y - 0.5;
				i++;
				break ;
			}
			x++;
		}
		y++;
	}
}

int	ft_door_count(t_game *game)
{
	int		x;
	int		y;
	int		total;

	x = 0;
	total = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (ft_is_door(game->map[x][y]) != 0)
			{
				total++;
				break ;
			}
			y++;
		}
		x++;
	}
	return (total);
}

void	ft_door_close(t_game *game, int x, int y)
{
	if (game->map[y][x] == DOOR_CHAR[1])
		game->map[y][x] = DOOR_CHAR[0];
	else if (game->map[y][x] == DOOR_CHAR[2])
		game->map[y][x] = DOOR_CHAR[1];
	else if (game->map[y][x] == DOOR_CHAR[3])
		game->map[y][x] = DOOR_CHAR[2];
	else if (game->map[y][x] == 'X')
		game->map[y][x] = DOOR_CHAR[3];
}

void	ft_door_open(t_game *game, int x, int y)
{
	if (game->dist_x < 2.5 && game->dist_y < 2.5 && game->keyboard.space)
	{
		if (game->map[y][x] == DOOR_CHAR[0])
			game->map[y][x] = DOOR_CHAR[1];
		else if (game->map[y][x] == DOOR_CHAR[1])
			game->map[y][x] = DOOR_CHAR[2];
		else if (game->map[y][x] == DOOR_CHAR[2])
			game->map[y][x] = DOOR_CHAR[3];
		else if (game->map[y][x] == DOOR_CHAR[3])
			game->map[y][x] = 'X';
	}
	else
		ft_door_close(game, x, y);
}

void	ft_door(t_game *game)
{
	static int64_t	timer = 0;
	int				x;
	int				y;

	if ((timer == 0 || get_time() - timer > 150))
		timer = get_time();
	else
		return ;
	y = -1;
	while (++y < game->max_y)
	{
		x = -1;
		while (++x < game->max_x)
		{
			game->dist_x = x - game->player_x;
			game->dist_y = y - game->player_y;
			if (game->dist_x < 0)
				game->dist_x = -game->dist_x;
			if (game->dist_y < 0)
				game->dist_y = -game->dist_y;
			ft_door_open(game, x, y);
		}
	}
}
