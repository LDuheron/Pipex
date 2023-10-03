/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:52:49 by lduheron          #+#    #+#             */
/*   Updated: 2023/05/11 15:56:27 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_init(t_pipex *pipex)
{
	pipex->fd[0] = -1;
	pipex->fd[1] = -1;
	pipex->file_in = -1;
	pipex->file_out = -1;
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (check_path_exist(env) == 0)
		return (0);
	if (argc != 5)
		return (ft_putstr_fd("Wrong number of arguments.", 2));
	pipex_init(&pipex);
	if (pipe(pipex.fd) == -1)
		return (ft_putstr_fd("Error pipe", 2));
	pipex.pid1 = fork ();
	if (pipex.pid1 == -1)
		return (ft_putstr_fd("Error fork", 2));
	else if (pipex.pid1 == 0)
		child_process(argv, env, &pipex);
	pipex.pid2 = fork ();
	if (pipex.pid2 == -1)
		return (ft_putstr_fd("Error fork ", 2));
	else if (pipex.pid2 == 0)
		parent_process(argv, env, &pipex);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
