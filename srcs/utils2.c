/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:38:46 by sjo               #+#    #+#             */
/*   Updated: 2022/12/16 16:57:13 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

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

void	exit_with_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}
