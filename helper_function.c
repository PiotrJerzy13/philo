/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:37:47 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/20 17:49:48 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_read(int *value_ptr)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	int						value;

	pthread_mutex_lock(&mutex);
	value = *value_ptr;
	pthread_mutex_unlock(&mutex);
	return (value);
}

void	safe_write(int *value_ptr, int new_value)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	*value_ptr = new_value;
	pthread_mutex_unlock(&mutex);
}
