/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:33:45 by sjo               #+#    #+#             */
/*   Updated: 2022/12/16 17:01:02 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "main.h"

char	*ft_firstword(const char *s, char *deli)
{
	size_t	len;
	int		i;
	char	*ptr;

	len = 0;
	while (s[len])
	{
		i = 0;
		while (deli[i])
		{
			if (s[len] == deli[i])
				break ;
			i++;
		}
		if (i == (int)ft_strlen(deli))
			len++;
		else
			break ;
	}
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

char	**check_firstword(char const *s, char *deli, int nbr_of_words,
						char **ptr)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < nbr_of_words && s[j])
	{
		k = 0;
		while (deli[k])
		{
			if (s[j] == deli[k++])
				break ;
		}
		if (k == (int)ft_strlen(deli))
		{
			ptr[i] = ft_firstword(&s[j], deli);
			j += ft_strlen(ptr[i]);
			if (!ptr[i++])
				return (ft_freeall(ptr));
		}
		else
			j++;
	}
	return (ptr);
}

char	**ft_inside_split(char const *s, char *deli, int nbr_of_words)
{
	char	**ptr;

	ptr = (char **)ft_calloc(nbr_of_words + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	return (check_firstword(s, deli, nbr_of_words, ptr));
}

char	**ft_split_str(char const *s, char *deli)
{
	int	nbr_of_words;

	if (!s)
		return (NULL);
	nbr_of_words = ft_wordcount(s, deli);
	return (ft_inside_split(s, deli, nbr_of_words));
}
