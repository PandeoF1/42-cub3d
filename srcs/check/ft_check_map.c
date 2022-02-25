/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:18:22 by tnard             #+#    #+#             */
/*   Updated: 2022/02/25 12:14:56 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_add_space(char *str, int i, char **tmp, int x)
{
	int		y;
	char	*tmp2;

	y = ft_max_len(str + x);
	(*tmp) = malloc(sizeof(char) * y + 2);
	i = 0;
	while (i < y)
		(*tmp)[i++] = ' ';
	(*tmp)[i] = '\n';
	(*tmp)[i + 1] = '\0';
	tmp2 = ft_strdup((*tmp));
	(*tmp) = ft_strnjoin((*tmp), str + x, ft_strlen(str + x));
	if ((*tmp)[ft_strlen(*tmp) - 1] != '\n')
		(*tmp) = ft_strnjoin((*tmp), "\n", 1);
	(*tmp) = ft_strnjoin((*tmp), tmp2, ft_strlen(tmp2));
	free(tmp2);
}

int	ft_check_corner(char **split, int x, int y)
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
	if (y != ft_strlen(split[x]) && x != 0 && split[x - 1][y + 1]
		&& split[x - 1][y + 1] == '0')
		return (0);
	if (y != 0 && x != 0 && split[x - 1][y - 1] && split[x - 1][y - 1] == '0')
		return (0);
	if (split[x + 1] && x != ft_splitlen(split) && y != ft_strlen(split[x + 1])
		&& split[x + 1][y + 1] && split[x + 1][y + 1] == '0')
		return (0);
	if (x != ft_splitlen(split) - 1 && y != 0 && split[x + 1][y - 1]
		&& split[x + 1][y - 1] == '0')
		return (0);
	return (1);
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
			if (split[x][y] == ' ' && !ft_check_corner(split, x, y))
				return (0);
	}
	return (1);
}

char	*ft_nspace(char *str, int x)
{
	int		y;
	int		a;
	char	*tmp;

	a = 0;
	y = ft_strlen(str);
	tmp = malloc(sizeof(char) * x - y + 1);
	while (a < x - y)
		tmp[a++] = ' ';
	tmp[a] = '\0';
	tmp = ft_strnjoinf(str, tmp, ft_strlen(str));
	free(str);
	return (tmp);
}

int	ft_check_map(t_map_check *check, int x, char *str, int i)
{
	char	*tmp;
	char	**split;
	char	*space;

	while (str[i])
	{
		if (str[i + 1] && str[i] == '\n' && str[i + 1] == '\n'
			&& (str[i] != '\n' || str[i] != '0' || str[i] != '1'
				|| str[i] != ' ' || str[i] != 'N' || str[i] != 'E'
				|| str[i] != 'S' || str[i] != 'W'))
			return (0);
		i++;
	}
	check->max_x = ft_max_len(str + x);
	ft_add_space(str, i, &tmp, x);
	split = ft_split(tmp, '\n');
	i = -1;
	while (split[++i])
	{
		split[i] = ft_strnjoinf(" ", split[i], ft_strlen(split[i]));
		split[i] = ft_nspace(split[i], ft_max_len(str + x) + 2);
	}
	check->map = split;
	free(tmp);
	return (ft_check_border(check, -1, 0));
}
