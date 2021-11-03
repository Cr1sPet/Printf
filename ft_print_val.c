#include "libftprintf.h"
#include "libft/libft.h"

int	find_len(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int ft_putnbr_count(t_flags *flags, va_list *fa)
{
	int i;
	int	output;
	int	filler_len;
	int	output_len;

	i = 0;
	output = va_arg(*fa, int);
	output_len = find_len(output);
	filler_len = flags->width - output_len;
	while(i++ < filler_len)
		write(1, " ",1);
	ft_putnbr_fd(va_arg(*fa, int) , 1);
	return (filler_len + output_len);
}

int ft_print_value (t_flags *flags, va_list *fa)
{
	int ret_value;

	ret_value = 0;
	if (flags->specifier == 'd')
		ret_value = ft_putnbr_count(&flags, &fa);
	return (ret_value);
}