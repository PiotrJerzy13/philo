/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:17:16 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/02 15:59:59 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_odd(t_philo *philo)
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
	ft_usleep(100);
}

void	philo_eat_even(t_philo *philo)
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
	if (philo->data->num_philo == 1)
		return (handle_one_philo(philo));
	if (philo->id % 2 != 0)
		ft_usleep(50);
	while (death_mutex_check(philo) == 0)
	{
		if (philo->data->num_philo % 2 == 0)
			philo_eat_even(philo);
		else
			philo_eat_odd(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
