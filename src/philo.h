/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:20:59 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/10/04 17:56:39 by pwojnaro         ###   ########.fr       */
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
# include <limits.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_data		t_data;
typedef struct s_memories	t_memories;

typedef struct s_time
{
	uint64_t	start_time;
	uint64_t	last_meal;
}	t_time;

typedef struct s_philo
{
	int				id;
	int				meals_count;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	pthread_t		thread;
	t_data			*data;
	t_time			time;
	t_memories		*memories;
	pthread_mutex_t	meals_count_mutex;
	pthread_mutex_t	time_of_meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			has_finished_meals;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				max_num_meals;
	int				philo_dead;
	int				all_eaten;	
	t_philo			*philos;
	t_time			*time;
	t_memories		*memories;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	all_eaten_mutex;
	pthread_mutex_t	*forks;
	pthread_t		checker_thread;
}	t_data;

typedef struct s_memories
{
	t_data			*data;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_memories;

t_data		*init_data(int argc, char **argv);
bool		create_philosopher_threads(t_data *data);
bool		assign_mutexes(t_data *data, t_memories *memories);
bool		check_meals_eaten(t_data *data, t_philo *philo);
uint64_t	get_current_time_ms(void);
uint64_t	get_meal_time(t_philo *philo);
int			death_mutex_check(t_philo *philo);
int			ft_atoi(const char *str);
int			check_passed_arg(int argc, char **argv);
void		clean_memories(t_memories *memories);
void		assign_forks(t_philo *philo, pthread_mutex_t *forks, int num_philo);
void		ft_usleep(uint64_t time_to_sleep_ms);
void		set_meal_time(t_philo *philo);
void		monitor_thread(t_data *data);
void		*is_philo_dead(void *arg);
void		print_mutex_lock(t_philo *philo, const char *state_log);
void		*handle_one_philo(t_philo *philo);
void		*philosopher_routine(void *arg);
void		print_log(int id, const char	*state,
				uint64_t start_time);

#endif
