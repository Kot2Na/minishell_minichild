/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:23:03 by crycherd          #+#    #+#             */
/*   Updated: 2019/04/12 19:45:10 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strequ(const char *s1, const char *s2)
{
	int result;

	result = 0;
	if (s1 && s2)
	{
		while (*s1 == *s2 && *s1 && *s2)
		{
			s1++;
			s2++;
		}
		if (*s1 == *s2)
			result = 1;
	}
	return (result);
}
