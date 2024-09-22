/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:21:40 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/22 20:30:26 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	assign_mutexes(t_data *data, t_memories *memories)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = 0;
	if (!data->forks)
	{
		printf("Error: Forks array is NULL.\n");
		return (false);
	}
	while (i <= data->num_philo)
	{
		if (i == data->num_philo)
		{
			mutex = &(data->waiter);
		}
		else
		{
			if (!data->forks || i >= data->num_philo)
			{
				printf("Error: Forks array is NULL or index out of bounds.\n");
				clean_memories(memories);
				return (false);
			}
			mutex = &data->forks[i].fork;
		}
		if (pthread_mutex_init(mutex, NULL) != 0)
		{
			printf("Error: Mutex initialization failed at index %d.\n", i);
			clean_memories(memories);
			return (false);
		}
		i++;
	}
	return (true);
}

void	assign_mutex(pthread_mutex_t *mutex, const char *operation)
{
	if (mutex == NULL)
	{
		printf("Error: Mutex pointer is NULL.\n");
		return ;
	}
	if (strcmp(operation, "init") == 0)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
		{
			printf("Error: Mutex initialization failed.\n");
		}
	}
	else if (strcmp(operation, "destroy") == 0)
	{
		if (pthread_mutex_destroy(mutex) != 0)
		{
			printf("Error: Mutex destruction failed.\n");
		}
	}
	else if (strcmp(operation, "lock") == 0)
	{
		if (pthread_mutex_lock(mutex) != 0)
		{
			printf("Error: Mutex lock failed.\n");
		}
	}
	else if (strcmp(operation, "unlock") == 0)
	{
		if (pthread_mutex_unlock(mutex) != 0)
		{
			printf("Error: Mutex unlock failed.\n");
		}
	}
	else
	{
		printf("Error: Unknown mutex operation '%s'.\n", operation);
	}
}
