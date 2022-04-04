/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_flip_img.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:29:54 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/04 11:30:03 by asaffroy         ###   ########lyon.fr   */
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
