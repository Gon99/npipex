/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:36:50 by goliano-          #+#    #+#             */
/*   Updated: 2021/10/28 16:44:50 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		j;
	size_t	nl;

	j = 0;
	nl = ft_strlen(needle);
	if (nl == 0)
		return ((char *)haystack);
	while (*haystack != '\0' && len > 0)
	{
		while (haystack[j] == needle[j])
		{
			if (nl > len)
				return (NULL);
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack);
		}
		j = 0;
		len--;
		haystack++;
	}
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	return (NULL);
}
