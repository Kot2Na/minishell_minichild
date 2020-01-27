/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 19:10:04 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/28 03:08:01 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int check_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

int find_end(char *str)
{
	int i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	return (i);
}

char *insertion(char *str, t_lst *list)
{
	char *start;
	char *end;
	char *var;
	int i;

	i = 0;
	start = str;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			str[i] = '\0';
			var = str + i + 1;
			str[i + find_end(var)] = '\0';
			end = str + i + find_end(var) + 1;
			return (join_three(start, find_var(list, var), end));
		}
		i++;
	}
	return (ft_strdup(str));
}

char *insert_var(char *str, t_lst *list)
{
	char *copy;
	char *result;

	copy = ft_strdup(str);
	while (check_str(copy))
	{
		result = insertion(copy, list);
		free(copy);
		copy = result;
	}
	return (copy);
}