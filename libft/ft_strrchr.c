/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:44:33 by iren              #+#    #+#             */
/*   Updated: 2021/06/01 23:36:13 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = 0;
	while (*s++)
	{
		if (c == *(s - 1))
			res = (char *)(s - 1);
	}
	if (c == '\0')
		return ((char *)(s - 1));
	return ((char *)res);
}
