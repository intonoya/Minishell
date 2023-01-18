/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:16:14 by intonoya          #+#    #+#             */
/*   Updated: 2022/04/12 20:23:54 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*a;
	char	*b;

	a = (char *)dst;
	b = (char *)src;
	if (dst == src)
		return (dst);
	if (src < dst)
	{
		while (len--)
			*(a + len) = *(b + len);
		return (dst);
	}
	while (len--)
	{
		*a = *b;
		a++;
		b++;
	}
	return (dst);
}	
