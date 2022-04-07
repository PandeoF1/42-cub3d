/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:15:13 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/07 09:09:09 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	int	i;

	i = 0;
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
	if (game->t)
		free(game->t);
	while (i < DOOR_LEN)
		if (game->z[i])
			free(game->z[i]);
	ft_free_rayon(game->rayon, game);
	if (game->s_color-- > 0)
		mlx_destroy_image(game->graphic->mlx, game->img_n.img_ptr);
	if (game->s_color-- > 0)
		mlx_destroy_image(game->graphic->mlx, game->img_s.img_ptr);
	if (game->s_color-- > 0)
		mlx_destroy_image(game->graphic->mlx, game->img_w.img_ptr);
	if (game->s_color-- > 0)
		mlx_destroy_image(game->graphic->mlx, game->img_e.img_ptr);
	if (game->s_color-- > 0)
		mlx_destroy_image(game->graphic->mlx, game->img_t.img_ptr);
	i = 0;
	while (i < DOOR_LEN)
		if (game->s_color-- > 0)
			mlx_destroy_image(game->graphic->mlx, game->door_color[i].img_ptr);
	mlx_destroy_window(game->graphic->mlx, game->graphic->win);
	mlx_destroy_display(game->graphic->mlx);
	printf("Cub3d: exit\n");
}
