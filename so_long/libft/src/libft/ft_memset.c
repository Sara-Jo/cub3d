/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:42:43 by sjo               #+#    #+#             */
/*   Updated: 2022/08/08 13:57:04 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*new_dest;
	unsigned char	val;
	size_t			i;

	new_dest = b;
	val = c;
	i = 0;
	while (i++ < len)
		*new_dest++ = val;
	return (b);
}
