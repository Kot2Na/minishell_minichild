/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 20:39:09 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/29 22:16:25 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int		check_exist(char **path, char *com)
{
	int		i;
	int		result;
	char	*box;

	i = 0;
	result = 0;
	while (path[i])
	{
		box = join_three(path[i], "/", com);
		if (!access(box, F_OK))
		{
			result = 1;
			free(box);
			break ;
		}
		free(box);
		i++;
	}
	return (result);
}

char	*path_to_bin(char **path, char *com)
{
	int		i;
	char	*box;

	i = 0;
	while (path[i])
	{
		box = join_three(path[i], "/", com);
		if (!access(box, F_OK))
			return (box);
		free(box);
		i++;
	}
	return (NULL);
}
