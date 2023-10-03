/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:55:09 by lduheron          #+#    #+#             */
/*   Updated: 2023/05/11 15:55:44 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_path_exist(char **env)
{
	int	i;

	i = 0;
	if (env == NULL)
		return (0);
	while (*env != 0)
	{
		if (ft_strncmp("PATH=", *env, 5) == 0)
			return (1);
		env++;
	}
	ft_putstr_fd("Error path.\n", 2);
	return (0);
}
