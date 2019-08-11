/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 21:03:32 by crycherd          #+#    #+#             */
/*   Updated: 2019/08/11 05:48:55 by crycherd         ###   ########.fr       */
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

void del_double_arr(char **arr)
{
	int i;

	i = 0;
	if (arr)
	{
		while(arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

int	check_path(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int count_list(t_lst *list)
{
	int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}
