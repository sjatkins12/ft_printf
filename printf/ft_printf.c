/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:12:16 by satkins           #+#    #+#             */
/*   Updated: 2017/10/27 11:12:19 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "ft_arg_handler.h"

size_t	char_print(long long num, t_flag arg_flags)
{
	unsigned char	chr;
	size_t len;

	chr = (unsigned char)num;
	len = 1;
	if (arg_flags.left_allign)
	{
		ft_putchar(chr);
		if (arg_flags.width_set)
			while (--arg_flags.width > 0 && (len++))
				ft_putchar(' ');
	}
	else
	{
		if (arg_flags.width_set)
			while (--arg_flags.width > 0 && (len++))
				ft_putchar(' ');
			ft_putchar(chr);
	}
	return (len);
}

size_t	ft_printf(char *format, ...)
{
	size_t len;

	len = 0;
	va_list ap;
	if (format)
	{
		va_start(ap, format);
		len = formatter(&ap, format);
		va_end(ap);
	}
	return ((int)len);
}

size_t	formatter(va_list *ap, char *format)
{
	char	*next_arg;
	size_t	len;

	len = 0;
	while ((next_arg = ft_strchr(format, '%')) != '\0')
	{
		len += next_arg - format;
		ft_putnstr(format, next_arg - format);
		len += handle_arg(&format, ++next_arg, ap);
	}
	ft_putstr(format);
	len += ft_strlen(format);
	return (len);
}

size_t	handle_arg(char	**format, char *arg, va_list *ap)
{
	t_flag arg_flags;
	size_t	len;

	ft_bzero(&arg_flags, sizeof(t_flag));
	len = 0;
	if (*arg == '\0')
		handle_error();
	flag_check(&arg_flags, &arg);
	if (*arg == 'i' || *arg == 'd' || *arg == 'c' || *arg == 'D' || *arg == 'C')
		len = signed_print(ap, arg_flags, *arg);
	else if (*arg == 'u' || *arg == 'o' || *arg == 'x' ||
		*arg == 'X' || *arg == 'O' || *arg == 'U')
		len = unsigned_print(ap, arg_flags, *arg);
	else if (*arg == 's' || *arg == 'S')
		len = str_print(ap, arg_flags);
	else if (*arg == 'p')
		len = ptr_print(ap, arg_flags);
	else if (*arg == '%' && (len = 1))
		ft_putchar(*arg);
	else
		handle_error();
	*format = arg + 1;
	return (len);
}
