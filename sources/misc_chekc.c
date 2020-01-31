/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_chekc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:51:37 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/31 19:54:55 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int		check_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int		check_parse(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] == c)
		{
			ft_putstr("minishell: parse error near '");
			ft_putchar(c);
			ft_putchar(c);
			ft_putstr("'\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int		check_path(char *str)
{
	int	i;

	if (ft_strcmp(str, ".") == 0)
		return (1);
	if (ft_strcmp(str, "..") == 0)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int		check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1] != '\0') || str[i] == '~')
			return (1);
		i++;
	}
	return (0);
}
