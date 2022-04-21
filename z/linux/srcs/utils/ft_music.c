/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_music.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:02:34 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/08 14:52:04 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	*ft_music(void *data)
{
	(void) data;
	while (42)
		if (system("afplay music.mp3"))
			sleep(5);
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
