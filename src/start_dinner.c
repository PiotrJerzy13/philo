/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:24:43 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/02 17:18:16 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner(t_data *data)
{
	int	i;

	if (!data)
	{
		clean_and_exit(NULL, "Data is NULL in start_dinner.");
		return ;
	}
	if (!assign_mutexes(data, data->memories)
		|| !create_philosopher_threads(data))
	{
		clean_and_exit(data->memories, "Failed during initialization.");
		return ;
	}
	monitor_thread(data);
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("Error: Failed to join thread for philosopher %d.\n", i + 1);
		}
		i++;
	}
	pthread_join(data->checker_thread, NULL);
	clean_memories(data->memories);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_passed_arg(argc, argv) != 0)
	{
		return (1);
	}
	data = init_data(argc, argv);
	if (!data)
	{
		printf("Error: Failed to initialize data.\n");
		return (1);
	}
	start_dinner(data);
	return (0);
}
