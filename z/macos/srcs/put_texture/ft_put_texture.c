/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:46:06 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/01 13:01:07 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_put_door_2(t_update *update, t_game *game)
{
	update->door = ft_is_door(game->map[(int)(-game->plan \
	[update->v_plan][update->u_plan].d)][(int)update->px_px]) - 1;
	if (update->door != 4)
	{
		update->x = (int)((update->px_px - (int)update->px_px) * \
		game->door_color[update->door].size_l * 0.25);
		update->y = (int)((update->point_z - (int)(update->point_z)) * \
		game->door_color[update->door].size_l * 0.25);
		update->img->data[update->i * game->twidth + update->j] = \
		game->door_color[update->door].data[(int)(update->y * \
		(game->door_color[update->door].size_l * 0.25) + update->x)];
		return (1);
	}
	return (0);
}

int	ft_put_door(t_update *u, t_game *g)
{
	if (u->v_plan == 3 && u->py_py > g->player_y && (int) \
	(-g->plan[u->v_plan][u->u_plan].d) < g->max_y && (int) \
	(-g->plan[u->v_plan][u->u_plan].d) >= 0 && ft_is_door(g->map[(int)(-g->plan \
	[u->v_plan][u->u_plan].d)][(int)u->px_px]) != 0)
	{
		u->door = ft_is_door(g->map[(int)(-g->plan \
		[u->v_plan][u->u_plan].d)][(int)u->px_px]) - 1;
		if (u->door != 4)
		{
			u->x = (int)((u->px_px - (int)u->px_px) * \
			g->door_color[u->door].size_l * 0.25);
			u->y = (int)((u->point_z - (int)(u->point_z)) * \
			g->door_color[u->door].size_l * 0.25);
			u->img->data[u->i * g->twidth + u->j] = \
			g->door_color[u->door].data[(int)(u->y * \
			(g->door_color[u->door].size_l * 0.25) + u->x)];
			return (1);
		}
	}
	else if (u->v_plan == 3 && u->py_py < g->player_y && (int)(-g->plan \
	[u->v_plan][u->u_plan].d - 0.5) < g->max_y && (int)(-g->plan \
	[u->v_plan][u->u_plan].d - 0.5) >= 0 && ft_is_door(g->map[(int)(-g->plan \
	[u->v_plan][u->u_plan].d - 0.5)][(int)u->px_px]) != 0)
		return (ft_put_door_2(u, g));
	return (0);
}

int	ft_put_sprite(t_update *update, t_game *game)
{
	if (update->v_plan == 2 && update->best_x != -7 && update->best_x != -7)
	{
		update->x = update->best_x;
		update->y = update->best_y;
		update->img->data[update->i * game->twidth + update->j] = \
		game->img_t.data[(int)(update->y * \
		(game->img_t.size_l * 0.25) + update->x)];
		return (1);
	}
	return (0);
}

int	ft_put_n_w_wall(t_update *u, t_game *g)
{
	if (u->v_plan == 0 && u->py_py < g->player_y && (int)(-g->plan \
	[u->v_plan][u->u_plan].d - 1) < g->max_y && (int)(-g->plan \
	[u->v_plan][u->u_plan].d - 1) >= 0 && g->map[(int)(-g->plan \
	[u->v_plan][u->u_plan].d - 1)][(int)u->px_px] == '1')
	{
		u->x = (int)((u->px_px - (int)u->px_px) * g->img_n.size_l * 0.25);
		u->y = (int)((u->point_z - (int)(u->point_z)) * \
		g->img_n.size_l * 0.25);
		u->img->data[u->i * g->twidth + u->j] = g->img_n.data \
		[(int)(u->y * (g->img_n.size_l * 0.25) + u->x)];
		return (1);
	}
	else if (u->v_plan == 1 && u->px_px < g->player_x && (int)(-g->plan \
	[u->v_plan][u->u_plan].d - 1) < g->max_x && (int)(-g->plan \
	[u->v_plan][u->u_plan].d - 1) >= 0 && g->map[(int)u->py_py] \
	[(int)(-g->plan[u->v_plan][u->u_plan].d - 1)] == '1')
	{
		u->x = (int)((u->py_py - (int)u->py_py) * g->img_w.size_l * 0.25);
		u->y = (int)((u->point_z - (int)(u->point_z)) * g->img_w.size_l * 0.25);
		u->img->data[u->i * g->twidth + u->j] = \
		g->img_w.data[(int)(u->y * (g->img_w.size_l * 0.25) + u->x)];
		return (1);
	}
	return (0);
}

int	ft_put_s_e_wall(t_update *u, t_game *g)
{
	if (u->v_plan == 0 && u->py_py > g->player_y && (int)(-g->plan[u->v_plan] \
	[u->u_plan].d) < g->max_y && (int)(-g->plan[u->v_plan][u->u_plan].d) >= 0 \
	&& g->map[(int)(-g->plan[u->v_plan][u->u_plan].d)][(int)u->px_px] == '1')
	{
		u->x = (int)((u->px_px - (int)u->px_px) * g->img_s.size_l * 0.25);
		u->y = (int)((u->point_z - (int)(u->point_z)) * g->img_s.size_l * 0.25);
		u->img->data[u->i * g->twidth + u->j] = g->img_s.data[(int)(u->y * \
		(g->img_s.size_l * 0.25) + u->x)];
		return (1);
	}
	else if (u->v_plan == 1 && u->px_px > g->player_x && \
	(int)(-g->plan[u->v_plan][u->u_plan].d) < g->max_x && \
	(int)(-g->plan[u->v_plan][u->u_plan].d) >= 0 && \
	g->map[(int)u->py_py][(int) \
	(-g->plan[u->v_plan][u->u_plan].d)] == '1')
	{
		u->x = (int)((u->py_py - (int)u->py_py) * g->img_e.size_l * 0.25);
		u->y = (int)((u->point_z - (int)(u->point_z)) * g->img_e.size_l * 0.25);
		u->img->data[u->i * g->twidth + u->j] = \
		g->img_e.data[(int)(u->y * (g->img_e.size_l * 0.25) + u->x)];
		return (1);
	}
	return (0);
}
