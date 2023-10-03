/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:51:27 by lduheron          #+#    #+#             */
/*   Updated: 2023/05/12 15:38:48 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
{
	int	i;

	i = 0;
	if (!*env)
		return (NULL);
	while (ft_strncmp("PATH=", *env, 5) != 0)
		env++;
	if (ft_strncmp("PATH=", *env, 5) == 0)
		return (ft_split(*env + 5, ':'));
	else
	{
		ft_putstr_fd("Error.\n", 2);
		return (NULL);
	}
}

char	*find_path(char *cmd, char **path_tableau)
{
	char	*path;
	char	*path_tmp;
	char	*path_tmp2;
	int		i;

	path = NULL;
	i = -1;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (path_tableau[++i])
	{
		path_tmp = ft_strjoin(path_tableau[i], "/");
		free(path_tableau[i]);
		path_tmp2 = ft_strjoin(path_tmp, cmd);
		free(path_tmp);
		if (access(path_tmp2, F_OK) == 0)
		{
			path = ft_strdup(path_tmp2);
			free(path_tmp2);
			break ;
		}
		free(path_tmp2);
	}
	while (path_tableau[i++])
		free(path_tableau[i]);
	return (free(path_tableau), path);
}

int	ft_exec(char *argv, char **env, t_pipex *pipex)
{
	char	**cmd;
	char	*path;
	char	**path_tableau;
	int		i;

	i = 0;
	path_tableau = NULL;
	path = NULL;
	cmd = NULL;
	path_tableau = get_path(env);
	cmd = ft_split(argv, 32);
	path = find_path(cmd[0], path_tableau);
	if (path == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		clean(cmd, path, pipex);
		exit(1);
	}
	if (execve(path, cmd, env) == 0)
	{
		ft_putstr_fd("Error execv\n", 2);
		clean(cmd, path, pipex);
	}
	return (0);
}
