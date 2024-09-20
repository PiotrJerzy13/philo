/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:30:33 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/20 11:55:49 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher_routine(void *arg)
{
    int id;
	pthread_mutex_t forks[NUM_PHILOSOPHERS];
	
	id = *(int *)arg;
    free(arg);
    while (1) 
	{
        printf("Philosopher %d is thinking\n", id);
        usleep(1000 * (rand() % 100 + 100));
        pthread_mutex_lock(&forks[id]);
        pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d is eating\n", id);
        usleep(1000 * (rand() % 100 + 100));
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d is sleeping\n", id);
        usleep(1000 * (rand() % 100 + 100));
    }
    return NULL;
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
	pthread_mutex_t forks[NUM_PHILOSOPHERS];
    int i = 0;

    while (i < NUM_PHILOSOPHERS)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < NUM_PHILOSOPHERS)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher_routine, id);
        i++;
    }
    i = 0;
    while (i < NUM_PHILOSOPHERS)
    {
        pthread_join(philosophers[i], NULL);
        i++;
    }
    i = 0;
    while (i < NUM_PHILOSOPHERS)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    return 0;
}
