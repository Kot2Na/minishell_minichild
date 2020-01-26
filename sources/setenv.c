/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:10:04 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/26 22:09:09 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_lst	*find_env(t_lst *list, char *name)
{
	t_lst	*iter;
	int		size;

	iter = NULL;
	if (list)
	{
		iter = list;
		size = ft_strlen(name);
		while (iter)
		{
			if (!ft_strncmp(iter->data, name, size) && iter->data[size] == '=')
				return (iter);
			iter = iter->next;
		}
	}
	return (iter);
}

t_lst	*ft_setenv(t_lst *list, char *name, char *str)
{
	t_lst	*change;

	if ((change = find_env(list, name)))
	{
		free(change->data);
		change->data = join_three(name, "=", str);
	}
	else
	{
		change = new_lst(join_three(name, "=", str));
		to_end(&list, change);
	}
	return (list);
}
