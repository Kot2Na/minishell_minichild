/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 01:12:50 by crycherd          #+#    #+#             */
/*   Updated: 2020/02/01 02:02:14 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	*g_com_names[] = {
	"echo",
	"env",
	"cd",
	"setenv",
	"unsetenv",
	"exit",
	NULL
};

char	**completion(const char *text, int start, int end)
{
	(void)start;
	(void)end;
	rl_attempted_completion_over = 1;
	return (rl_completion_matches(text, generator));
}

char	*generator(const char *text, int state)
{
	static int	list_index;
	static int	len;
	char		*name;

	if (!state)
	{
		list_index = 0;
		len = strlen(text);
	}
	while ((name = g_com_names[list_index++]))
	{
		if (ft_strncmp(name, text, len) == 0)
		{
			return (ft_strdup(name));
		}
	}
	return (NULL);
}
