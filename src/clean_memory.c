/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:56:27 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/02 15:45:51 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_memories(t_memories *memories)
{
	int	i;

	i = 0;
	if (!memories)
		return ;
	if (memories->philos && memories->forks && memories->data)
	{
		while (i < memories->data->num_philo)
		{
			pthread_mutex_destroy(&memories->philos[i].meals_count_mutex);
			pthread_mutex_destroy(&memories->forks[i].fork);
			i++;
		}
	}
	free(memories->philos);
	free(memories->forks);
	if (memories->data)
	{
		pthread_mutex_destroy(&memories->data->print_mutex);
		pthread_mutex_destroy(&memories->data->death_mutex);
		free(memories->data);
	}
	free(memories);
}

void	clean_and_exit(t_memories *memories, const char *error_message)
{
	if (error_message)
		printf("Error: %s\n", error_message);
	clean_memories(memories);
}
