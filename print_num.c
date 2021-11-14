#include "ft_printf.h"
#include "libft/libft.h"

int	my_putstr_fd(t_flags *flags, t_output *output)
{
	int	ok;

	ok = 0;
	if (!output->val)
		return (ok);
	if (flags->dot && !flags->precision && !('p' == flags->specifier))
	{
		if (!ft_strncmp(output->val, "0", output->len))
		{
			ok = 1;
			if (flags->null_filler)
				write(1, &" ", 1);
		}
	}
	if (!ok)
		write(1, output->val, output->len);
	return (ok);
}

t_output init_output(char *str)
{
	t_output output;
	output.val = str;
	output.neg = ('-' == str[0]);
	output.len = ft_strlen(str) - output.neg;
	return (output);
}

void point_print(int len, char out)
{
	int	i;

	i = 0;
	while(i < len)
	{
		write(1, &out, 1);
		i++;
	}
}

void print_null_filler(t_flags *flags,t_output *output, int number_out_spaces)
{
	if (output->neg)
	{
		output->val++;
		ft_putchar_fd('-', 1);
	}
	point_print(number_out_spaces, '0');
	if (flags->hash || 'p' == flags->specifier)
	{
		if('X' == flags->specifier)
			ft_putstr_fd("0X", 1);
		else
			ft_putstr_fd("0x", 1);
	}
	// ft_putstr_fd(output->val, 1);
	my_putstr_fd(flags, output);
}

void print_flag_width(t_flags *flags, t_output *output, int number_out_nulls, int number_out_spaces)
{
	if (flags->minus)
	{
		if (output->neg)
		{
			output->val++;
			ft_putchar_fd('-', 1);
		}
		if (flags->hash || 'p' == flags->specifier)
		{
			number_out_spaces -= 2;
			if('X' == flags->specifier)
				ft_putstr_fd("0X", 1);
			else
				ft_putstr_fd("0x", 1);
		}
		point_print(number_out_nulls, '0');
		// ft_putstr_fd(output->val, 1);
		if (my_putstr_fd(flags, output))
			number_out_spaces++;
		point_print(number_out_spaces, ' ');
	}
	else
	{
		if (flags->hash || 'p' == flags->specifier)
			number_out_spaces -= 2;
		if (flags->null_filler && flags->width && !flags->dot)
			print_null_filler (flags, output, number_out_spaces);
		else
		{
			point_print(number_out_spaces, ' ');
			if (output->neg)
			{
				output->val++;
				ft_putchar_fd('-', 1);
			}
			else if (flags->plus)
			{
				ft_putchar_fd('+', 1);
			}
			else if (flags->space)
			{
				ft_putchar_fd(' ', 1);
			}
			point_print(number_out_nulls, '0');
			if (flags->hash || 'p' == flags->specifier)
			{
				if('X' == flags->specifier)
					ft_putstr_fd("0X", 1);
				else
					ft_putstr_fd("0x", 1);
			}
			// ft_putstr_fd(output->val, 1);
			my_putstr_fd(flags, output);
		}
	}
}

int	print_width(t_flags *flags, t_output *output, int biggest_prec_or_output_len)
{
	int	number_out_nulls;
	int	number_out_spaces;
	int write_count;

	write_count = 0;
	if (flags->hash || 'p' == flags->specifier)
		write_count += 2;
	number_out_nulls = 0;
	if (output->len + output->neg + write_count >= flags->width)
	{
		if (flags->hash || 'p' == flags->specifier)
		{
			if ('X' == flags->specifier)
				ft_putstr_fd("0X", 1);
			else
				ft_putstr_fd("0x", 1);
		}
		// ft_putstr_fd(output->val, 1);
		if (output->neg)
		{
			output->val++;
			ft_putchar_fd('-', 1);
		}
		my_putstr_fd(flags, output);
		return (write_count + output->len + output->neg);
	}
	else
	{
		if (flags->precision > output->len)
			number_out_nulls = flags->precision - output->len;
		number_out_spaces = flags->width - biggest_prec_or_output_len;
		print_flag_width(flags, output, number_out_nulls, number_out_spaces);
		return (flags->width);
	}
}

int ft_putnbr_count(t_flags *flags, t_output *output)
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
		if (output->neg)
		{
			output->val++;
			ft_putchar_fd('-', 1);
		}
		else if (flags->plus)
		{
			biggest_prec_or_output_len +=1;
			ft_putchar_fd('+', 1);
		}
		else if (flags->space)
		{
			biggest_prec_or_output_len +=1;
			ft_putchar_fd(' ', 1);
		}
		point_print(flags->precision - output->len, '0');
		if (flags->hash || 'p' == flags->specifier)
		{
			write_count += 2;
			if ('X' == flags->specifier)
				ft_putstr_fd("0X", 1);
			else
				ft_putstr_fd("0x", 1);
		}
		// ft_putstr_fd(output->val, 1);
		write_count -= my_putstr_fd(flags, output);
		write_count += biggest_prec_or_output_len;
	}
	else
		write_count = print_width(flags, output, biggest_prec_or_output_len);
	return (write_count);
}

void	ft_put_prec_str_fd(char *s, int number,int fd)
{
	if (!s)
		return ;
	write(fd, s, number);
}



static int	find_length(unsigned long long int n, unsigned long long base)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

static void	ft_strrev(char *str, int is_neg)

{
	int		i;
	int		k;
	int		j;
	char	t;

	j = ft_strlen(str) - 1;
	k = j / 2;
	i = is_neg;
	while (i <= k)
	{
		t = str[j];
		str[j] = str[i];
		str[i] = t;
		i++;
		j--;
	}
}
char	*ft_utoa(unsigned int n)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = (1 + find_length(n, 10)) * sizeof(char);
	res = (char *) malloc (len);
	if ((void *)0 == res)
		return ((void *)0);
	while (i < len - 1)
	{
		res[i] = (n % 10) + 48;
		n /= 10;
		i++;
	}
	res[i] = 0;
	ft_strrev(res, 0);
	return (res);
}

char *convert_base(unsigned long long int out, int base, int ok)
{
	int		i;
	int		abc_shift;
	int		length;
	char	*num_str;

	i = 0;
	length = find_length (out, base);
	num_str = (char *)malloc(sizeof(char) * (length + 1));
	if (NULL == num_str)
		return (NULL);
	if (ok)
			abc_shift = 'A';
		else
			abc_shift = 'a';
	while(i < length)
	{
		if (out % base > 9)
			num_str[i] = (out % base) - 10 + abc_shift;
		else
			num_str[i] = (out % base) + '0';
		out /= base;
		i++;
	}
	num_str[i] = 0;
	ft_strrev(num_str, 0);
	return (num_str);
}

int ft_print_value (t_flags *flags, va_list fa)
{
	int		ret_value;
	ret_value = 0;
	if ('d' == flags->specifier || 'i' == flags->specifier || 'u' == flags->specifier)
	{
		char		*output_str;
		t_output	output;
	
		if ('u' == flags->specifier)
			output_str = ft_utoa(va_arg(fa, unsigned int));
		else
			output_str = ft_itoa(va_arg(fa, int));
		if (!output_str)
				return (0);
		output = init_output(output_str);
		ret_value = ft_putnbr_count(flags, &output);
		free (output_str);
	}
	if ('c' == flags->specifier)
	{
		if (flags->minus)
		{
			ft_putchar_fd (va_arg(fa, int), 1);
			point_print (flags->width - 1, ' ');
		}
		else
		{
			point_print (flags->width - 1, ' ');
			ft_putchar_fd (va_arg(fa, int), 1);
		}
		if (flags->width)
			return (flags->width);
		else
			return (1);
	}
	if ('s' == flags->specifier)
	{
		char	*output;
		int		strlen;
		int		number_out_len;

		output = va_arg(fa, char *);
		if (NULL == output)
			output = "(null)";
		strlen = ft_strlen(output);
		if (flags->dot && !flags->precision)
			return (0);
		if (flags->precision &&flags->precision < strlen)
			number_out_len = flags->precision;
		else 
			number_out_len = strlen;
		if (flags->minus)
		{
			ft_put_prec_str_fd(output, number_out_len, 1);
			point_print(flags->width - number_out_len, ' ');
		}
		else
		{
			point_print(flags->width - number_out_len, ' ');
			ft_put_prec_str_fd(output, number_out_len, 1);
		}
		if (flags->width > number_out_len)
			return (flags->width);
		else
			return (number_out_len);
	}
	if ('x' == flags->specifier || 'X' == flags->specifier)
	{
		unsigned int	num;
		t_output		output;
		char			*num_str;

		num = va_arg(fa, unsigned int);
		num_str =  convert_base(num, 16, 'X' == flags->specifier);
		if (NULL == num_str)
			return (0);
		output = init_output(num_str);
		if (0 == num)
			flags->hash = 0;
		ret_value += ft_putnbr_count(flags, &output);
		free(num_str);
	}
	if ('p' == flags ->specifier)
	{
		unsigned long long		num;
		char					*num_str;
		t_output				output;
		num = va_arg(fa, unsigned long long);
		num_str =  convert_base(num, 16, 0);
		if (NULL == num_str)
			return (0);
		output = init_output(num_str);
		ret_value += ft_putnbr_count(flags, &output);
		free (num_str);
	}
	if ('%' == flags->specifier)
	{
		ft_putchar_fd ('%', 1);
		ret_value = 1;
	}
	return (ret_value);
}