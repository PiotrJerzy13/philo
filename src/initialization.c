/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:36:48 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/03 19:39:48 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*allocate(void **ptr, size_t size, t_memories *memories)
{
	*ptr = malloc(size);
	if (!*ptr)
	{
		printf("Error: Memory allocation failed.\n");
		if (memories)
		{
			clean_memories(memories);
		}
		return (NULL);
	}
	memset(*ptr, 0, size);
	return (*ptr);
}

void	take_input(int argc, char **argv, t_data *data)
{
	data->num_philo = ft_atoi(argv[1]);
	if (argc == 6)
		data->max_num_meals = ft_atoi(argv[5]);
	else
		data->max_num_meals = -1;
	data->all_eaten = 0;
	data->philo_dead = 0;
}

bool	allocate_resources(t_data **data, t_memories **memories, int num_philo)
{
	while (true)
	{
		*memories = allocate((void **)memories, sizeof(t_memories), NULL);
		if (!(*memories))
			break ;
		*data = allocate((void **)&(*memories)->data,
				sizeof(t_data), *memories);
		if (!(*data))
			break ;
		if (!allocate((void **)&(*memories)->philos,
				num_philo * sizeof(t_philo), *memories))
			break ;
		if (!allocate((void **)&(*memories)->forks,
				num_philo * sizeof(pthread_mutex_t), *memories))
			break ;
		break ;
	}
	if (!(*memories) || !(*data) || !(*memories)->philos || !(*memories)->forks)
	{
		clean_memories(*memories);
		return (false);
	}
	(*data)->philos = (*memories)->philos;
	(*data)->forks = (*memories)->forks;
	return (true);
}

t_data	*init_data(int argc, char **argv)
{
	int			i;
	t_memories	*memories;
	t_data		*data;

	memories = NULL;
	data = NULL;
	i = 0;
	if (!allocate_resources(&data, &memories, ft_atoi(argv[1])))
		return (NULL);
	take_input(argc, argv, data);
	while (i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_count = 0;
		data->philos[i].memories = memories;
		data->philos[i].data = data;
		data->philos[i].time_to_die = ft_atoi(argv[2]);
		data->philos[i].time_to_eat = ft_atoi(argv[3]);
		data->philos[i].time_to_sleep = ft_atoi(argv[4]);
		data->philos[i].time.start_time = get_current_time_ms();
		data->philos[i].time.last_meal = data->philos[i].time.start_time;
		i++;
	}
	data->memories = memories;
	return (data);
}
