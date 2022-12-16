/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:38:46 by sjo               #+#    #+#             */
/*   Updated: 2022/12/16 21:28:57 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "main.h"

void	free_str(char **str)
{
	char	**start;

	if (str)
	{
		start = str;
		while (*start)
		{
			free(*start);
			start++;
		}
		free(str);
	}
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
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}

int	access_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		perror(file);
		return (-1);
	}
	if (ft_strncmp(ft_strrchr(file, '.'), ".cub", 5) != 0)
		exit_with_error("Invalid file type\n");
	return (fd);
}
