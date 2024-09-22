/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:20:59 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/22 21:30:33 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>

# define MIN_ARGC 5
# define MAX_ARGC 6 

typedef struct s_data		t_data;
typedef struct s_memories	t_memories;

typedef struct s_time
{
	int	start_time;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	last_meal;
}	t_time;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;
	int				is_taken;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_count;
	int				has_eaten;
	t_time			*time;
	t_memories		*memories;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	meals_count_mutex;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	t_philo			*philos;
	t_fork			*forks;
	t_time			*time;
	t_memories		*memories;
	pthread_mutex_t	waiter;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	total_meals_mutex;
	int				total_meals;
}	t_data;

typedef struct s_memories
{
	t_data		*data;
	t_philo		*philos;
	t_fork		*forks;
	t_time		*time;
}	t_memories;

// Function Prototypes
void	start_dinner(t_data *data);
t_data	*init_data(int argc, char **argv);
void	set_eating_limits(int argc, char **argv, t_data *data);
void	*allocate(void **ptr, size_t size, t_memories *memories);
void	*philosopher_routine(void *arg);
bool	create_philosopher_threads(t_data *data);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	assign_mutex(pthread_mutex_t *mutex, const char *operation);
bool	assign_mutexes(t_data *data, t_memories *memories);
void	clean_memories(t_memories *memories);
void	clean_memories_resources(t_memories *memories);
void	safe_write(int *value_ptr, int new_value);
int		read_safe(pthread_mutex_t *mutex, int *value);
void	assign_forks(t_philo *philo, t_fork *forks, int philo_position);
int		ft_atoi(const char *str);
int		check_passed_arg(int argc, char **argv);
void	init_time(t_time *time_data, int time_to_die,
			int time_to_eat, int time_to_sleep);

#endif
