/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:21:40 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/28 15:11:48 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	assign_mutexes(t_data *data, t_memories *memories)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->forks[i].fork_id = i;
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
		{
			printf("Error: Mutex initialization failed at index %d.\n", i);
			clean_memories(memories);
			return (false);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		printf("Error: Print mutex initialization failed.\n");
		clean_memories(memories);
		return (false);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		printf("Error: Death mutex initialization failed.\n");
		clean_memories(memories);
		return (false);
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->philos[i].meals_count_mutex, NULL) != 0)
		{
			printf("Error: Meals count mutex failed for philosopher %d.\n", i);
			clean_memories(memories);
			return (false);
		}
		if (pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL) != 0)
		{
			printf("Error: Last meal mutex initialization failed for %d.\n", i);
			clean_memories(memories);
			return (false);
		}
		i++;
	}
	if (data->num_of_meals > 0)
	{
		data->nr_of_meals_mutex = malloc(sizeof(pthread_mutex_t));
		if (!data->nr_of_meals_mutex)
		{
			printf("Error: Failed to allocate memory for nr_of_meals_mutex.\n");
			clean_memories(memories);
			return (false);
		}
		if (pthread_mutex_init(data->nr_of_meals_mutex, NULL) != 0)
		{
			printf("Error: Number of meals mutex initialization failed.\n");
			free(data->nr_of_meals_mutex);
			data->nr_of_meals_mutex = NULL;
			clean_memories(memories);
			return (false);
		}
	}
	else
	{
		data->nr_of_meals_mutex = NULL;
	}
	return (true);
}
