/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:28:47 by intonoya          #+#    #+#             */
/*   Updated: 2022/04/12 12:40:40 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	m;

	if (!b)
		return (NULL);
	m = 0;
	while (m < len)
	{
		*(unsigned char *)(b + m) = (unsigned char)c;
		m++;
	}	
	return (b);
}	
