/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:57:26 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/04 11:23:32 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	*ft_open_xpm(t_game *game, char *str, int size_x)
{
	return (mlx_xpm_file_to_image(
			game->graphic->mlx, str, &size_x,
			&size_x));
}

int	ft_color_format(char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (ft_splitlen(split) != 3 || !ft_split_number(split))
	{
		ft_free_split(split);
		return (-1);
	}
	return ((ft_atoi(split[0]) << 16)
		+ (ft_atoi(split[1]) << 8) + ft_atoi(split[2]));
}

int	ft_image_len(char *str, int y)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (x > y - 1)
			if (x == y && str[x] != ' ')
				return (0);
		x++;
	}
	if (str[x - 1] == ' ' || x < y + 2)
		return (0);
	return (x);
}

int	ft_check_image(char *path)
{
	char	*ext;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	ext = ft_strrchr(path, '.');
	if (ext == NULL || ft_strncmp(".xpm", ext, ft_strlen(".xpm")) != 0)
		return (0);
	return (1);
}

void	ft_put_image(t_game *game, t_img img2)
{
	int		i;
	int		j;
	t_img	img;

	img.img_ptr = mlx_new_image(game->graphic->mlx, WIDTH, HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr,
			&img.bpp, &img.size_l, &img.endian);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			img.data[(i) * WIDTH + (j)]
				= img2.data[((i / PERF) * game->twidth + (j / PERF))];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->graphic->mlx, game->graphic->win,
		img.img_ptr, 0, 0);
	mlx_destroy_image(game->graphic->mlx, img.img_ptr);
}
