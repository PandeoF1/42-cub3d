/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_and_fps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:22:18 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/01 12:22:54 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
