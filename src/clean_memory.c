/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:56:27 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/23 15:59:14 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_memories(t_memories *memories)
{
	if (!memories)
		return ;
	if (memories->time)
	{
		free(memories->time);
		memories->time = NULL;
	}
	if (memories->forks)
	{
		free(memories->forks);
		memories->forks = NULL;
	}
	if (memories->philos)
	{
		free(memories->philos);
		memories->philos = NULL;
	}
	if (memories->data)
	{
		free(memories->data);
		memories->data = NULL;
	}
	free(memories);
}
