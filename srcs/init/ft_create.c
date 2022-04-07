/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:38:10 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/07 10:26:59 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			r_v = 2 * tan((60 * PI / 180)
					* game->theight / (game->twidth * 2)) / game->theight;
			game->rayon[i][j].x = ((j - game->twidth * 0.5) * r_h);
			game->rayon[i][j].y = -1.0;
			game->rayon[i][j].z = ((game->theight * 0.5 - i) * r_v);
			j++;
		}
		i++;
	}
}

int	ft_init_sprite(t_game *game, int b, int x, int y)
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
	while (a < (int)ft_strlen(charset))
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
