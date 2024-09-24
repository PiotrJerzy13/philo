/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:19:53 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/23 14:09:29 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_count = 0;
		if (pthread_mutex_init(&data->philos[i].meals_count_mutex, NULL) != 0)
		{
			printf("Error: Mutex initialization failed");
			return (false);
		}
		data->philos[i].memories = data->memories;
		data->philos[i].data = data;
		assign_forks(&data->philos[i], data->forks, data->num_philo);
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
		{
			printf("Error: Thread creation failed for philosopher %d.\n", i);
			return (false);
		}
		i++;
	}
	return (true);
}
