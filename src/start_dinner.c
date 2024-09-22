/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:24:43 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/22 20:23:05 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner(t_data *data)
{
	int		i;

	i = 0;
	if (!data)
	{
		printf("Error: Data is NULL in start_dinner.\n");
		return ;
	}
	if (!assign_mutexes(data, data->memories))
	{
		clean_memories(data->memories);
		return ;
	}
	if (!create_philosopher_threads(data))
	{
		clean_memories(data->memories);
		return ;
	}
	while (i < data->num_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		pthread_mutex_destroy(&data->philos[i].meals_count_mutex);
		i++;
	}
	clean_memories(data->memories);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = init_data(argc, argv);
	if (!data)
	{
		printf("Error: Failed to initialize data.\n");
		return (1);
	}
	start_dinner(data);
	return (0);
}
