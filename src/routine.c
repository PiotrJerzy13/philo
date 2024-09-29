/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:17:16 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/29 23:45:05 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (death_mutex_check(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->left_fork->fork);
	print_mutex_lock(philo, "has taken the left fork");
	pthread_mutex_lock(&philo->right_fork->fork);
	print_mutex_lock(philo, "has taken the right fork");
	set_meal_time(philo);
	print_mutex_lock(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->meals_count_mutex);
	philo->meals_count += 1;
	pthread_mutex_unlock(&philo->meals_count_mutex);
	if (philo->data->nr_of_meals_mutex)
	{
		pthread_mutex_lock(philo->data->nr_of_meals_mutex);
		philo->data->total_meals += 1;
		pthread_mutex_unlock(philo->data->nr_of_meals_mutex);
	}
}

void	philo_think(t_philo *philo)
{
	if (death_mutex_check(philo) == 1)
		return ;
	print_mutex_lock(philo, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	if (death_mutex_check(philo) == 1)
		return ;
	print_mutex_lock(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (death_mutex_check(philo) == 0)
	{
		if (philo->id % 2 == 0)
		{
			philo_think(philo);
			ft_usleep(philo->time_to_eat / 2);
		}
		while (death_mutex_check(philo) == 0)
		{
			if (philo->data->num_of_meals != -1
				&& philo->meals_count >= philo->data->num_of_meals)
			{
				break ;
			}
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
		}
	}
	return (NULL);
}
