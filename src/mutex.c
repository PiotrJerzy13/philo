/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:21:40 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/04 17:22:38 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	assign_mutexes(t_data *data, t_memories *memories)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			break ;
		if (pthread_mutex_init(&data->philos[i].meals_count_mutex, NULL) != 0)
			break ;
		i++;
	}
	if (i < data->num_philo
		|| pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->death_mutex, NULL) != 0
		|| pthread_mutex_init(&data->all_eaten_mutex, NULL) != 0)
	{
		printf("Error: Mutex initialization failed.\n");
		clean_memories(memories);
		return (false);
	}
	return (true);
}
