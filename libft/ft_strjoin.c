/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:06:11 by intonoya          #+#    #+#             */
/*   Updated: 2022/04/15 09:17:10 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	a;
	size_t	b;
	size_t	i;
	size_t	j;
	char	*s;

	i = 0;
	j = 0;
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	s = malloc(sizeof (char) * (a + b + 1));
	while (j < a)
		s[i++] = s1[j++];
	j = 0;
	while (j < b)
		s[i++] = s2[j++];
	s[i] = '\0';
	return (s);
}	
