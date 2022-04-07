/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_music.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:02:34 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/07 10:26:49 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	*ft_music(void *data)
{
	t_game	*game;

	game = (t_game *)data;
	while (42)
		system("afplay music.mp3");
}

void	ft_start_music(t_game *game, pthread_t music)
{
	if (MUSIC)
	{
		pthread_create(&music, NULL, ft_music, game);
		pthread_detach(music);
	}
}

void	ft_stop_music(pthread_t music)
{
	if (MUSIC)
		pthread_cancel(music);
}
