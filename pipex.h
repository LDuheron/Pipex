/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:01:00 by lduheron          #+#    #+#             */
/*   Updated: 2023/05/11 15:59:51 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "./utils/PrintF/ft_printf.h"

typedef struct s_pipex {
	int		fd[2];
	int		file_in;
	int		file_out;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

// Check_env.c
int			check_path_exist(char **env);

// Error_management.c
void		clean(char **cmd, char *path, t_pipex *pipex);
int			ft_putstr_fd(char *s, int fd);

// Exec.c
int			ft_exec(char *argv, char **env, t_pipex *pipex);
char		*find_path(char *cmd, char **path_tableau);
char		**get_path(char **env);

// Ft_split.c
char		**ft_split(char *s, char c);
int			wdcount(char const *s, char c);

// Pipex_utils.c
int			ft_strlen(char const *str);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strdup(char *src);

// Main.c
void		pipex_init(t_pipex *pipex);
int			main(int argc, char **argv, char **env);

// Process.c
void		parent_process(char **argv, char **env, t_pipex *pipex);
void		child_process(char **argv, char **env, t_pipex *pipex);

#endif
