/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:32:58 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/04 14:31:03 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_of_meal_mutex);
	philo->time.last_meal = get_current_time_ms();
	pthread_mutex_unlock(&philo->time_of_meal_mutex);
}

uint64_t	get_meal_time(t_philo *philo)
{
	uint64_t	time_of_last_meal;

	pthread_mutex_lock(&philo->time_of_meal_mutex);
	time_of_last_meal = philo->time.last_meal;
	pthread_mutex_unlock(&philo->time_of_meal_mutex);
	return (time_of_last_meal);
}

void	print_log(int id, const char *state, uint64_t start_time)
{
	uint64_t	timestamp_in_ms;

	timestamp_in_ms = (get_current_time_ms() - start_time);
	printf("%llu %d %s\n", (unsigned long long)timestamp_in_ms, id, state);
}

void	print_mutex_lock(t_philo *philo, const char *state_log)
{
	if (death_mutex_check(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	print_log(philo->id, state_log, philo->time.start_time);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
