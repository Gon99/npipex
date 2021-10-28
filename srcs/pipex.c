/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:32:36 by goliano-          #+#    #+#             */
/*   Updated: 2021/10/28 16:46:20 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/pipex.h"

void	handle_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i])
	{
		path = ft_strnstr(env[i], "PATH", ft_strlen(env[i]));
		i++;
	}
	printf("PATH: %s\n", path);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 0)
		return (0);
	argv = NULL;
	handle_path(envp);	
}
