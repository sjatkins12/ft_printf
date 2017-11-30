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

static size_t		print_pres(char *str, t_flag arg_flag)
{
	size_t	len;

	len = ft_strlen(str);
	if (arg_flag.precision_set && arg_flag.precision < (int)len)
		len = arg_flag.precision;
	ft_putnstr(str, len);
	return (len);
}

static size_t		print_width(char *str, t_flag arg_flag)
{
	size_t	len;
	int		print_len;

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
		if (arg_flag.pad_zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		len++;
	}
	return (len);
}

size_t		str_format(char *str, t_flag arg_flag)
{
	size_t	len;

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

size_t		str_print(va_list *ap, t_flag arg_flag)
{
	char	*str;

	str = va_arg(*ap, char*);
	if (str == NULL)
		str = "(null)";
	return (str_format(str, arg_flag));
}

static size_t	ft_wstrlen(wchar_t *str, int precision_set, int precision)
{
	size_t	len;

	len = 0;
	while (*str != '\0' && (!precision_set || precision != 0))
	{
		if (*str <= 0x7F && (++len))
			precision--;
		else if (*str <= 0x7FF &&
			(!precision_set || precision >= 2))
		{
			precision -= 2;
			len += 2;
		}
		else if (*str <= 0xFFFF &&
			(!precision_set || precision >= 3))
		{
			precision -= 3;
			len += 3;
		}
		else if (*str <= 0x10FFFF &&
			(!precision_set || precision >= 4))
		{
			precision -= 4;
			len += 4;
		}
		else
			return (len);
		str++;
	}
	return (len);
}

static void			ft_putnwstr(wchar_t *str, size_t len)
{
	while (*str != '\0' && len-- > 0)
	{
		if (*str <= 0x7F)
			ft_putchar(*str);
		else if (*str <= 0x7FF)
		{
			ft_putchar((*str >> 6) + 0xC0);
			ft_putchar((*str & 0x3F) + 0x80);
		}
		else if (*str <= 0xFFFF)
		{
			ft_putchar((*str >> 12) + 0xE0);
			ft_putchar(((*str >> 6) & 0x3F) + 0x80);
			ft_putchar((*str & 0x3F) + 0x80);
		}
		else if (*str <= 0x10FFFF)
		{
			ft_putchar((*str >> 18) + 0xF0);
			ft_putchar(((*str >> 12) & 0x3F) + 0x80);
			ft_putchar(((*str >> 6) & 0x3F) + 0x80);
			ft_putchar((*str & 0x3F) + 0x80);
		}
		str++;
	}
}

static size_t		print_wpres(wchar_t *str, t_flag arg_flag)
{
	size_t	len;

	len = ft_wstrlen(str, arg_flag.precision_set, arg_flag.precision);
	if (arg_flag.precision_set && arg_flag.precision < (int)len)
		len = arg_flag.precision;
	ft_putnwstr(str, len);
	return (len);
}

static size_t		print_wwidth(wchar_t *str, t_flag arg_flag)
{
	size_t	len;
	int		print_len;

	len = ft_wstrlen(str, arg_flag.precision_set, arg_flag.precision);
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
		if (arg_flag.pad_zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		len++;
	}
	return (len);
}



size_t		wstr_print(va_list *ap, t_flag arg_flag)
{
	wchar_t	*str;
	size_t	len;

	str = va_arg(*ap, wchar_t*);
	if (str == NULL)
		return (str_format("(null)", arg_flag));
	if (arg_flag.left_allign)
	{
		len = print_wpres(str, arg_flag);
		len += print_wwidth(str, arg_flag);
	}
	else
	{
		len = print_wwidth(str, arg_flag);
		len += print_wpres(str, arg_flag);
	}
	return (len);
}