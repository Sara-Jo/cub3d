/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:43:17 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 15:17:02 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static char	*gnl(int fd, int depth)
{
	char	*line;
	char	c;
	int		byte;

	c = 0;
	line = NULL;
	byte = read(fd, &c, 1);
	if (byte < 0 || (byte == 0 && depth == 0))
		return (NULL);
	if (c == '\n' || byte == 0)
		line = malloc(depth + 2);
	else
		line = gnl(fd, depth + 1);
	if (line)
	{
		line[depth] = c;
		line[depth + 1] = line[depth + 1] * (c != '\n');
	}
	return (line);
}

char	*get_next_line(int fd)
{
	return (gnl(fd, 0));
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	free_str(char **str)
{
	char	**start;

	start = str;
	while (*start)
	{
		free(*start);
		start++;
	}
	free(str);
}

char	*ft_strndup(const char *s1, int n)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * (n + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1, n + 1);
	return (dst);
}

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
	while (s[i])
	{
		j = 0;
		while (deli[j])
		{
			if (s[i] == deli[j])
			{
				i++;
				break;
			}
			j++;
		}
		if (j == (int)ft_strlen(deli))
		{
			count++;
			while (s[i])
			{
				j = 0;
				while (deli[j])
				{
					if (s[i] == deli[j])
						break;
					j++;
				}
				if (j != (int)ft_strlen(deli))
					break;			
				i++;
			}
		}
	}
	return (count);
}

char	*ft_firstword(const char *s, char *deli)
{
	size_t	len;
	int 	i;
	char	*ptr;

	len = 0;
	while (s[len])
	{
		i = 0;
		while (deli[i])
		{
			if (s[len] == deli[i])
				break;
			i++;
		}
		if (i == (int)ft_strlen(deli))
			len++;
		else
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
	ptr = (char **)ft_calloc(nbr_of_words + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < nbr_of_words && s[j])
	{
		k = 0;
		while (deli[k])
		{
			if (s[j] == deli[k])
				break;
			k++;
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

char 	**ft_split_str(char const *s, char *deli)
{
	int	nbr_of_words;

	if (!s)
		return (NULL);
	nbr_of_words = ft_wordcount(s, deli);
	return (ft_inside_split(s, deli, nbr_of_words));
}

void exit_with_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}
