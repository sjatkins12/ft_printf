/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:12:19 by satkins           #+#    #+#             */
/*   Updated: 2017/11/09 19:12:23 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

size_t						print_pres(char *str, t_flag arg_flag)
{
	size_t					len;

	len = ft_strlen(str);
	if (arg_flag.precision_set && arg_flag.precision < (int)len)
		len = arg_flag.precision;
	ft_putnstr(str, len);
	return (len);
}

size_t						print_width(char *str, t_flag arg_flag)
{
	size_t					len;
	int						print_len;

	len = ft_strlen(str);
	print_len = 0;
	if (arg_flag.precision_set && arg_flag.precision < (int)len)
	{
		if (arg_flag.width_set)
			print_len = arg_flag.width - arg_flag.precision;
	}
	else if (arg_flag.width_set)
		print_len = arg_flag.width - len;
	len = 0;
	while (--print_len >= 0)
	{
		ft_putchar(' ');
		len++;
	}
	return (len);
}

size_t						str_print(va_list *ap, t_flag arg_flag)
{
	char					*str;
	size_t					len;

	str = va_arg(*ap, char*);
	if (str == NULL)
		str = "(null)";
	if (arg_flag.left_allign)
	{
		len = print_pres(str, arg_flag);
		len += print_width(str, arg_flag);
	}
	else
	{
		len = print_width(str, arg_flag);
		len += print_pres(str, arg_flag);
	}
	return (len);
}

static void					print_prefix_str(char *str)
{
	ft_putstr("0x");
	ft_putstr(str);
}

size_t						ptr_print(va_list *ap, t_flag arg_flag)
{
	unsigned long long int	ptr;
	char					*str;
	size_t					len;
	int						i;

	ptr = (unsigned long long int)va_arg(*ap, void *);
	str = ft_ullitoa_base(ptr, 16);
	len = ft_strlen(str) + 2;
	if (arg_flag.width_set && arg_flag.width > (int)len && (i = -1))
	{
		if (arg_flag.left_allign)
		{
			print_prefix_str(str);
			while (++i < arg_flag.width - (int)len)
				ft_putchar(' ');
			return (arg_flag.width);
		}
		while (++i < arg_flag.width - (int)len)
			ft_putchar(' ');
		print_prefix_str(str);
		return (arg_flag.width);
	}
	print_prefix_str(str);
	return (len);
}
