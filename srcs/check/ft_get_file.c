/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:15:26 by tnard             #+#    #+#             */
/*   Updated: 2022/02/21 16:24:42 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = -1;
	while (++i < n && src[i])
		dest[i] = src[i];
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

char	*ft_get_file(int fd, int size, int len)
{
	char	buf[2048];
	char	*value;
	char	*tmp;

	value = malloc(sizeof(char));
	if (!value)
		return (NULL);
	len = read(fd, buf, 2048);
	while (len > 0)
	{
		tmp = malloc((size + len + 1) * sizeof(char));
		if (!tmp)
			break ;
		tmp = ft_strncpy(tmp, value, size);
		free(value);
		ft_strncpy(tmp + size, buf, len);
		value = tmp;
		size += len;
		value[size] = '\0';
		len = read(fd, buf, 2048);
	}
	if (len)
		free(value);
	return (value);
}
