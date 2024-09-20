/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:37:47 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/20 13:50:37 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int safe_read(int *value_ptr)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    int value;

    pthread_mutex_lock(&mutex);
    value = *value_ptr;
    pthread_mutex_unlock(&mutex);

    return value;
}

void safe_write(int *value_ptr, int new_value)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mutex);
    *value_ptr = new_value;
    pthread_mutex_unlock(&mutex);
}
