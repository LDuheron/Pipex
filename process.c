/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:56:32 by lduheron          #+#    #+#             */
/*   Updated: 2023/05/11 15:56:44 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **env, t_pipex *pipex)
{
	pipex->file_in = open(argv[1], O_RDONLY, 0777);
	if (pipex->file_in < 0)
	{
		ft_printf("pipex: %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}	
	dup2(pipex->fd[1], 1);
	if (pipex->fd[0] != -1)
		close(pipex->fd[0]);
	dup2(pipex->file_in, 0);
	if (pipex->file_in != -1)
		close(pipex->file_in);
	ft_exec(argv[2], env, pipex);
}

void	parent_process(char **argv, char **env, t_pipex *pipex)
{
	pipex->file_out = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex->file_out < 0)
	{
		ft_printf("pipex: %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	dup2(pipex->file_out, 1);
	if (pipex->file_out != -1)
		close(pipex->file_out);
	dup2(pipex->fd[0], 0);
	if (pipex->fd[1] != -1)
		close(pipex->fd[1]);
	ft_exec(argv[3], env, pipex);
}
