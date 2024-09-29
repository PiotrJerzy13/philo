/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:20:59 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/29 22:39:28 by pwojnaro         ###   ########.fr       */
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
# include <stdint.h>
# include <inttypes.h> 

typedef struct s_data		t_data;
typedef struct s_memories	t_memories;

typedef struct s_time
{
	uint64_t	start_time;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint64_t	last_meal;
}	t_time;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_count;
	t_time			time;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_meals;
	t_memories		*memories;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	meals_count_mutex;
	pthread_mutex_t	last_meal_mutex;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				num_of_meals;
	pthread_mutex_t	*nr_of_meals_mutex;
	t_philo			*philos;
	t_fork			*forks;
	t_time			*time;
	t_memories		*memories;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	int				total_meals;
	int				philo_dead;
	pthread_t		checker_thread;
	int				all_eaten;
}	t_data;

typedef struct s_memories
{
	t_data		*data;
	t_philo		*philos;
	t_fork		*forks;
}	t_memories;

void		start_dinner(t_data *data);
t_data		*init_data(int argc, char **argv);
void		*philosopher_routine(void *arg);
bool		create_philosopher_threads(t_data *data);
bool		assign_mutexes(t_data *data, t_memories *memories);
void		clean_memories(t_memories *memories);
void		assign_forks(t_philo *philo, t_fork *forks, int philo_position);
int			ft_atoi(const char *str);
int			check_passed_arg(int argc, char **argv);
void		init_time(t_time *time_data);
uint64_t	time_without_food(uint64_t last_meal);
uint64_t	time_from_start(t_time const *params);
void		clean_and_exit(t_memories *memories, const char *error_message);
uint64_t	get_current_time_ms(void);
void		ft_usleep(uint64_t time_to_sleep_ms);
void		set_meal_time(t_philo *philo);
uint64_t	get_meal_time(t_philo *philo);
void		print_log(int id, char	*state_log, \
	u_int64_t start_time_program);
void		monitor_thread(t_data *data);
int			death_mutex_check(t_philo *philo);
void		*is_philo_dead(void *arg);
void		print_mutex_lock(t_philo *philo, char *state_log);

#endif
