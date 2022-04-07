/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:20:03 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/01 11:44:25 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_set_rayons(t_update *update, t_game *game)
{
	update->rayon_tempp.y = game->rayon[update->i][update->j].y
		* game->cos_x + game->rayon[update->i][update->j].z * -game->sin_x;
	update->rayon_tempp.z = game->rayon[update->i][update->j].y
		* game->sin_x + game->rayon[update->i][update->j].z * game->cos_x;
	update->rayon_tempp.x = game->rayon[update->i][update->j].x
		* game->cos_z + update->rayon_tempp.y * -game->sin_z;
	update->rayon_tempp.y = game->rayon[update->i][update->j].x
		* game->sin_z + update->rayon_tempp.y * game->cos_z;
	update->rayon_tempp.z = game->rayon[update->i][update->j].y
		* game->sin_x + game->rayon[update->i][update->j].z * game->cos_x;
}

void	ft_set_switch(t_update *update, t_game *game)
{
	if (update->v == 0)
	{
		update->switch_plan = game->max_y;
		update->u = game->player_y;
	}
	else if (update->v == 1)
	{
		update->switch_plan = game->max_x;
		update->u = game->player_x;
	}
	else if (update->v == 2)
		update->switch_plan = game->nb_sprites - 1;
	else if (update->v == 3)
		update->switch_plan = game->nb_door;
	update->add = 1;
	if ((update->v == 0 && update->rayon_tempp.y < 0)
		|| (update->v == 1 && update->rayon_tempp.x < 0))
		update->add = -1;
	else if (update->v == 3 && update->rayon_tempp.y < 0)
	{
		update->add = -1;
		update->u = game->nb_door;
	}
}

void	ft_set_var(t_update *update)
{
	update->best_t = 0;
	update->v_plan = 4;
	update->u_plan = -7;
	update->v = 0;
	update->best_x = -7;
	update->best_y = -7;
}

void	ft_set_sprites(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->nb_sprites)
	{
		game->plan[2][x].a = game->sprites[x].sx - game->player_x;
		game->plan[2][x].b = game->sprites[x].sy - game->player_y;
		game->plan[2][x].c = 0;
		game->plan[2][x].d = -(game->plan[2][x].a * game->sprites[x].sx)
			- (game->plan[2][x].b * game->sprites[x].sy);
		x++;
	}
}
