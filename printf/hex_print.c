/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:32:47 by satkins           #+#    #+#             */
/*   Updated: 2017/11/16 14:32:49 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

static void	get_zeros(int *zeros, int *spaces, size_t *len, t_flag arg_flag)
{
	*spaces = 0;
	*zeros = 0;
	if (arg_flag.precision_set && arg_flag.precision > (int)*len)
		*zeros = arg_flag.precision - (int)*len;
	if (arg_flag.prefix)
		*len += 2;
	if (arg_flag.width_set && arg_flag.width > (int)*len + *zeros)
		*spaces = arg_flag.width - ((int)*len + *zeros);
	*len += *spaces + *zeros;
}

static void	print_prefix(int caps)
{
	if (caps)
		ft_putstr("0X");
	else
		ft_putstr("0x");
}

size_t	hex_print(unsigned long long int num, t_flag arg_flag, char caps)
{
	size_t	len;
	char	*str;
	int		zeros;
	int		spaces;

	str = ft_ullitoa_base(num, 16);
	if (caps)
		ft_toupper_str(str);
	len = ft_strlen(str);
	get_zeros(&zeros, &spaces, &len, arg_flag);
	if (arg_flag.left_allign)
	{
		if (arg_flag.prefix)
			print_prefix(caps);
		while (zeros-- > 0)
			ft_putchar('0');
		ft_putstr(str);
		while (spaces-- > 0)
			ft_putchar(' ');
	}
	else
	{
		while (zeros && spaces-- > 0)
			ft_putchar('0');
		while (spaces-- > 0)
			ft_putchar(' ');
		if (arg_flag.prefix)
			print_prefix(caps);
		while (zeros-- > 0)
			ft_putchar('0');
		ft_putstr(str);
	}
	return (len);
}
