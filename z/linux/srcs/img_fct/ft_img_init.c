/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:45:49 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/07 10:27:28 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_data_image(t_game *game)
{
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

int	ft_create_image_util(t_game *game)
{
	if (ft_image_len(game->w, 2) == 0)
		return (0);
	if (ft_check_image(game->w + 3))
		game->img_w.img_ptr = ft_open_xpm(game, game->w + 3,
				game->img_w.size_l);
	else
		return (0);
	game->s_color++;
	if (ft_image_len(game->e, 2) == 0)
		return (0);
	if (ft_check_image(game->e + 3))
		game->img_e.img_ptr = ft_open_xpm(game, game->e + 3,
				game->img_e.size_l);
	else
		return (0);
	game->s_color++;
	if (ft_image_len(game->t, 2) == 0)
		return (0);
	if (ft_check_image(game->t + 3))
		game->img_t.img_ptr = ft_open_xpm(game, game->t + 3,
				game->img_t.size_l);
	else
		return (0);
	game->s_color++;
	return (1);
}

int	ft_create_image_e_w(t_game *game)
{
	int	i;

	i = 0;
	if (ft_create_image_util(game) == 0)
		return (0);
	while (i < DOOR_LEN)
	{
		if (ft_image_len(game->z[i], 2) == 0)
			return (0);
		if (ft_check_image(game->z[i] + 3))
			game->door_color[i].img_ptr = ft_open_xpm(game, game->z[i] + 3,
					game->door_color[i].size_l);
		else
			return (0);
		game->s_color++;
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
	game->s_color++;
	if (ft_image_len(game->s, 2) == 0)
		return (0);
	if (ft_check_image(game->s + 3))
		game->img_s.img_ptr = ft_open_xpm(game, game->s + 3,
				game->img_s.size_l);
	else
		return (0);
	game->s_color++;
	if (ft_create_image_e_w(game) != 1)
		return (0);
	return (ft_data_image(game));
}
