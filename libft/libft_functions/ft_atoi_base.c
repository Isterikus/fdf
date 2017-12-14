/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 21:22:42 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/09 17:42:36 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define SMALL	"0123456789abcdef"
#define BIG		"0123456789ABCDEF"

static int		ft_get_sym(char c)
{
	int		pos;

	pos = ft_stripos(SMALL, c);
	if (pos != -1)
		return (pos);
	pos = ft_stripos(BIG, c);
	return (pos);
}

unsigned int	ft_atoi_base(char *str, int base)
{
	int		ret;
	int		pl;
	int		i;

	ret = 0;
	i = 0;
	if (base < 2 || base > 16)
		return (0);
	while (str[i])
	{
		pl = ft_get_sym(str[i]);
		if (pl == -1)
			break ;
		ret += ret * (base - 1) + pl;
		i++;
	}
	return (ret);
}
