/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:10:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/29 22:33:33 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_philo_dead_1(t_data *data)
{
	int			i;
	uint64_t	last_meal_time;
	t_philo		*philo;

	i = 0;
	while (i < data->num_philo)
	{
		philo = &data->philos[i];
		last_meal_time = get_meal_time(&data->philos[i]);
		if (get_current_time_ms() - last_meal_time
			>= data->philos[i].time_to_die)
		{
			print_mutex_lock(philo, "died");
			pthread_mutex_lock(&philo->data->death_mutex);
			philo->data->philo_dead = 1;
			pthread_mutex_unlock(&philo->data->death_mutex);
			return ;
		}
		i++;
	}
}

void	*is_philo_dead(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep(100);
	while (data->philo_dead == 0)
	{
		is_philo_dead_1(data);
	}
	return (NULL);
}

int	death_mutex_check(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->death_mutex);
	result = philo->data->philo_dead;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (result);
}
