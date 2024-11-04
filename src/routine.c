/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:17:16 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/08 12:07:53 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (death_mutex_check(philo) == 1)
		return ;
	pthread_mutex_lock(philo->left_fork);
	print_mutex_lock(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_mutex_lock(philo, "has taken a fork");
	set_meal_time(philo);
	print_mutex_lock(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
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
	{
		print_log(philo->id, "is thinking", philo->time.start_time);
		ft_usleep(50);
	}
	while (death_mutex_check(philo) == 0)
	{
		if (philo->data->num_philo % 2 == 0)
			philo_eat(philo);
		else
		{
			philo_eat(philo);
			ft_usleep(100);
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
