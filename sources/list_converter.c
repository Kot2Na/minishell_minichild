/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 22:59:24 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/24 19:24:12 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_lst	*cnvrt_to_lst(char **array)
{
	t_lst	*list;
	int		i;

	i = 0;
	list = NULL;
	if (array)
	{
		while (array[i])
		{
			to_end(&list, new_lst(array[i]));
			i++;
		}
	}	
	return (list);
}

char	**cnvrt_to_arr(t_lst *list)
{
	char **result;
	int i;
	int n;

	i = 0;
	result = NULL;
	n = count_list(list) + 1;
	if ((result = (char **)malloc(sizeof(char *) * n)))
	{
		while (list)
		{
			result[i] = ft_strdup(list->data);
			list = list->next;
			i++;
		}
		result[i] = NULL;
	}
	return (result);
}
