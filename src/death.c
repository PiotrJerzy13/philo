/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:10:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/23 16:07:49 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_philosophers(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->philo_dead)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		i = 0;
		pthread_mutex_unlock(&data->death_mutex);
		while (i < data->num_philo)
		{
			if (check_philosopher_starvation(&data->philos[i]))
			{
				pthread_mutex_lock(&data->death_mutex);
				data->philo_dead = true;
				pthread_mutex_unlock(&data->death_mutex);
				handle_philosopher_death(&data->philos[i]);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	check_philosopher_starvation(t_philo *philo)
{
	long	last_meal_time;
	long	elapsed_time;

	if (!philo || !philo->time)
	{
		printf("Error: Philosopher or time structure is NULL.\n");
		return (0);
	}
	pthread_mutex_lock(&philo->meals_count_mutex);
	last_meal_time = philo->time->last_meal;
	if (last_meal_time == -1)
	{
		last_meal_time = philo->time->start_time;
	}
	pthread_mutex_unlock(&philo->meals_count_mutex);
	elapsed_time = time_without_food(last_meal_time);
	return (elapsed_time > philo->time->time_to_die);
}

void	handle_philosopher_death(t_philo const *philo)
{
	printf("%d %d died\n", time_from_start(philo->time), philo->id);
}
