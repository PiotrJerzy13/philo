/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:21:40 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/23 15:55:25 by pwojnaro         ###   ########.fr       */
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
	while (i < data->num_philo)
	{
		mutex = &data->forks[i].fork;
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
