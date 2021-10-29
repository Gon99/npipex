/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:43:12 by goliano-          #+#    #+#             */
/*   Updated: 2021/10/29 11:43:57 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	check_char(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	r;
	size_t	i;
	size_t	l;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	l = ft_strlen(s1);
	while (s1[i] != '\0' && check_char(s1[i], set))
		i++;
	while (i < l && check_char(s1[l - 1], set))
		l--;
	trimmed = (char *)malloc((l - i + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	r = 0;
	while (i < l)
		trimmed[r++] = s1[i++];
	trimmed[r] = '\0';
	return (trimmed);
}
