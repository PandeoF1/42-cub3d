/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:42:13 by tnard             #+#    #+#             */
/*   Updated: 2022/04/07 10:21:10 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_max_len(char *str)
{
	char	**split;
	int		x;
	int		max;

	x = 0;
	max = 0;
	split = ft_split(str, '\n');
	while (split[x])
	{
		if ((int)ft_strlen(split[x]) > max)
			max = ft_strlen(split[x]);
		x++;
	}
	ft_free_split(split);
	return (max);
}
