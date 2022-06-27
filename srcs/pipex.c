/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:39:06 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/27 11:43:16 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*handle_cmd(char *cmd)
{
	int		l;
	int		i;
	char	*n_cmd;

	l = ft_strlen(cmd);
	n_cmd = malloc(sizeof(char) * (l + 2));
	if (!n_cmd)
		return (0);
	l = 1;
	i = 0;
	n_cmd[0] = '/';
	while (cmd[i])
		n_cmd[l++] = cmd[i++];
	n_cmd[l] = '\0';
	return (n_cmd);
}

static void	do_child_one(int fd, char *cmd, int *end, char **envp)
{
	close(end[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(end[1], STDOUT_FILENO);
	handle_path(cmd, envp);
}

static void	do_child_two(int fd, char *cmd, int *end, char **envp)
{
	close(end[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(end[0], STDIN_FILENO);
	handle_path(cmd, envp);
}

static void	pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		end[2];
	pid_t	p1;
	pid_t	p2;
	int		status;

	pipe(end);
	p1 = fork();
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		do_child_one(fd1, argv[2], end, envp);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
		return ;
	p2 = fork();
	if (p2 < 0)
		return (perror("Fork: "));
	if (p2 == 0)
		do_child_two(fd2, argv[3], end, envp);
	close(end[0]);
	close(end[1]);
	waitpid(p2, &status, 0);
	if (WEXITSTATUS(status))
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
		return (1);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("Error");
		return (0);
	}
	if (check_cmd_path(argv[2]))
		argv[2] = handle_cmd(argv[2]);
	if (check_cmd_path(argv[3]))
		argv[3] = handle_cmd(argv[3]);
	printf("ARGV[2]: %s\n", argv[2]);
	printf("ARGV[3]: %s\n", argv[3]);
	pipex(fd1, fd2, argv, envp);
	return (0);
}
