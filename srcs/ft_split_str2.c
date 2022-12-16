/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:57:58 by sjo               #+#    #+#             */
/*   Updated: 2022/12/16 17:00:31 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "main.h"

char	**ft_freeall(char **s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

int	is_delimiter(char c, char *deli)
{
	int	i;

	i = 0;
	while (deli[i])
	{
		if (c == deli[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_wordcount(char const *s, char *deli)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (is_delimiter(s[i], deli))
			i++;
		else
		{
			count++;
			while (s[i] && !is_delimiter(s[i], deli))
				i++;
		}
	}
	return (count);
}
