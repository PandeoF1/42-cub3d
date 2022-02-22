/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:19:11 by tnard             #+#    #+#             */
/*   Updated: 2022/02/22 11:37:45 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_add_texture(char *split, t_map_check *check, int x, int y)
{
	if (split[0] == 'N' && !check->n)
		check->n = ft_strdup(split);
	else if (split[0] == 'S' && !check->s)
		check->s = ft_strdup(split);
	else if (split[0] == 'W' && !check->w)
		check->w = ft_strdup(split);
	else if (split[0] == 'E' && !check->e)
		check->e = ft_strdup(split);
	else if (split[0] == 'F' && !check->f)
		check->f = ft_strdup(split);
	else if (split[0] == 'C' && !check->c)
		check->c = ft_strdup(split);
	else
		return (0);
	return (1);
}

int	ft_pos(char *line, char *str)
{
	int	i;
	int	j;
	int	i_temp;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (line[j] == str[i])
		{
			i_temp = i;
			while (line[j] && str[i] && line[j] == str[i])
			{
				i++;
				j++;
			}
			if (j == ft_strlen(line))
				return (i_temp);
		}
		i++;
	}
	return (0);
}

int	ft_check_texture(char *str, t_map_check *check)
{
	char	**split;
	int		x;
	int		y;

	x = 0;
	split = ft_split(str, '\n');
	while (split[x])
	{
		if (!ft_add_texture(split[x], check, x, y))
			return (0);
		if (check->n && check->s && check->w
			&& check->e && check->f && check->c && split[x + 1])
		{
			if (ft_check_map(check, ft_pos(split[x + 1], str), str, 0))
			{
				ft_free_split(split);
				return (1);
			}
			ft_free_split(split);
			return (0);
		}
		x++;
	}
	ft_free_split(split);
	return (0);
}
