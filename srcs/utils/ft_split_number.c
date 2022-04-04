/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:19:14 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/04 10:19:21 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
