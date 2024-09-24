/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:13:44 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/23 15:43:54 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_current_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	time_from_start(t_time const *params)
{
	return (get_current_time_ms() - params->start_time);
}

int	time_without_food(int last_meal)
{
	int	current_time;

	current_time = get_current_time_ms();
	return (current_time - last_meal);
}

void	init_time(t_time *time_data, int time_to_die,
			int time_to_eat, int time_to_sleep)
{
	time_data->start_time = get_current_time_ms();
	time_data->time_to_die = time_to_die;
	time_data->time_to_eat = time_to_eat;
	time_data->time_to_sleep = time_to_sleep;
	time_data->last_meal = time_data->start_time;
}
