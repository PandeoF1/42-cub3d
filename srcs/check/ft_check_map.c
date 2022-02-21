/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:18:22 by tnard             #+#    #+#             */
/*   Updated: 2022/02/21 16:56:53 by tnard            ###   ########lyon.fr   */
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
		if (ft_strlen(split[x]) > max)
			max = ft_strlen(split[x]);
		x++;
	}
	ft_free_split(split);
	return (max);
}

void	ft_add_space(char *str, int i, char **tmp, int x)
{
	int		y;
	char	*tmp2;

	y = ft_max_len(str + x);
	(*tmp) = malloc(sizeof(char) * y + 2);
	i = 0;
	while (i < y)
		(*tmp)[i++] = ' ';
	tmp2 = ft_strdup((*tmp));
	(*tmp)[i] = '\n';
	(*tmp)[i + 1] = '\0';
	(*tmp) = ft_strnjoin((*tmp), str + x, ft_strlen(str + x));
	(*tmp) = ft_strnjoin((*tmp), tmp2, ft_strlen(tmp2));
	free(tmp2);
}

int	ft_check_border(t_map_check *check,	int x, int y)
{
	char	**split;

	split = check->map;
	x = -1;
	while (split[++x])
	{
		y = -1;
		while (split[x][++y])
		{
			if (split[x][y] == ' ')
			{
				if (y != ft_strlen(split[x]) && split[x][y + 1]
					&& split[x][y + 1] == '0')
					return (0);
				if (y != 0 && split[x][y - 1] && split[x][y - 1] == '0')
					return (0);
				if (x != 0 && split[x - 1][y] && split[x - 1][y] == '0')
					return (0);
				if (x != ft_splitlen(split) - 1 && split[x + 1][y]
					&& split[x + 1][y] == '0')
					return (0);
			}
		}
	}
	return (1);
}

int	ft_check_map(t_map_check *check, int x, char *str)
{
	int		i;
	char	*tmp;
	char	**split;

	i = x;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '\n' && str[i + 1] == '\n'
			&& (str[i] != '\n' || str[i] != '0' || str[i] != '1'
				|| str[i] != ' ' || str[i] != 'N' || str[i] != 'E'
				|| str[i] != 'S' || str[i] != 'W'))
			return (0);
		i++;
	}
	check->max_x = ft_max_len(str + x) + 2; // to remove
	ft_add_space(str, i, &tmp, x);
	split = ft_split(tmp, '\n');
	i = 0;
	while (split[i])
	{
		split[i] = ft_strnjoinf(" ", split[i], ft_strlen(split[i]));
		split[i] = ft_strnjoin(split[i], " ", 1);
		i++;
	}
	check->map = split;
	return (ft_check_border(check, -1, 0));
}
