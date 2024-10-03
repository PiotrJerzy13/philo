/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:13:44 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/03 19:38:11 by pwojnaro         ###   ########.fr       */
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

void	ft_usleep(uint64_t time_to_sleep_ms)
{
	uint64_t	start_timestamp;

	start_timestamp = get_current_time_ms();
	while (get_current_time_ms() - start_timestamp < time_to_sleep_ms)
		usleep(100);
}
