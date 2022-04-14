/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fps.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:33:04 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/14 13:43:09 by tnard            ###   ########lyon.fr   */
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
			2, 30, 0xffffff, "Moy FPS: ");
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
