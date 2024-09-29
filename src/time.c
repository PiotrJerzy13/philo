/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:13:44 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/29 22:11:33 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_current_time_ms(void)
{
	struct timeval	time;
	uint64_t		current_time;

	if (gettimeofday(&time, NULL) != 0)
	{
		perror("gettimeofday failed");
		return (0);
	}
	current_time = (uint64_t)(time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

uint64_t	time_from_start(t_time const *params)
{
	return (get_current_time_ms() - params->start_time);
}

uint64_t	time_without_food(uint64_t last_meal)
{
	uint64_t	current_time;

	current_time = get_current_time_ms();
	return (current_time - last_meal);
}

void	init_time(t_time *time_data)
{
	time_data->start_time = get_current_time_ms();
	time_data->last_meal = time_data->start_time;
}

void	ft_usleep(u_int64_t time_to_do_sth)
{
	u_int64_t	start_timestamp;

	start_timestamp = get_current_time_ms();
	while (get_current_time_ms() - start_timestamp < time_to_do_sth)
		usleep(100);
}
