/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:24:43 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/04 17:57:34 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_leaks(void)
{
	system("leaks philo");
}

void	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	if (!assign_mutexes(data, data->memories)
		|| !create_philosopher_threads(data))
	{
		clean_memories(data->memories);
		return ;
	}
	monitor_thread(data);
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

	atexit(check_leaks);
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments.\n");
		return (1);
	}
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
