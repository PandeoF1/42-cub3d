/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:59:07 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/04 11:21:45 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int	ft_is_double_x(char	**str, int x)
{
	int	y;

	y = 0;
	while (str[y] && str[y][x] && str[y][x - 1])
	{
		if (str[y][x] != str[y][x - 1])
			return (0);
		y++;
	}
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
