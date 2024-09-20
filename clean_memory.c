/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:56:27 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/20 18:41:21 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_memories_resources(t_memories *memories)
{
	int	i;

	if (!memories)
		return ;
	if (memories->time)
		free(memories->time);
	if (memories->forks)
	{
		i = 0;
		while (i < memories->data->num_philo)
		{
			pthread_mutex_destroy(&memories->forks[i].fork);
			i++;
		}
		free(memories->forks);
	}
	if (memories->philos)
	{
		i = 0;
		while (i < memories->data->num_philo)
			i++;
		free(memories->philos);
	}
}

void	clean_memories(t_memories *memories)
{
	if (!memories)
		return ;
	clean_memories_resources(memories);
	if (memories->data)
	{
		pthread_mutex_destroy(&memories->data->waiter);
		free(memories->data);
	}
	free(memories);
}
