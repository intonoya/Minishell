/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:10:25 by intonoya          #+#    #+#             */
/*   Updated: 2022/04/14 19:59:59 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	l;

	l = ft_strlen(s1) + 1;
	ptr = malloc(sizeof (char) * l);
	if (!ptr)
		return (0);
	ptr = ft_memcpy(ptr, s1, l);
	return (ptr);
}	
