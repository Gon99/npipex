/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:15:11 by goliano-          #+#    #+#             */
/*   Updated: 2021/11/03 17:02:46 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strcatslash(char *dst)
{
	size_t	i;
	size_t	x;
	char	*aux;

	i = 0;
	x = 0;
	while (dst[i])
		i++;
	aux = malloc(sizeof(char) * (i + 2));
	if (!aux)
		return (0);
	i = 0;
	while (dst[i])
		dst[i++] = aux[x++];
	aux[x] = '/';
	dst[x + 1] = '\0';
	return (aux);
}
