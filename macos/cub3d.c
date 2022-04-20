/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:17 by tnard             #+#    #+#             */
/*   Updated: 2022/04/20 13:36:57 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	ft_set_points(t_update *update, t_game *game, float t)
{
	update->point_x = update->rayon_tempp.x * t;
	update->point_y = update->rayon_tempp.y * t;
	update->point_z = game->size_p + update->rayon_tempp.z * t;
	update->px_px = (game->player_x + update->point_x);
	update->py_py = (game->player_y + update->point_y);
}

void	*ft_updater(void	*data)
{
	t_update	*update;
	t_game		*game;

	update = (t_update *)data;
	game = update->game;
	update->i = 0;
	while (update->i < game->theight)
	{
		update->j = update->start_y;
		while (update->j < update->end_y)
		{
			ft_updater_5(update, game);
			update->t = 0;
			update->j++;
		}
		update->i++;
	}
	return (0);
}

void	ft_threads(t_game *game, t_update *updt, pthread_t *thread, t_img *img)
{
	int	x;

	x = 0;
	while (x < NB_THREAD)
	{
		updt[x].img = img;
		if (x == 0)
			updt[x].start_y = 0;
		else
			updt[x].start_y = (x * game->twidth) / NB_THREAD;
		updt[x].end_y = ((x + 1) * game->twidth) / NB_THREAD;
		updt[x].game = game;
		pthread_create(&thread[x], NULL, &ft_updater, &updt[x]);
		x++;
	}
	x = 0;
	while (x < NB_THREAD)
		pthread_join(thread[x++], NULL);
}

int	ft_update(t_game *game)
{
	t_update	update[NB_THREAD];
	pthread_t	thread[NB_THREAD];
	t_img		img;

	ft_door(game);
	ft_move(game);
	ft_mouse(game);
	ft_set_sprites(game);
	img.img_ptr = mlx_new_image(game->graphic->mlx,
			game->twidth, game->theight);
	img.data = (int *)mlx_get_data_addr(img.img_ptr,
			&img.bpp, &img.size_l, &img.endian);
	ft_threads(game, update, thread, &img);
	if (game->minimap > 0)
		ft_map(game, img);
	ft_put_image(game, img);
	mlx_string_put(game->graphic->mlx, game->graphic->win \
		, (WIDTH * 0.5) - 2, (HEIGHT * 0.5) + 4, 0xFF0000, "+");
	ft_fps(game);
	mlx_destroy_image(game->graphic->mlx, img.img_ptr);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game		game;
	t_graphic	graphic;

	game.s_color = 0;
	ft_init_struct(&game, &graphic);
	ft_start_music(&game, game.music);
	if (ft_check_arg(argc, argv, &game)
		&& ft_get_pos(&game) && ft_create_image_n_s(&game))
	{
		ft_create_vector(&game);
		ft_create_plan(&game);
		mlx_loop_hook(graphic.mlx, ft_update, &game);
		mlx_mouse_hide(graphic.mlx, graphic.win);
		mlx_hook(graphic.win, 17, 1L << 17, ft_exit_hook, &game);
		mlx_hook(graphic.win, 02, 1L << 0, ft_win_event, &game);
		mlx_hook(graphic.win, 03, 1L << 1, ft_unpress, &game);
		mlx_mouse_hide(graphic.mlx, graphic.win);
		mlx_loop(graphic.mlx);
	}
	else
		ft_printf("Error\n");
	ft_stop_music(game.music);
	ft_close(&game);
	return (0);
}
