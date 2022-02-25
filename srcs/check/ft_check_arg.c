/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:38:36 by tnard             #+#    #+#             */
/*   Updated: 2022/02/25 11:54:29 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_check_file(char *path)
{
	char	*ext;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	ext = ft_strrchr(path, '.');
	if (ext == NULL || ft_strncmp(".cub", ext, ft_strlen(".cub")) != 0)
		return (0);
	return (1);
}

void	ft_init(t_map_check *map_check)
{
	map_check->n = NULL;
	map_check->s = NULL;
	map_check->w = NULL;
	map_check->e = NULL;
	map_check->f = NULL;
	map_check->c = NULL;
	map_check->map = NULL;
}

int	ft_check_arg(int argc, char **argv, t_map_check *check)
{
	char		*str;
	int			fd;

	ft_init(check);
	if (argc != 2 || !ft_check_file(argv[1]))
		return (0);
	fd = open(argv[1], O_RDONLY);
	str = ft_get_file(fd, 0, 0);
	close(fd);
	if (str == NULL)
		return (0);
	if (!ft_check_texture(str, check))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}
