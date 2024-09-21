/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:24:43 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/21 21:10:26 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*meals_count_mutex;
	pthread_mutex_t	*data_mutex;
	int				num_of_meals;
	int				meals_count;

	meals_count_mutex = &philo->meals_count_mutex;
	data_mutex = &philo->data->data_mutex;
	philo = (t_philo *)arg;
	while (1)
	{
		num_of_meals = read_safe(data_mutex, &philo->data->num_of_meals);
		meals_count = read_safe(meals_count_mutex, &philo->meals_count);
		if (num_of_meals != -1 && meals_count >= num_of_meals)
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

bool	create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].id = i;
		data->philos[i].meals_count = 0;
		pthread_mutex_init(&data->philos[i].meals_count_mutex, NULL);
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

void	start_dinner(int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = 0;
	data = init_data(argc, argv);
	if (!data)
	{
		return ;
	}
	if (!assign_mutexes(data))
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
