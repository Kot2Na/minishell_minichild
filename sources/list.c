/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:10:10 by crycherd          #+#    #+#             */
/*   Updated: 2019/08/09 20:29:28 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_lst	*new_lst(char *content)
{
	t_lst	*new;
	int		size;

	size = ft_strlen(content);
	if ((new = (t_lst *)malloc(sizeof(t_lst))))
	{
		if (content)
		{
			if ((new->data = malloc(size + 1)))
			{
				new->data = ft_memcpy(new->data, content, size + 1);
			}
			else
			{
				free(new);
				return (NULL);
			}
		}
		else
		{
			new->data = NULL;
		}
		new->next = NULL;
	}
	return (new);
}

void	to_end(t_lst **head, t_lst *new)
{
	t_lst *start;

	if (head)
	{
		start = *head;
		if (start)
		{
			while (start->next)
				start = start->next;
			start->next = new;
		}
		else
		{
			*head = new;
		}
	}
}

void	lst_del(t_lst *head)
{
	if (head)
	{
		lst_del(head->next);
		free(head->data);
		free(head);
	}
}

char	*find_var(t_lst *head, char *find)
{
	char *result;
	int	size;

	result = NULL;
	size = ft_strlen(find);
	while (head)
	{
		if (ft_strncmp(find, head->data, size) == 0)
		{
			result = head->data + size + 1;
			break ;
		}
		head = head->next;
	}
	return (result);
}

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
