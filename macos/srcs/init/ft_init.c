/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:38:34 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/12 09:38:35 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	game->minimap = -1;
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

t_rayon	**ft_malloc_rayon(t_game *game)
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
