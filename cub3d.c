/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/04/04 10:15:03 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

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

float	ft_best_var(t_update *update, t_game *game)
{
	update->best_t = update->t;
	update->v_plan = update->v;
	update->u_plan = update->u;
	update->u = -8;
	return (update->best_t);
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
			ft_best_var(u, g);
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
				ft_best_var(update, game);
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

void	ft_set_points(t_update *update, t_game *game, float t)
{
	update->point_x = update->rayon_tempp.x * t;
	update->point_y = update->rayon_tempp.y * t;
	update->point_z = game->size_p + update->rayon_tempp.z * t;
	update->px_px = (game->player_x + update->point_x);
	update->py_py = (game->player_y + update->point_y);
}

void	*ft_updater(void	*data)
{
	t_update	*update;
	t_game		*game;

	update = (t_update *)data;
	game = update->game;
	update->i = update->start_y;
	while (update->i < update->end_y)
	{
		update->j = 0;
		while (update->j < game->twidth)
		{
			ft_updater_5(update, game);
			update->t = 0;
			update->j++;
		}
		update->i++;
	}
	return (0);
}

void	ft_threads(t_game *game, t_update *updt, pthread_t *thread, t_img *img)
{
	int	x;

	x = 0;
	while (x < NB_THREAD)
	{
		updt[x].img = img;
		if (x == 0)
			updt[x].start_y = 0;
		else
			updt[x].start_y = (x * game->theight) / NB_THREAD;
		updt[x].end_y = ((x + 1) * game->theight) / NB_THREAD;
		updt[x].game = game;
		pthread_create(&thread[x], NULL, &ft_updater, &updt[x]);
		x++;
	}
	x = 0;
	while (x < NB_THREAD)
		pthread_join(thread[x++], NULL);
}

int	ft_update(t_game *game)
{
	t_update	update[NB_THREAD];
	pthread_t	thread[NB_THREAD];
	t_img		img;

	ft_door(game);
	ft_move(game);
	ft_mouse(game);
	ft_set_sprites(game);
	img.img_ptr = mlx_new_image(game->graphic->mlx,
			game->twidth, game->theight);
	img.data = (int *)mlx_get_data_addr(img.img_ptr,
			&img.bpp, &img.size_l, &img.endian);
	ft_threads(game, update, thread, &img);
	if (game->minimap > 0)
		ft_map(game, img);
	ft_put_image(game, img);
	mlx_string_put(game->graphic->mlx, game->graphic->win \
		, (WIDTH * 0.5) - 2, (HEIGHT * 0.5) + 4, 0xFF0000, "+");
	ft_fps(game);
	mlx_destroy_image(game->graphic->mlx, img.img_ptr);
	return (0);
}

void	*ft_open_xpm(t_game *game, char *str, int size_x)
{
	return (mlx_xpm_file_to_image(
			game->graphic->mlx, str, &size_x,
			&size_x));
}

int	ft_split_number(char **split)
{
	int	x;
	int	y;

	x = 0;
	while (split[x])
	{
		y = 0;
		while (split[x][y])
		{
			if (split[x][y] < '0' || split[x][y] > '9')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	ft_color_format(char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (ft_splitlen(split) != 3 || !ft_split_number(split))
	{
		ft_free_split(split);
		return (-1);
	}
	return ((ft_atoi(split[0]) << 16)
		+ (ft_atoi(split[1]) << 8) + ft_atoi(split[2]));
}

void ft_mouse(t_game *game)
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

int main(int argc, char *argv[])
{
	t_game		game;
	t_graphic	graphic;
	pthread_t	music;

	ft_init_struct(&game, &graphic);
	mlx_mouse_move(game.graphic->mlx, game.graphic->win,
		game.twidth / 2, game.theight / 2);
	if (ft_check_arg(argc, argv, &game)
		&& ft_create_image_n_s(&game) && ft_get_pos(&game))
	{
		ft_start_music(&game, music);
		ft_create_vector(&game);
		ft_create_plan(&game);
		mlx_loop_hook(graphic.mlx, ft_update, &game);
		mlx_mouse_hide(graphic.mlx, graphic.win);
		mlx_hook(graphic.win, 17, 1L << 17, ft_exit_hook, &game);
		mlx_hook(graphic.win, 02, 1L << 0, ft_win_event, &game);
		mlx_hook(graphic.win, 03, 1L << 1, ft_unpress, &game);
		mlx_mouse_hide(graphic.mlx, graphic.win);
		mlx_loop(graphic.mlx);
	}
	else
		ft_printf("Error\n");
	ft_stop_music(&game, music);
	ft_close(&game);
	return (0);
}
