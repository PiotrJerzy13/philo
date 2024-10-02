/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:10:26 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/02 15:59:46 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_meals_eaten(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_count_mutex);
	if (data->max_num_meals != -1 && philo->meals_count >= data->max_num_meals)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->philo_dead = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_unlock(&philo->meals_count_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->meals_count_mutex);
	return (false);
}

void	is_philo_dead_1(t_data *data)
{
	int			i;
	uint64_t	last_meal_time;
	t_philo		*philo;

	i = 0;
	while (i < data->num_philo)
	{
		philo = &data->philos[i];
		if (check_meals_eaten(data, philo))
			return ;
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

void	*handle_one_philo(t_philo *philo)
{
	print_mutex_lock(philo, "has taken the left fork");
	print_mutex_lock(philo, "died");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->data->philo_dead = 1;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (NULL);
}
