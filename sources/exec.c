/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 20:39:09 by crycherd          #+#    #+#             */
/*   Updated: 2019/08/09 21:07:31 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char *join_three(char *fr, char *sc, char *th)
{
	char *box;
	box = NULL;
	if (fr && sc && th)
	{
		fr = ft_strjoin(fr, sc);
		box = ft_strjoin(fr, th);
		free(fr);
	}
	return (box);
}

int		check_exist(char **path, char *com)
{
	int i;
	int	result;
	char *box;

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
