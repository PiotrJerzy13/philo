/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:19:53 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/03 19:37:48 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int num_philo)
{
	int	left_fork_id;
	int	right_fork_id;

	left_fork_id = philo->id - 1;
	right_fork_id = philo->id % num_philo;
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

bool	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->philos[i].meals_count_mutex, NULL) != 0)
		{
			clean_memories(data->memories);
			return (false);
		}
		assign_forks(&data->philos[i], data->forks, data->num_philo);
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
		{
			printf("Error: Thread creation failed %d.\n", i + 1);
			clean_memories(data->memories);
			return (false);
		}
		i++;
	}
	return (true);
}

void	monitor_thread(t_data *data)
{
	if (pthread_create(&data->checker_thread, NULL, &is_philo_dead, data) != 0)
	{
		printf("Error: Failed to create the checker thread.\n");
		clean_memories(data->memories);
	}
}
