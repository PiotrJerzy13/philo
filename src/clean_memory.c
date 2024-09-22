/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:56:27 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/22 13:17:54 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_memories_resources(t_memories *memories)
{
	int	i;

	if (!memories)
		return ;
	if (memories->time)
	{
		free(memories->time);
		memories->time = NULL;
	}
	if (memories->forks)
	{
		i = 0;
		while (i < memories->data->num_philo)
		{
			pthread_mutex_destroy(&memories->forks[i].fork);
			i++;
		}
		free(memories->forks);
		memories->forks = NULL;
	}
	if (memories->philos)
	{
		i = 0;
		while (i < memories->data->num_philo)
		{
			pthread_mutex_destroy(&memories->philos[i].meals_count_mutex);
			i++;
		}
		free(memories->philos);
		memories->philos = NULL;
	}
}

void	clean_memories(t_memories *memories)
{
	if (!memories)
		return ;
	if (memories->time)
	{
		free(memories->time);
		memories->time = NULL;
	}
	if (memories->forks)
	{
		free(memories->forks);
		memories->forks = NULL;
	}
	if (memories->philos)
	{
		free(memories->philos);
		memories->philos = NULL;
	}
	if (memories->data)
	{
		pthread_mutex_destroy(&memories->data->waiter);
		free(memories->data);
		memories->data = NULL;
	}
	free(memories);
}
