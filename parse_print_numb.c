/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_print_numb.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:23:50 by jchopped          #+#    #+#             */
/*   Updated: 2021/11/16 12:32:19 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_null_filler(t_flags *flags, t_output *output, int spces)
{
	check_neg(output);
	point_print(spces, '0');
	check_hash_pointer(flags);
	putstr_check_case(flags, output);
}

static void	print_flag_wd(t_flags *flags, t_output *output, int nlls, int spces)
{
	if (flags->minus)
	{
		check_neg(output);
		spces -= check_hash_pointer(flags);
		point_print(nlls, '0');
		spces += putstr_check_case(flags, output);
		point_print(spces, ' ');
	}
	else
	{
		if (flags->hash || 'p' == flags->specifier)
			spces -= 2;
		if (flags->null_filler && flags->width && !flags->dot)
			print_null_filler (flags, output, spces);
		else
		{
			point_print(spces, ' ');
			check_plus_minus(flags, output);
			point_print(nlls, '0');
			check_hash_pointer(flags);
			putstr_check_case(flags, output);
		}
	}
}

static int	print_width(t_flags *flags, t_output *output, int biggest_prec_len)
{
	int	number_out_nulls;
	int	number_out_spaces;
	int	write_count;

	write_count = 0;
	number_out_nulls = 0;
	if (flags->hash || 'p' == flags->specifier)
		write_count = 2;
	if (output->len + output->neg + write_count >= flags->width)
	{
		check_hash_pointer(flags);
		check_neg(output);
		putstr_check_case(flags, output);
		return (write_count + output->len + output->neg);
	}
	else
	{
		if (flags->precision > output->len)
			number_out_nulls = flags->precision - output->len;
		number_out_spaces = flags->width - biggest_prec_len;
		print_flag_wd(flags, output, number_out_nulls, number_out_spaces);
		return (flags->width);
	}
}

static int	putnbr_count(t_flags *flags, t_output *output)
{
	int	write_count;
	int	biggest_prec_or_output_len;

	write_count = 0;
	if (flags->precision > output->len)
		biggest_prec_or_output_len = flags->precision + output->neg;
	else
		biggest_prec_or_output_len = output->len + output->neg;
	if (flags->precision >= flags->width)
	{
		write_count += check_plus_minus(flags, output);
		point_print(flags->precision - output->len, '0');
		write_count += check_hash_pointer(flags);
		write_count -= putstr_check_case(flags, output);
		write_count += biggest_prec_or_output_len;
	}
	else
		write_count = print_width(flags, output, biggest_prec_or_output_len);
	return (write_count);
}

int	parse_print_numb(t_flags *flags, va_list fa, char *out_str, int ret)
{
	char		s;
	t_output	output;

	s = flags->specifier;
	if ('u' == flags->specifier)
		out_str = ft_utoa(va_arg(fa, unsigned int));
	else if ('i' == flags->specifier || 'd' == flags->specifier)
		out_str = ft_itoa(va_arg(fa, int));
	else if ('p' == flags->specifier)
		out_str = convert_base(va_arg(fa, unsigned long long), 16, 'p', 'a');
	else if ('x' == flags->specifier || 'X' == flags->specifier)
	{
		out_str = convert_base(va_arg(fa, unsigned int), 16, s, 'a');
		if (!out_str)
			return (0);
		if (!ft_strncmp(out_str, "0", ft_strlen(out_str)))
			flags->hash = 0;
	}
	if (!out_str)
		return (0);
	output = init_output(out_str);
	ret = putnbr_count(flags, &output);
	free (out_str);
	return (ret);
}
