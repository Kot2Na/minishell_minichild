/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_deletions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:58:47 by crycherd          #+#    #+#             */
/*   Updated: 2020/02/01 17:47:58 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int		miss_spaces(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

char	*del_spaces(char *str)
{
	char	*result;
	int		flag;
	int		i;
	int		j;

	result = ft_strnew(ft_strlen(str) + 1);
	flag = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		i = miss_spaces(str, i);
		while (str[i] && ((str[i] != ' ' && str[i] != '\t') || flag))
		{
			if (str[i] == '"')
				change_flag(&flag);
			ins_char_and_inc(result, &j, str[i]);
			i++;
		}
		i = miss_spaces(str, i);
		if (str[i])
			ins_char_and_inc(result, &j, ' ');
	}
	return (result);
}

void	del_double_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

char	*del_quotes(char *str)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	copy = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		while (str[i] == '"')
			i++;
		copy[j] = str[i];
		j++;
		i++;
	}
	return (copy);
}

char	*del_double_char(char *str, char c)
{
	char	*result;
	int		flag;
	int		i;
	int		j;

	result = NULL;
	if (str)
	{
		i = 0;
		j = 0;
		flag = 1;
		result = ft_strnew(ft_strlen(str) + 1);
		while (str[i])
		{
			if (str[i] != c && flag == 0)
				change_flag(&flag);
			if (str[i] != c || flag)
				ins_char_and_inc(result, &j, str[i]);
			if (str[i] == c && flag)
				change_flag(&flag);
			i++;
		}
	}
	return (result);
}
