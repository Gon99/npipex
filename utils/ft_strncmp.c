/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:25:24 by goliano-          #+#    #+#             */
/*   Updated: 2021/10/29 11:43:01 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (n > 0)
	{
		if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
			return (1);
		if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
			return (-1);
		if (!((unsigned char *)s1)[i] || !((unsigned char *)s2)[i])
			return (0);
		i++;
		n--;
	}
	return (0);
}
