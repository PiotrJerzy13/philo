/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:36:48 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/21 21:00:45 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*allocate(void **ptr, size_t size, t_memories *memories)
{
	*ptr = calloc(1, size);
	if (!*ptr)
	{
		clean_memories(memories);
		return (NULL);
	}
	return (*ptr);
}

static void	set_eating_limits(int argc, char **argv, t_data *data)
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
	memories->data = calloc(1, sizeof(t_data));
	if (!memories)
		return (NULL);
	if (!allocate((void **)&memories->data, sizeof(t_data), memories))
		return (NULL);
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	set_eating_limits(argc, argv, data);
	if (!allocate((void **)&memories->philos, data->num_philo
			* sizeof(t_philo), memories))
		return (NULL);
	if (!allocate((void **)&memories->forks, data->num_philo
			* sizeof(t_fork), memories))
		return (NULL);
	if (!allocate((void **)&memories->time, sizeof(t_time), memories))
		return (NULL);
	data->memories = memories;
	if (pthread_mutex_init(&(data->waiter), NULL) != 0)
	{
		clean_memories(memories);
		return (NULL);
	}
	return (data);
}

void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	left_fork_id;
	int	right_fork_id;

	left_fork_id = philo->id;
	right_fork_id = (philo->id + 1) % philo_position;
	if (left_fork_id < right_fork_id)
	{
		philo->left_fork = &forks[left_fork_id];
		philo->right_fork = &forks[right_fork_id];
	}
	else
	{
		philo->left_fork = &forks[right_fork_id];
		philo->right_fork = &forks[left_fork_id];
	}
}

bool	assign_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
		{
			printf("Error: Mutex initialization failed for fork %d.\n", i);
			return (false);
		}
		i++;
	}
	if (pthread_mutex_init(&(data->waiter), NULL) != 0)
	{
		printf("Error: Mutex initialization failed for the waiter.\n");
		return (false);
	}
	return (true);
}
