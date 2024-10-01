/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:56:27 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/01 20:05:05 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_memories(t_memories *memories)
{
	int	num_philo;
	int	i;

	if (!memories)
		return ;
	if (memories->data != NULL)
		num_philo = memories->data->num_philo;
	else
		num_philo = 0;
	if (memories->philos && memories->forks)
	{
		i = 0;
		while (i < num_philo)
		{
			pthread_mutex_destroy(&memories->philos[i].meals_count_mutex);
			pthread_mutex_destroy(&memories->forks[i].fork);
			i++;
		}
		free(memories->philos);
		memories->philos = NULL;
		free(memories->forks);
		memories->forks = NULL;
	}
	if (memories->data)
	{
		pthread_mutex_destroy(&memories->data->print_mutex);
		pthread_mutex_destroy(&memories->data->death_mutex);
		free(memories->data);
		memories->data = NULL;
	}
	free(memories);
}

void	clean_and_exit(t_memories *memories, const char *error_message)
{
	if (error_message)
		printf("Error: %s\n", error_message);
	clean_memories(memories);
}
