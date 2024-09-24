/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:17:16 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/23 16:37:43 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->right_fork->fork);
	if (philo->data->philo_dead)
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
		return ;
	}
	printf("%d %d has taken a fork\n", time_from_start(philo->time), philo->id);
	printf("%d %d has taken a fork\n", time_from_start(philo->time), philo->id);
	printf("%d %d is eating\n", time_from_start(philo->time), philo->id);
	usleep(philo->data->time_to_eat * 1000);
	safe_write(&philo->meals_count, philo->meals_count + 1);
	safe_write(&philo->data->total_meals, philo->data->total_meals + 1);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	philo_sleep(t_philo *philo)
{
	if (philo->data->philo_dead)
		return ;
	printf("%d %d is sleeping\n", time_from_start(philo->time), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_think(t_philo const *philo)
{
	if (philo->data->philo_dead)
		return ;
	printf("%d %d is thinking\n", time_from_start(philo->time), philo->id);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->philo_dead)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (philo->data->num_of_meals != -1
			&& philo->meals_count >= philo->data->num_of_meals)
			break ;
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
