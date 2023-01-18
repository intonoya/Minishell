/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:49:15 by intonoya          #+#    #+#             */
/*   Updated: 2022/04/15 12:57:22 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*dst;
	unsigned int	l;

	l = ft_strlen(s);
	if (start > l || len == 0)
		i = 0;
	else if (l < start + len)
		i = l - start;
	else
		i = len;
	dst = (char *) malloc(i + 1);
	if (!dst)
		return (0);
	l = 0;
	while (s[start] && l < i)
		dst[l++] = s[start++];
	dst[l] = '\0';
	return (dst);
}
