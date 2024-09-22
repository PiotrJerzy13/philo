/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:09:23 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/22 12:26:45 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

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
	if (!ft_isdigit(str[i]))
	{
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
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

int	check_passed_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < MIN_ARGC || argc > MAX_ARGC)
	{
		printf("Error: Wrong number of arguments.\n");
		return (1);
	}
	while (i < argc)
	{
		if (!is_number(argv[i]))
		{
			printf("Error: %d ('%s') is not a valid number.\n", i, argv[i]);
			return (1);
		}
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error: %d ('%s') must be a positive number.\n", i, argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
