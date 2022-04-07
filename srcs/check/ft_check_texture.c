/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:19:11 by tnard             #+#    #+#             */
/*   Updated: 2022/04/07 10:20:42 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_add_texture(char *split, t_game *game)
{
	if (split[0] == 'N' && !game->n)
		game->n = ft_strdup(split);
	else if (split[0] == 'S' && !game->s)
		game->s = ft_strdup(split);
	else if (split[0] == 'W' && !game->w)
		game->w = ft_strdup(split);
	else if (split[0] == 'E' && !game->e)
		game->e = ft_strdup(split);
	else if (split[0] == 'F' && !game->f)
		game->f = ft_strdup(split);
	else if (split[0] == 'C' && !game->c)
		game->c = ft_strdup(split);
	else if (split[0] == 'T' && !game->t)
		game->t = ft_strdup(split);
	else if (split[0] == 'Z' && !game->z[0])
		game->z[0] = ft_strdup(split);
	else if (split[0] == 'B' && !game->z[1])
		game->z[1] = ft_strdup(split);
	else if (split[0] == 'V' && !game->z[2])
		game->z[2] = ft_strdup(split);
	else if (split[0] == 'C' && !game->z[3])
		game->z[3] = ft_strdup(split);
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
			if (j == (int)ft_strlen(line))
				return (i_temp);
		}
		i++;
	}
	return (0);
}

int	ft_check_texture_util(t_game *game, char **split, char *str, int x)
{
	if (ft_check_map(game, ft_pos(split[x + 1], str),
			str, ft_pos(split[x + 1], str)))
	{
		ft_free_split(split);
		return (1);
	}
	ft_free_split(split);
	return (0);
}

int	ft_check_texture(char *str, t_game *game)
{
	char	**split;
	int		x;

	x = -1;
	split = ft_split(str, '\n');
	while (split[++x])
	{
		if (!ft_add_texture(split[x], game))
		{
			ft_free_split(split);
			return (0);
		}
		if (game->n && game->s && game->w
			&& game->e && game->f && game->c && game->t && game->z[0] && \
			game->z[1] && game->z[2] && game->z[3] && split[x + 1])
		{
			return (ft_check_texture_util(game, split, str, x));
		}
	}
	ft_free_split(split);
	return (0);
}
