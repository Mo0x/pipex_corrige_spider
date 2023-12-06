/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:12:59 by mgovinda          #+#    #+#             */
/*   Updated: 2023/10/21 16:33:30 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	is_neg;
	int	ret;
	int	i;

	ret = 0;
	is_neg = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			is_neg = -1;
		i++;
	}
	while ((nptr[i] > 47 && nptr[i] < 58) && nptr[i])
		ret = (ret * 10) + (nptr[i++] - '0');
	return (ret * is_neg);
}
