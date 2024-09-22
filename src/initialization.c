/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:36:48 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/22 21:49:05 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*allocate(void **ptr, size_t size, t_memories *memories)
{
	*ptr = calloc(1, size);
	if (!*ptr)
	{
		printf("Error: Memory allocation failed.\n");
		free(memories);
	}
	return (*ptr);
}

void	set_eating_limits(int argc, char **argv, t_data *data)
{
	if (argc == MAX_ARGC)
		data->num_of_meals = ft_atoi(argv[5]);
	else
		data->num_of_meals = -1;
}

t_data	*init_data(int argc, char **argv)
{
	t_memories	*memories;
	t_data		*data;

	memories = calloc(1, sizeof(t_memories));
	data = NULL;
	if (!memories)
	{
		printf("Error: Failed to allocate memory for memories.\n");
		return (NULL);
	}
	memories->data = calloc(1, sizeof(t_data));
	if (!memories->data)
	{
		printf("Error: Failed to allocate memory for data.\n");
		clean_memories(memories);
		return (NULL);
	}
	data = memories->data;
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	printf("Number of philosophers: %d\n", data->num_philo);
	printf("Time to die: %d\n", data->time_to_die);
	printf("Time to eat: %d\n", data->time_to_eat);
	printf("Time to sleep: %d\n", data->time_to_sleep);
	set_eating_limits(argc, argv, data);
	if (!allocate((void **)&memories->philos,
			data->num_philo * sizeof(t_philo), memories))
	{
		printf("Error: Failed to allocate memory for philosophers.\n");
		clean_memories(memories);
		return (NULL);
	}
	data->philos = memories->philos;
	if (!allocate((void **)&memories->forks,
			data->num_philo * sizeof(t_fork), memories))
	{
		printf("Error: Failed to allocate memory for forks.\n");
		clean_memories(memories);
		return (NULL);
	}
	data->forks = memories->forks;
	if (!data || !data->philos || !data->forks)
	{
		printf("Error: Data, Philosopher, or Forks array is NULL.\n");
		clean_memories(memories);
		return (NULL);
	}
	if (!allocate((void **)&memories->time, sizeof(t_time), memories))
	{
		printf("Error: Failed to allocate memory for time.\n");
		clean_memories(memories);
		return (NULL);
	}
	init_time(memories->time, data->time_to_die, data->time_to_eat,
		data->time_to_sleep);
	data->memories = memories;
	if (pthread_mutex_init(&(data->waiter), NULL) != 0)
	{
		printf("Error: Mutex initialization failed for the waiter.\n");
		clean_memories(memories);
		return (NULL);
	}
	return (data);
}
