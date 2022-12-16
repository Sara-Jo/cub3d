#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

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

int main(void)
{
	// int a = 0;
	// printf("%f\n", cos(1.047));
	// printf("%f\n", M_PI);
	// printf("%d\n", (int)1 / a);

	char *s = "  	abc\n\n  b123	\tc  ddd1 	";
	char **tmp = ft_split(s, " \t\n\v\f\r");

	for (int i = 0; i < 4; i++)
		printf("%s\n", tmp[i]);

	return (0);
}
