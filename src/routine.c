/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:17:16 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/22 11:40:37 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*meals_count_mutex;
	int				current_count;
	pthread_mutex_t	*total_meals_mutex;

	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->right_fork->fork);
	printf("Philosopher %d is eating.\n", philo->id);
	usleep(philo->data->time_to_eat * 1000);
	meals_count_mutex = &philo->meals_count_mutex;
	current_count = read_safe(meals_count_mutex, &philo->meals_count);
	safe_write(&philo->meals_count, current_count + 1);
	total_meals_mutex = &philo->data->total_meals_mutex;
	safe_write(&philo->data->total_meals, read_safe(total_meals_mutex,
			&philo->data->total_meals) + 1);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	philo_sleep(t_philo *philo)
{
	printf("Philosopher %d is sleeping.\n", philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	printf("Philosopher %d is thinking.\n", philo->id);
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*meals_count_mutex;
	pthread_mutex_t	*data_mutex;
	int				num_of_meals;
	int				meals_count;

	philo = (t_philo *)arg;
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
