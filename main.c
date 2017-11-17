/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:36:21 by satkins           #+#    #+#             */
/*   Updated: 2017/11/09 19:36:25 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

#include <stdio.h>

int	main(void)
{
	size_t len;
	char num = '\0';

	len = ft_printf("%10c\n", num);
	printf("%10c\n", num);
	ft_printf("%zu\n", len);
}
