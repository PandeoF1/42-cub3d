/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:38:36 by tnard             #+#    #+#             */
/*   Updated: 2022/04/21 13:45:05 by tnard            ###   ########lyon.fr   */
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

void	ft_init(t_game *game)
{
	game->n = NULL;
	game->s = NULL;
	game->w = NULL;
	game->e = NULL;
	game->f = NULL;
	game->c = NULL;
	game->t = NULL;
	game->z[0] = NULL;
	game->z[1] = NULL;
	game->z[2] = NULL;
	game->z[3] = NULL;
	game->map = NULL;
}

int	ft_check_arg(int argc, char **argv, t_game *game)
{
	char		*str;
	int			fd;

	ft_init(game);
	if (argc != 2 || !ft_check_file(argv[1]))
		return (0);
	fd = open(argv[1], O_RDONLY);
	str = ft_get_file(fd, 0, 0);
	close(fd);
	if (str == NULL)
		return (0);
	if (!ft_check_texture(str, game))
	{
		free(str);
		return (0);
	}
	free(str);
	mlx_mouse_move(game->graphic->win, game->twidth / 2, game->theight / 2);
	return (1);
}
