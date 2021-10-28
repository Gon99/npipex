/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:10:16 by goliano-          #+#    #+#             */
/*   Updated: 2021/10/28 16:36:44 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	*ft_memset(void	*b, int c, size_t len)
{
	unsigned char	*aux;

	aux = b;
	while (len > 0)
	{
		*aux = (unsigned char)c;
		len--;
		aux++;
	}
	return (b);
}
