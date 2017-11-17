/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oct_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:19:16 by satkins           #+#    #+#             */
/*   Updated: 2017/11/16 23:19:20 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

static void	get_zeros(int *zeros, int *spaces, size_t *len, t_flag arg_flag)
{
	*spaces = 0;
	*zeros = 0;
	if (arg_flag.prefix)
		*zeros = 1;
	if (arg_flag.precision_set && arg_flag.precision > (int)*len)
		*zeros = arg_flag.precision - (int)*len;
	if (arg_flag.sign)
		(*len)++;
	if (arg_flag.width_set && arg_flag.width > (int)*len + *zeros)
		*spaces = arg_flag.width - ((int)*len + *zeros);
	*len += *spaces + *zeros;
}

size_t	oct_print(unsigned long long int num, t_flag arg_flag)
{
	size_t	len;
	char	*str;
	int		zeros;
	int		spaces;

	str = ft_ullitoa_base(num, 8);
	len = ft_strlen(str);
	get_zeros(&zeros, &spaces, &len, arg_flag);
	if (arg_flag.left_allign)
	{
		while (zeros-- > 0)
			ft_putchar('0');
		ft_putstr(str);
		while (spaces-- > 0)
			ft_putchar(' ');
	}
	else
	{
		while (spaces-- > 0)
			ft_putchar(' ');
		while (zeros-- > 0)
			ft_putchar('0');
		ft_putstr(str);
	}
	return (len);
}

