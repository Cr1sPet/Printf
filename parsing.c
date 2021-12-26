/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:24:00 by jchopped          #+#    #+#             */
/*   Updated: 2021/11/16 16:48:07 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_isspecifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%');
}

static void	check_flags(t_flags *flags, const char *f, int *i)
{
	while (f[*i])
	{
		if ('#' == f[*i])
			flags->hash = 1;
		else if ('+' == f[*i])
			flags->plus = 1;
		else if (' ' == f[*i])
			flags->space = 1;
		else if ('-' == f[*i])
			flags->minus = 1;
		else if ('0' == f[*i])
			flags->null_filler = 1;
		else
			break ;
		(*i)++;
	}
}

int	parsing(t_flags *flags, const char *f, int *i)
{
	check_flags(flags, f, i);
	while (ft_isdigit(f[*i]))
		flags->width = (flags->width * 10) + (f[(*i)++] - 48);
	if ('.' == f[*i])
	{
		flags->dot = 1;
		(*i)++;
	}
	while (ft_isdigit(f[*i]))
		flags->precision = (flags->precision * 10) + (f[(*i)++] - 48);
	if (ft_isspecifier(f[*i]))
	{
		flags->specifier = f[*i];
		return (1);
	}
	return (0);
}
