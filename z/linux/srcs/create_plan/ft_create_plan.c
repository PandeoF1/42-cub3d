/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:05:41 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/08 14:50:54 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_create_plan_n_s(t_game *game, int x)
{
	while (x < game->max_y - 1)
	{
		if ((!ft_is_double_y(game->map, x)))
		{
			dprintf(1, "x : \033[0;32m%s - %d\e[0m\n", game->map[x], x);
			game->plan[0][x].a = 0;
			game->plan[0][x].b = 1;
			game->plan[0][x].c = 0;
			game->plan[0][x].d = -x;
		}
		else
		{
			dprintf(1, "x : \033[0;31m%s - %d\e[0m\n", game->map[x], x);
			game->plan[0][x].a = 0;
			game->plan[0][x].b = 0;
			game->plan[0][x].c = 0;
			game->plan[0][x].d = 0;
		}
		x++;
	}
}

void	ft_create_plan_e_w(t_game *game, int x)
{
	dprintf(1, "y :  ");
	while (x < game->max_x - 1)
	{
		if ((!ft_is_double_x(game->map, x)))
		{
			dprintf(1, "+");
			game->plan[1][x].a = 1;
			game->plan[1][x].b = 0;
			game->plan[1][x].c = 0;
			game->plan[1][x].d = -x;
		}
		else
		{
			dprintf(1, "-");
			game->plan[1][x].a = 0;
			game->plan[1][x].b = 0;
			game->plan[1][x].c = 0;
			game->plan[1][x].d = 0;
		}
		x++;
	}
	dprintf(1, "\n");
}

int	ft_create_plan_sprite_door(t_game *game)
{
	if (game->nb_sprites != 0)
	{
		game->plan[2] = malloc(sizeof(t_plan) * game->nb_sprites);
		if (!game->plan[2])
			return (0);
		game->sprites = malloc(sizeof(t_sprite) * game->nb_sprites);
		if (!game->sprites)
			return (0);
		ft_create_sprite(game, SPRITE_CHAR);
	}
	game->plan[3] = malloc(sizeof(t_plan) * game->nb_door);
	if (!game->plan[3])
		return (0);
	ft_create_door(game);
	return (1);
}

int	ft_create_plan(t_game *game)
{
	int	x;

	game->nb_door = ft_door_count(game);
	game->plan = malloc(sizeof(t_plan *) * 5);
	if (!game->plan)
		return (0);
	game->plan[0] = malloc(sizeof(t_plan) * (game->max_y + 1));
	if (!game->plan[0])
		return (0);
	game->plan[1] = malloc(sizeof(t_plan) * (game->max_x + 1));
	if (!game->plan[1])
		return (0);
	x = 0;
	game->nb_sprites = 0;
	while (x < SPRITE_LEN)
		game->nb_sprites += ft_nb_of(game, SPRITE_CHAR[x++]);
	if (ft_create_plan_sprite_door(game) != 1)
		return (0);
	ft_create_plan_n_s(game, 1);
	ft_create_plan_e_w(game, 1);
	return (1);
}
