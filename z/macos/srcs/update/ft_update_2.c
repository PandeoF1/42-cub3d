/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:19:15 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/07 10:29:04 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_updater_3(t_update *u, t_game *g)
{
	u->door = 0;
	if (u->py_py > g->player_y && (int)(-g->plan[u->v][u->u].d) \
	< g->max_y && (int)(-g->plan[u->v][u->u].d) >= 0 && ft_is_door(g->map \
	[(int)(-g->plan[u->v][u->u].d)][(int)u->px_px]) != 0)
		u->door = ft_is_door(g->map[(int)(-g->plan \
		[u->v][u->u].d)][(int)u->px_px]) - 1;
	else if (u->py_py < g->player_y && (int)(-g->plan[u->v][u->u].d) < g->max_y \
	&& (int)(-g->plan[u->v][u->u].d - 0.5) >= 0 && ft_is_door(g->map[(int) \
	(-g->plan[u->v][u->u].d - 0.5)][(int)u->px_px]) != 0)
		u->door = ft_is_door(g->map[(int)(-g->plan \
		[u->v][u->u].d - 0.5)][(int)u->px_px]) - 1;
	if (u->door != 4)
	{
		u->x = (int)((u->px_px - (int)u->px_px) * \
		g->door_color[u->door].size_l * 0.25);
		u->y = (int)((u->point_z - (int)(u->point_z)) * \
		g->door_color[u->door].size_l * 0.25);
		if (g->door_color[u->door].data[(int)(u->y * \
		(g->door_color[u->door].size_l * 0.25) + u->x)] != -16777216)
			ft_best_var(u);
	}
}

void	ft_updater_4_util(t_update *update)
{
	update->best_t = update->t;
	update->best_x = update->x;
	update->best_y = update->y;
	update->v_plan = update->v;
	update->u_plan = update->u;
}

void	ft_updater_4(t_update *u, t_game *g)
{
	float	ux;
	float	uy;
	float	sqrt1;

	if ((u->best_t == 0 || u->t < u->best_t) && u->point_z < 1 && u->point_z > \
	0 && (int)u->px_px >= 0 && (int)u->py_py >= 0 && (int)u->px_px < g->max_x \
	&& (int)u->py_py < g->max_y && g->map[(int)u->py_py][(int)u->px_px] == 'T')
	{
		ux = (u->px_px - g->sprites[u->u].sx);
		uy = (u->py_py - g->sprites[u->u].sy);
		sqrt1 = sqrt(pow(g->plan[u->v][u->u].b, 2) \
		+ pow(-g->plan[u->v][u->u].a, 2));
		u->r = ((ux * (g->plan[u->v][u->u].b / sqrt1)) \
		+ (uy * (-g->plan[u->v][u->u].a / sqrt1)) + 0.5);
		if (u->r >= 0 && u->r < 1)
		{
			u->x = u->r * g->img_t.size_l * 0.25;
			u->y = (int)((u->point_z - (int)(u->point_z)) \
			* g->img_t.size_l * 0.25);
			if (g->img_t.data[(int)(u->y * (g->img_t.size_l * 0.25) \
			+ u->x)] != -16777216)
				ft_updater_4_util(u);
		}
	}
}

void	ft_updater_5(t_update *update, t_game *game)
{
	ft_set_rayons(update, game);
	ft_set_var(update);
	while (update->v < 4)
	{
		update->u = 0;
		ft_set_switch(update, game);
		while (update->u <= update->switch_plan && update->u >= 0)
		{
			if (ft_case_two(update, game))
				ft_case_two_util(update, game);
			update->u += update->add;
		}
		update->v++;
	}
	if (update->best_t != 0 && update->v_plan != 4 \
	&& update->u_plan != -7)
	{
		ft_set_points(update, game, update->best_t);
		if (ft_put_n_w_wall(update, game) == 0)
			if (ft_put_s_e_wall(update, game) == 0)
				if (ft_put_sprite(update, game) == 0)
					ft_put_door(update, game);
	}
}
