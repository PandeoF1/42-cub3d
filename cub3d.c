/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/03/31 09:44:01 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	ft_is_door(char c)
{
	int	x;

	x = 0;
	while (x < DOOR_LEN)
	{
		if (c == DOOR_CHAR[x])
			return (x + 1);
		x++;
	}
	return (0);
}

int	ft_is_sprite(char c)
{
	int	x;

	x = 0;
	while (x < SPRITE_LEN)
	{
		if (c == SPRITE_CHAR[x])
			return (1);
		x++;
	}
	return (0);
}

void	ft_free_rayon(t_rayon **rayon, t_game *game)
{
	int			x;

	x = 0;
	while (x < game->theight)
	{
		free(rayon[x]);
		x++;
	}
	free(rayon);
}

void	ft_close(t_game *game)
{
	if (game->map)
		ft_free_split(game->map);
	if (game->n)
		free(game->n);
	if (game->s)
		free(game->s);
	if (game->e)
		free(game->e);
	if (game->w)
		free(game->w);
	if (game->f)
		free(game->f);
	if (game->c)
		free(game->c);
	ft_free_rayon(game->rayon, game);
	mlx_destroy_image(game->graphic->mlx, game->img_n.img_ptr);
	mlx_destroy_image(game->graphic->mlx, game->img_s.img_ptr);
	mlx_destroy_image(game->graphic->mlx, game->img_e.img_ptr);
	mlx_destroy_image(game->graphic->mlx, game->img_w.img_ptr);
	mlx_destroy_window(game->graphic->mlx, game->graphic->win);
	mlx_destroy_display(game->graphic->mlx);
	printf("Cub3d: exit\n");
}

int	ft_select_pos(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'N')
		game->angle_z = 0;
	else if (game->map[y][x] == 'S')
		game->angle_z = 3.14;
	else if (game->map[y][x] == 'W')
		game->angle_z = 3.14 * 0.5;
	else if (game->map[y][x] == 'E')
		game->angle_z = 3.14 * 0.5 + 3.14;
	else
		return (1);
	if (game->player_x != -1 || game->player_y != -1)
		return (0);
	game->player_x = x + 0.5;
	game->player_y = y + 0.5;
	game->map[y][x] = '0';
	return (1);
}

int	ft_get_pos(t_game *game)
{
	int			x;
	int			y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (!ft_select_pos(game, x, y))
				return (0);
			x++;
		}
		y++;
	}
	game->max_y = ft_splitlen(game->map);
	if (game->player_x == -1 || game->player_y == -1)
		return (0);
	return (1);
}

int	ft_is_double_y(char	**str, int y)
{
	int	x;

	x = 0;
	if (ft_strlen(str[y]) != ft_strlen(str[y - 1]))
		return (0);
	while (str[y][x] && str[y - 1][x])
	{
		if (str[y][x] != str[y - 1][x])
			return (0);
		x++;
	}
	return (1);
}

int	ft_is_double_x(char	**str, int x)
{
	int	y;

	y = 0;
	while (str[y] && str[y][x] && str[y][x - 1])
	{
		//printf("y : %d %d - %c %c\n", y, x, str[y][x], str[y][x + 1]);
		//if (str[y][x] != ' ' && str[y][x + 1] != ' ')
		if (str[y][x] != str[y][x - 1])
			return (0);
		y++;
	}
	return (1);
}

int	ft_nb_of(t_game *game, char	charset)
{
	int	x;
	int	y;
	int	total;

	x = 0;
	total = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == charset)
				total++;
			y++;
		}
		x++;
	}
	return (total);
}

int		ft_init_sprite(t_game *game, int b, int x, int y)
{
	game->sprites[b].sx = x + 0.5;
	game->sprites[b].sy = y + 0.5;
	game->plan[2][b].a = 0;
	game->plan[2][b].b = 0;
	game->plan[2][b].c = 0;
	game->plan[2][b].d = 0;
	return (1);
}

void	ft_create_sprite(t_game *game, char *charset)
{
	int	a;
	int	b;
	int	x;
	int	y;

	a = 0;
	b = 0;
	while (a < ft_strlen(charset))
	{
		y = 0;
		while (game->map[y])
		{
			x = 0;
			while (game->map[y][x])
			{
				if (game->map[y][x] == charset[a])
				{
					b += ft_init_sprite(game, b, x, y);
				}
				x++;
			}
			y++;
		}
		a++;
	}
}

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

int	ft_create_plan(t_game *game)
{
	int	x;
	int	next;

	next = 0;
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

void	ft_create_vector(t_game *game)
{
	int		i;
	int		j;
	float	r_h;
	float	r_v;

	i = 0;
	while (i < game->theight)
	{
		j = 0;
		while (j < game->twidth)
		{
			r_h = 2 * tan((60 * PI / 180) * 0.5) / game->twidth;
			r_v= 2 * tan((60 * PI / 180)
					* game->theight / (game->twidth * 2)) / game->theight;
			game->rayon[i][j].x = ((j - game->twidth * 0.5) * r_h);
			game->rayon[i][j].y = -1.0;
			game->rayon[i][j].z = ((game->theight * 0.5 - i) * r_v);
			j++;
		}
		i++;
	}
}

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_put_fps(t_game *game, int lframe, int total_second, int total_frame)
{
	game->put_fps = ft_itoa(lframe);
	mlx_string_put(game->graphic->mlx, game->graphic->win,
		2, 10, 0xffffff, "FPS: ");
	mlx_string_put(game->graphic->mlx, game->graphic->win,
		30, 10, 0xffffff, game->put_fps);
	if (total_second > 1)
	{
		free(game->put_fps);
		game->put_fps = ft_itoa(total_frame / total_second);
		mlx_string_put(game->graphic->mlx, game->graphic->win,
			2, 30, 0xffffff, "Moy FPS : ");
		mlx_string_put(game->graphic->mlx, game->graphic->win,
			60, 30, 0xffffff, game->put_fps);
	}
	free(game->put_fps);
}
void	ft_fps(t_game *game)
{
	static int		lframe = 0;
	static int		frame = 0;
	static int		total_frame = 0;
	static int		total_second = -1;
	static int64_t	fps = 0;

	if (get_time() - fps < 1000)
	{
		frame++;
	}
	else
	{
		lframe = frame;
		fps = get_time();
		total_frame += frame;
		total_second += 1;
		frame = 1;
	}
	ft_put_fps(game, lframe, total_second, total_frame);
}

void ft_draw_square(t_img img, int y, int x, int max_y, int color, t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < max_y)
	{
		j = 0;
		while (j < max_y)
		{
			img.data[(i + x) * (game->twidth) + (j + y)] = color;
			j++;
		}
		i++;
	}
}

void ft_map(t_game *game, t_img img)
{
	int		i;
	int		j;
	int		x;
	int		y;

	ft_draw_square(img, x + (game->twidth - (25 * 9)), y + 25,
		25 * 10, 0x5e5e5e, game);
	i = (game->player_x * 4) - 25 * 4;
	if (i < 0)
		i = 0;
	x = 0;
	while (i < game->max_x * 4 && i < (game->player_x * 4) + 25 * 4)
	{
		j = (game->player_y * 4) - 25 * 4;
		if (j < 0)
			j = 0;
		y = 0;
		while (j < game->max_y * 4 && j < (game->player_y * 4) + 25 * 4)
		{
			if ((int)(i * 0.25) == (int)game->player_x && j * 0.25 == (int)game->player_y)
			{
				ft_draw_square(img, x + (game->twidth - (25 * 9)), y + 25, 4, 0xffffff, game);
				j += 3;
				y += 3;
			}
			else if (game->map[(int)(j * 0.25)][(int)(i * 0.25)] == '1')
				ft_draw_square(img, x + (game->twidth - (25 * 9)), y + 25, 4, 0x9000ff, game);
			else if (game->map[(int)(j * 0.25)][(int)(i * 0.25)] == '0' || ft_is_door(game->map[(int)(j * 0.25)][(int)(i * 0.25)]) || game->map[(int)(j * 0.25)][(int)(i * 0.25)] == 'X')
				ft_draw_square(img, x + (game->twidth - (25 * 9)), y + 25, 4, 0x2205ff, game);
			j++;
			y++;
		}
		x++;
		i++;
	}
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

void	ft_set_rayons(t_update *update, t_game *game)
{
	update->rayon_tempp.y = game->rayon[update->i][update->j].y
		* game->cos_x + game->rayon[update->i][update->j].z * -game->sin_x;
	update->rayon_tempp.z = game->rayon[update->i][update->j].y
		* game->sin_x + game->rayon[update->i][update->j].z * game->cos_x;
	update->rayon_tempp.x = game->rayon[update->i][update->j].x
		* game->cos_z + update->rayon_tempp.y * -game->sin_z;
	update->rayon_tempp.y = game->rayon[update->i][update->j].x
		* game->sin_z + update->rayon_tempp.y * game->cos_z;
	update->rayon_tempp.z = game->rayon[update->i][update->j].y
		* game->sin_x + game->rayon[update->i][update->j].z * game->cos_x;
}

void	ft_set_switch(t_update *update, t_game *game)
{
	if (update->v == 0)
	{
		update->switch_plan = game->max_y;
		update->u = game->player_y;
	}
	else if (update->v == 1)
	{
		update->switch_plan = game->max_x;
		update->u = game->player_x;
	}
	else if (update->v == 2)
		update->switch_plan = game->nb_sprites - 1;
	else if (update->v == 3)
		update->switch_plan = game->nb_door;
	update->add = 1;
	if ((update->v == 0 && update->rayon_tempp.y < 0)
		|| (update->v == 1 && update->rayon_tempp.x < 0))
		update->add = -1;
	else if (update->v == 3 && update->rayon_tempp.y < 0)
	{
		update->add = -1;
		update->u = game->nb_door;
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

void	ft_set_var(t_update *update)
{
	update->best_t = 0;
	update->v_plan = 4;
	update->u_plan = -7;
	update->v = 0;
	update->best_x = -7;
	update->best_y = -7;
}

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

void	ft_set_sprites(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->nb_sprites)
	{
		game->plan[2][x].a = game->sprites[x].sx - game->player_x;
		game->plan[2][x].b = game->sprites[x].sy - game->player_y;
		game->plan[2][x].c = 0;
		game->plan[2][x].d = -(game->plan[2][x].a * game->sprites[x].sx)
			- (game->plan[2][x].b * game->sprites[x].sy);
		x++;
	}
}

void ft_put_image(t_game *game, t_img img2)
{
	int		i;
	int		j;
	t_img	img;

	img.img_ptr = mlx_new_image(game->graphic->mlx, WIDTH, HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr,
			&img.bpp, &img.size_l, &img.endian);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			img.data[(i) * WIDTH + (j)]
				= img2.data[((i / PERF) * game->twidth + (j / PERF))];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->graphic->mlx, game->graphic->win,
		img.img_ptr, 0, 0);
	mlx_destroy_image(game->graphic->mlx, img.img_ptr);
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
	//ft_map(game, img);
	ft_put_image(game, img);
	mlx_string_put(game->graphic->mlx, game->graphic->win
		, (WIDTH * 0.5) - 2, (HEIGHT * 0.5) + 4, 0xFF0000, "+");
	ft_fps(game);
	mlx_destroy_image(game->graphic->mlx, img.img_ptr);
	return (0);
}

t_rayon **ft_malloc_rayon(t_game *game)
{
	t_rayon		**rayon;
	int			x;

	x = 0;
	rayon = malloc(sizeof(t_rayon *) * game->theight + 1);
	while (x < game->theight)
	{
		rayon[x] = malloc(sizeof(t_rayon) * game->twidth + 1);
		x++;
	}
	return (rayon);
}

int	ft_image_len(char *str, int y)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (x > y - 1)
			if (x == y && str[x] != ' ')
				return (0);
		x++;
	}
	if (str[x - 1] == ' ' || x < y + 2)
		return (0);
	return (x);
}

int	ft_check_image(char *path)
{
	char	*ext;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	ext = ft_strrchr(path, '.');
	if (ext == NULL || ft_strncmp(".xpm", ext, ft_strlen(".xpm")) != 0)
		return (0);
	return (1);
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

void	ft_reverse_img(t_img *img, int t, int x, int temp)
{
	int	value;

	x = 0;
	value = img->size_l * 0.25;
	while (x < (img->size_l * 0.25 * img->size_l
			* 0.25 - (img->size_l * 0.25 / 2)))
	{
		if (x >= value - img->size_l * 0.25 / 2)
		{
			x = value;
			t = 0;
			value += img->size_l * 0.25;
		}
		temp = img->data[x];
		img->data[x] = img->data[value - 1 - t];
		img->data[value - 1 - t] = temp;
		t++;
		x++;
	}
}

void	ft_flip_img(t_img *img, int x, int temp, int check)
{
	int	value;

	img->data = (int *)mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_l, &img->endian);
	if (x == 0)
	{
		value = img->size_l * 0.25 * img->size_l * 0.25;
		while (x < value / 2)
		{
			temp = img->data[x];
			img->data[x] = img->data[value - 1 - x];
			img->data[value - 1 - x] = temp;
			x++;
		}
	}
	if (check == 0)
		ft_reverse_img(img, 0, 0, 0);
}

int	ft_data_image(t_game *game)
{
	int	x;
	int	temp;
	int	t;
	int	value;

	if (ft_image_len(game->f, 1) == 0)
		return (0);
	game->floor_color = ft_color_format(game->f + 2);
	if (game->floor_color == -1)
		return (0);
	if (ft_image_len(game->c, 1) == 0)
		return (0);
	game->ceiling_color = ft_color_format(game->c + 2);
	if (game->ceiling_color == -1)
		return (0);
	ft_flip_img(&game->img_n, 0, 0, 0);
	ft_flip_img(&game->img_s, 0, 0, 1);
	ft_flip_img(&game->img_e, 0, 0, 0);
	ft_flip_img(&game->img_w, 0, 0, 1);
	ft_flip_img(&game->img_t, 0, 0, 1);
	ft_flip_img(&game->door_color[0], 0, 0, 0);
	ft_flip_img(&game->door_color[1], 0, 0, 0);
	ft_flip_img(&game->door_color[2], 0, 0, 0);
	ft_flip_img(&game->door_color[3], 0, 0, 0);
	return (1);
}

int	ft_create_image_e_w(t_game *game)
{
	int	i;

	i = 0;
	if (ft_image_len(game->w, 2) == 0)
		return (0);
	if (ft_check_image(game->w + 3))
		game->img_w.img_ptr = ft_open_xpm(game, game->w + 3,
				game->img_w.size_l);
	else
		return (0);
	if (ft_image_len(game->e, 2) == 0)
		return (0);
	if (ft_check_image(game->e + 3))
		game->img_e.img_ptr = ft_open_xpm(game, game->e + 3,
				game->img_e.size_l);
	else
		return (0);
	if (ft_image_len(game->t, 2) == 0)
		return (0);
	if (ft_check_image(game->t + 3))
		game->img_t.img_ptr = ft_open_xpm(game, game->t + 3,
				game->img_t.size_l);
	else
		return (0);
	while (i < 4)
	{
		if (ft_image_len(game->z[i], 2) == 0)
			return (0);
		if (ft_check_image(game->z[i] + 3))
			game->door_color[i].img_ptr = ft_open_xpm(game, game->z[i] + 3,
					game->door_color[i].size_l);
		else
			return (0);
		i++;
	}
	return (1);
}

int	ft_create_image_n_s(t_game *game)
{
	if (ft_image_len(game->n, 2) == 0)
		return (0);
	if (ft_check_image(game->n + 3))
		game->img_n.img_ptr = ft_open_xpm(game, game->n + 3,
				game->img_n.size_l);
	else
		return (0);
	if (ft_image_len(game->s, 2) == 0)
		return (0);
	if (ft_check_image(game->s + 3))
		game->img_s.img_ptr = ft_open_xpm(game, game->s + 3,
				game->img_s.size_l);
	else
		return (0);
	if (ft_create_image_e_w(game) != 1)
		return (0);
	return (ft_data_image(game));
}

void ft_mouse(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->graphic->mlx, game->graphic->win, &x, &y);
	mlx_mouse_hide(game->graphic->mlx, game->graphic->win);
	if (x > game->twidth / 2)
		game->angle_z += 0.05;
	else if (x < game->twidth / 2)
		game->angle_z -= 0.05;
	if (y > game->theight / 2 && game->angle_x <= 0.75)
		game->angle_x += 0.025;
	else if (y < game->theight / 2 && game->angle_x >= -0.5)
		game->angle_x -= 0.025;
	mlx_mouse_move(game->graphic->mlx, game->graphic->win,
		game->twidth / 2, game->theight / 2);
}

void	*ft_music(void *data)
{
	t_game *game;

	game = (t_game *)data;
	while (42)
		system("afplay music.mp3");
}

void	ft_start_music(t_game *game, pthread_t music)
{
	if (MUSIC)
	{
		pthread_create(&music, NULL, ft_music, game);
		pthread_detach(music);
	}
}

void	ft_stop_music(t_game *game, pthread_t music)
{
	if (MUSIC)
		pthread_cancel(music);
}

void	ft_init_struct(t_game *game, t_graphic *graphic)
{
	t_rayon		**rayon;

	game->twidth = WIDTH / PERF;
	game->theight = HEIGHT / PERF;
	game->keyboard.w = 0;
	game->keyboard.a = 0;
	game->keyboard.s = 0;
	game->keyboard.d = 0;
	game->keyboard.space = 0;
	game->keyboard.up = 0;
	game->keyboard.down = 0;
	game->keyboard.left = 0;
	game->keyboard.right = 0;
	game->size_p = SIZE_P_STANDING;
	rayon = ft_malloc_rayon(game);
	game->rayon = rayon;
	game->angle_x = 0;
	game->angle_z = 0;
	game->player_x = -1;
	game->player_y = -1;
	game->graphic = graphic;
	graphic->map_check = game;
	graphic->mlx = mlx_init();
	graphic->win = mlx_new_window(graphic->mlx, WIDTH, HEIGHT, "cub3d");
}

int main(int argc, char *argv[])
{
	t_game		game;
	t_graphic	graphic;
	pthread_t	music;

	ft_init_struct(&game, &graphic);
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
