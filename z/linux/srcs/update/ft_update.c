/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:14:17 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/13 21:13:18 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_case_one(t_update *u, t_game *g)
{
	if ((u->best_t == 0 || u->t < u->best_t) && ((u->v == 0 && \
		u->py_py < g->player_y \
		&& (int)(-g->plan[u->v][u->u].d - 1) < g->max_y && (int)(-g->plan \
		[u->v][u->u].d - 1) >= 0 && g->map[(int)(-g->plan[u->v][u->u].d - 1)] \
		[(int)u->px_px] == '1') || (u->v == 1 && u->px_px < g->player_x \
		&& (int)(-g->plan[u->v][u->u].d - 1) < g->max_x && (int)(-g->plan \
		[u->v][u->u].d - 1) >= 0 && g->map[(int)u->py_py][(int)(-g->plan[u->v] \
		[u->u].d - 1)] == '1') || (u->v == 0 && u->py_py > g->player_y && (int) \
		(-g->plan[u->v][u->u].d) < g->max_y && (int)(-g->plan[u->v][u->u].d) \
		>= 0 && g->map[(int)(-g->plan[u->v][u->u].d)][(int)u->px_px] == '1') \
		|| (u->v == 1 && u->px_px > g->player_x && (int)(-g->plan \
		[u->v][u->u].d) < g->max_x && (int)(-g->plan[u->v][u->u].d) >= 0 \
		&& g->map[(int)u->py_py][(int)(-g->plan[u->v][u->u].d)] == '1') \
		|| (u->v == 3 && u->py_py > g->player_y \
		&& (int)(-g->plan[u->v][u->u].d) < g->max_y \
		&& (int)(-g->plan[u->v][u->u].d) >= 0 \
		&& ft_is_door(g->map[(int) \
		(-g->plan[u->v][u->u].d)][(int)u->px_px]) != 0)
		|| (u->v == 3 && u->py_py < g->player_y \
		&& (int)(-g->plan[u->v][u->u].d) < g->max_y && (int) \
		(-g->plan[u->v][u->u].d - 0.5) >= 0 && ft_is_door(g->map[(int)(-g->plan \
		[u->v][u->u].d - 0.5)][(int)u->px_px]) != 0)))
		return (1);
	else
		return (0);
}

int	ft_case_two(t_update *update, t_game *game)
{
	if (game->plan[update->v][update->u].a == 1 || game->plan \
	[update->v][update->u].b == 1 || update->v == 2)
	{
		update->t = (game->plan[update->v][update->u].a * \
		update->rayon_tempp.x + game->plan[update->v][update->u].b * \
		update->rayon_tempp.y + game->plan[update->v][update->u].c * \
		update->rayon_tempp.z);
		return (1);
	}
	return (0);
}

void	ft_case_two_util(t_update *update, t_game *game)
{
	if (update->t != 0)
	{
		update->t = -(game->plan[update->v][update->u].a * \
		game->player_x + game->plan[update->v][update->u].b * \
		game->player_y + game->plan[update->v][update->u].c * 0.5 + \
		game->plan[update->v][update->u].d) / update->t;
		if (update->t > 0)
		{
			ft_set_points(update, game, update->t);
			ft_updater_2(update, game);
		}
	}
}

void	ft_updater_2(t_update *update, t_game *game)
{
	if (update->v != 2 && update->point_z < 1 && update->point_z > 0 \
	&& (int)update->px_px >= 0 && (int)update->py_py >= 0 && \
	(int)update->px_px < game->max_x && (int)update->py_py < game->max_y)
	{
		if (ft_case_one(update, game))
		{
			if (update->v == 3)
				ft_updater_3(update, game);
			else
				ft_best_var(update);
		}
	}
	else if (update->v == 2)
		ft_updater_4(update, game);
	else if (update->point_z > 1.0 || update->point_z < 0.0)
	{
		if (update->point_z > 1.0)
			update->img->data[update->i * game->twidth + update->j] \
			= game->ceiling_color;
		else
			update->img->data[update->i * game->twidth + update->j] \
			= game->floor_color;
		update->u = -8;
	}
}

float	ft_best_var(t_update *update)
{
	update->best_t = update->t;
	update->v_plan = update->v;
	update->u_plan = update->u;
	update->u = -8;
	return (update->best_t);
}
