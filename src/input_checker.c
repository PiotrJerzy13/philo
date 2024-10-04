/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:09:23 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/04 15:00:50 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
	{
		return (0);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

long	check_overflow(long number, int sign, char digit)
{
	if (number > (LONG_MAX / 10) || (number == (LONG_MAX / 10)
			&& (digit - '0') > (LONG_MAX % 10)))
	{
		if (sign == 1)
			return (LONG_MAX);
		else
			return (LONG_MIN);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (nbr * sign);
}

long	ft_atol(char *str)
{
	long	number;
	int		sign;
	long	overflow;

	number = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		overflow = check_overflow(number, sign, *str);
		if (overflow != 0)
			return (overflow);
		number = number * 10 + (*str - '0');
		str++;
	}
	return (number * sign);
}

int	check_passed_arg(int argc, char **argv)
{
	int		i;
	long	number;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
		{
			printf("Error: %d ('%s') is not a valid number.\n", i, argv[i]);
			return (1);
		}
		number = ft_atol(argv[i]);
		if (number > INT_MAX)
		{
			printf("Error: %d ('%s') above the max value.\n", i, argv[i]);
			return (1);
		}
		if (number <= 0)
		{
			printf("Error: %d ('%s') must be a positive number.\n", i, argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
