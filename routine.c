/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:17:16 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/21 21:10:05 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*meals_count_mutex;
	int				current_count;
	pthread_mutex_t	*total_meals_mutex;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	printf("Philosopher %d is eating.\n", philo->id);
	usleep(philo->data->time_to_eat * 1000);
	meals_count_mutex = &philo->meals_count_mutex;
	current_count = read_safe(meals_count_mutex, &philo->meals_count);
	safe_write(&philo->meals_count, current_count + 1);
	total_meals_mutex = &philo->data->total_meals_mutex;
	safe_write(&philo->data->total_meals, read_safe(total_meals_mutex,
			&philo->data->total_meals) + 1);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
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
