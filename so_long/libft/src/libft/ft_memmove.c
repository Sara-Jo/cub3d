/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:44:24 by sjo               #+#    #+#             */
/*   Updated: 2022/08/08 13:57:04 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	const unsigned char	*source;

	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (len--)
			dest[len] = source[len];
	}
	else
	{
		while (len--)
			*dest++ = *source++;
	}
	return (dst);
}
