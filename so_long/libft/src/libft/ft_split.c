/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:05:29 by sjo               #+#    #+#             */
/*   Updated: 2022/12/15 17:17:14 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

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

int	ft_wordcount(char const *s, char *deli)
{
	int	count;
	int	i;
	int j;

	count = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		while (deli[j])
		{
			if (s[i] == deli[j])
				break;
			j++;
		}
		if (j == ft_strlen(deli))
			count++;
		i++;
	}
	return (count);
}

char	*ft_firstword(const char *s, char *deli)
{
	size_t	len;
	int 	i;
	char	*ptr;

	len = 0;
	i = 0;
	while (s[len])
	{
		while (deli[i])
		{
			if (s[len] == deli[i])
				len++;
				break;
		}
		if (i == ft_strlen(deli))
			break;
	}
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

char	**ft_inside_split(char const *s, char *deli, int nbr_of_words)
{
	int		i;
	int		j;
	int		k;
	char	**ptr;

	i = 0;
	j = 0;
	k = 0;
	ptr = (char **)ft_calloc(nbr_of_words + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < nbr_of_words && s[j])
	{
		while (deli[k])
		{
			if (s[j] == deli[k])
				break;
			k++;
		}
		if (k == ft_strlen(deli))
		{
			ptr[i] = ft_firstword(&s[j], deli);
			if (!ptr[i++])
				return (ft_freeall(ptr));
			j += ft_strlen(ptr[i]);
		}
		else
			j++;
	}
	return (ptr);
}

char	**ft_split(char const *s, char *deli)
{
	int	nbr_of_words;

	if (!s)
		return (NULL);
	nbr_of_words = ft_wordcount(s, deli);
	return (ft_inside_split(s, deli, nbr_of_words));
}
