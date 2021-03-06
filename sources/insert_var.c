/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 19:10:04 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/31 19:52:29 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	*cut_name(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	result = ft_strnew(i + 1);
	result = ft_strncpy(result, str, i);
	return (result);
}

char	*dollar_exp(char *str, int i, t_lst *list)
{
	char	*start;
	char	*var;
	char	*end;

	str[i] = '\0';
	var = cut_name(str + i + 1);
	end = str + i + ft_strlen(var) + 1;
	if (find_var(list, var))
		start = join_three(str, find_var(list, var), end);
	else
		start = join_three(str, "", end);
	free(var);
	return (start);
}

char	*tilde_exp(char *str, int i, t_lst *list)
{
	char	*end;

	str[i] = '\0';
	if (str[i + 1] != '\0')
	{
		end = str + i + 2;
		if (str[i + 1] == '+')
			return (join_three(str, find_var(list, "PWD"), end));
		if (str[i + 1] == '-')
			return (join_three(str, find_var(list, "OLDPWD"), end));
	}
	end = str + i + 1;
	return (join_three(str, find_var(list, "HOME"), end));
}

char	*insertion(char *str, t_lst *list)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
			return (dollar_exp(str, i, list));
		if (str[i] == '~')
			return (tilde_exp(str, i, list));
		i++;
	}
	return (ft_strdup(str));
}

char	*insert_var(char *str, t_lst *list)
{
	char	*result;

	result = ft_strdup(str);
	while (check_str(result))
	{
		str = result;
		result = insertion(result, list);
		free(str);
	}
	return (result);
}
