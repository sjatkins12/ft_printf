/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:12:41 by satkins           #+#    #+#             */
/*   Updated: 2017/11/09 19:12:44 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

static char	*parse_flags(char **arg, t_flag *arg_flags)
{
	if (**arg == '#' || **arg == '0' || **arg == '+' || **arg == '-' || 
		**arg == ' ')
	{
		if (**arg == '#')
			arg_flags->prefix = 1;
		else if (**arg == '0')
			arg_flags->pad_zero = 1;
		else if (**arg == '+')
			arg_flags->sign = 1;
		else if (**arg == '-')
			arg_flags->left_allign = 1;
		else if (**arg == ' ')
			arg_flags->blank = 1;
		(*arg)++;
		if (arg_flags->left_allign == 1)
			arg_flags->pad_zero = 0;
		return (parse_flags(arg, arg_flags));
	}
	else
		return (*arg);
}

static void	parse_precision(char **arg, t_flag *arg_flags)
{
	if (**arg == '.')
	{
		++(*arg);
		if (ft_isdigit(**arg))
		{
			arg_flags->precision = ft_atoi(*arg);
			arg_flags->precision_set = 1;
			while (ft_isdigit(**arg))
				++(*arg);
		}
		else
		{
			arg_flags->precision = 0;
			arg_flags->precision_set = 1;
		}
	}
	else
		arg_flags->precision_set = 0;
}

static void	parse_length(char **arg, t_flag *arg_flags)
{
	if (**arg == 'h' && (++(*arg)))
	{
		if (**arg == 'h' && (++(*arg)))
			arg_flags->e_length = hh;
		else
			arg_flags->e_length = h;
	}
	else if (**arg == 'l' && (++(*arg)))
	{
		if (**arg == 'l' && (++(*arg)))
			arg_flags->e_length = ll;
		else
			arg_flags->e_length = l;
	}
	else if (**arg == 'z' && (++(*arg)))
		arg_flags->e_length = z;
	else if (**arg == 'j' && (++(*arg)))
		arg_flags->e_length = j;
}

static void	parse_width(char **arg, t_flag *arg_flags)
{
	arg_flags->width = ft_atoi(*arg);
	while (ft_isdigit(**arg))
	{
		++(*arg);
		arg_flags->width_set = 1;
	}
}

void		flag_check(t_flag *arg_flags, char **arg)
{
	parse_flags(arg, arg_flags);
	parse_width(arg, arg_flags);
	parse_precision(arg, arg_flags);
	parse_length(arg, arg_flags);
}
