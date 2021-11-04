/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:32:36 by goliano-          #+#    #+#             */
/*   Updated: 2021/11/04 17:05:13 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/pipex.h"

void	handle_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	*cmd_one;
	char	**mycmdargs;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	path = ft_strtrim(envp[i], "PATH=");
	all_paths = ft_split(path, ':');
	mycmdargs = ft_split(cmd, ' ');
	printf("my1: %s\n", mycmdargs[0]);
	printf("my2: %s\n", mycmdargs[1]);
	i = 0;
	while (all_paths[i])
	{
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		printf("C: %s\n", cmd_one);
		execve(cmd_one, mycmdargs, envp);
		i++;
	}
}

static void	do_child_one(int fd, char *cmd, int *end, char **envp)
{
	int	r;

	close(end[0]);
	write(1, "hola0\n", 6);
	r = dup2(fd, STDIN_FILENO);
	close(fd);
	//printf("R1: %d\n", r);
	write(1, "hola1\n", 6);
	r = dup2(end[1], STDOUT_FILENO);
	//close(end[1]);
	write(1, "hola2\n", 6);
	//printf("R2: %d\n", r);
	handle_path(cmd, envp);
	//printf("FIN\n");
}

/*static void	do_child_two(int fd, char **argv, int *end, char **envp)
{
	int	nfd;

	printf("FD2: %d\n", fd);
	close(end[1]);
	nfd = open(argv[4], O_WRONLY);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	dup2(nfd, STDOUT_FILENO); //para que lo escriba en el archivo
	handle_path(argv[3], envp);
	
}*/

static void	do_parent_one(char *cfd, char *cmd, int *end, char **envp)
{
	int status;
	int	r;
	int	fd;

	status = 0;
	r = 0;
	//wait(&status);
	write(1, "padre0\n", 7);
	close(end[1]);
	r = dup2(end[0], STDIN_FILENO);
	//close(end[0]);
	write(1, "padre1\n", 7);
	fd = open(cfd, O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(1, "hgg\n", 4);
	r = dup2(fd, STDOUT_FILENO);
	close(fd);
	write(1, "padre2\n", 7);
	printf("CMD: %s\n", cmd);
	printf("ENVP[0]: %s\n", envp[0]);
	//handle_path(cmd, envp);
}

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

static void	pipex(int fd1, char **argv, char **envp)
{
	int	end[2];
	//int	status;
	pid_t	p1;
	//pid_t	p2;

	pipe(end);
	p1 = fork();
	printf("P1: %d\n", p1);
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		do_child_one(fd1, argv[2], end, envp);
	else
		do_parent_one(argv[4], argv[3], end, envp);
	printf("FIN\n");
	/*p2 = fork();
	if (p2 < 0)
		return (perror("Fork: "));
	else if(p2 == 0)
		do_child_two(fd2, argv, end, envp);
	else
		close(end[0]);
	waitpid(p1, &status, 0);
	waitpid(p2, &status, 0);*/
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	//int	fd2;

	if (argc == 0)
		return (1);
	fd1 = open(argv[1], O_RDONLY);
	//fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 /*|| fd2 < 0*/)
		return (-1);
	argv[2] = handle_cmd(argv[2]);
	argv[3] = handle_cmd(argv[3]);
	pipex(fd1, argv, envp);
	return (0);
}
