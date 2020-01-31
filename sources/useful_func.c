/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 21:03:32 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/31 23:09:55 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	*join_three(char *fr, char *sc, char *th)
{
	char	*box;

	box = NULL;
	if (fr && sc && th)
	{
		fr = ft_strjoin(fr, sc);
		box = ft_strjoin(fr, th);
		free(fr);
	}
	return (box);
}

int		count_list(t_lst *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int		count_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

char	**split_wquote(char *str, char c, int k)
{
	t_lst	*argv;
	char	**result;
	int		i;
	int		flag;

	i = 0;
	argv = NULL;
	flag = 1;
	while (str[i])
	{
		if (str[i] && str[i] == c && flag)
		{
			add_to_list(str, i, &argv, k);
			str += i + 1;
			i = 0;
		}
		if (str[i] == '"')
			change_flag(&flag);
		i++;
	}
	add_to_list(str, i, &argv, k);
	result = cnvrt_to_arr(argv);
	lst_del(argv);
	return (result);
}

void	change_flag(int *flag)
{
	if (flag)
	{
		if (*flag == 1)
			*flag = 0;
		else
			*flag = 1;
	}
}
