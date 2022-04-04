/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:45:49 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/04 08:58:51 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
