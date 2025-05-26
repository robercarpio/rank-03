/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rober <rober@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:36:25 by rober             #+#    #+#             */
/*   Updated: 2025/05/26 20:11:37 by rober            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	ft_putchr(char c)
{
	int	count;
	count = 0;
	write(1, &c, 1);
	count++;
	return (count);
}

int	ft_putstr(char *str)
{
	int		i;

	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		ft_putchr(str[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n, int base)
{
	int		count;
	char	*chars;
	int		i;

	count = 0;
	chars = "0123456789abcdef";
	i = n % base;
	if (n >= base)
		count += ft_putnbr(n / base, base);
	count = ft_putchr(chars[n % base]);
	return (count);
}

int	ft_putd(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += ft_putchr('-');
		if (n == -2147483648)
		{
			count += ft_putstr("2147483648");
			return (count);
		}
		n = -n;
	}
	count += ft_putnbr(n, 10);
	return (count);
}

int	ft_printf(char *str, ...)
{
	int		count;
	va_list	args;	
	int		i;

	count = 0;
	va_start(args, str);
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == 'd')
				count += ft_putd(va_arg(args, int));
			else if (str[i + 1] == 'x')
				count += ft_putnbr(va_arg(args, int), 16);
			else if (str[i + 1] == 's')
				count += ft_putstr(va_arg(args, char *));
			i++;
		}
		else
			count = ft_putchr(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int	main(void)
{
	ft_printf("Hello %s\n", "toto");
	ft_printf("Magic %s is %d \n", "number", 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	return (0);
}
