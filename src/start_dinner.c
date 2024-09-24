/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:24:43 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/23 17:56:19 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_and_exit(t_memories *memories, const char *error_message)
{
	if (error_message)
		printf("Error: %s\n", error_message);
	clean_memories(memories);
}

void	start_dinner(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	if (!data)
		return (clean_and_exit(NULL, "Data is NULL in start_dinner."));
	if (!assign_mutexes(data, data->memories)
		|| !create_philosopher_threads(data)
		|| pthread_create(&monitor_thread, NULL,
			monitor_philosophers, (void *)data) != 0)
	{
		return (clean_and_exit(data->memories,
				"Failed during initialization."));
	}
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		pthread_mutex_destroy(&data->philos[i].meals_count_mutex);
		i++;
	}
	pthread_join(monitor_thread, NULL);
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
