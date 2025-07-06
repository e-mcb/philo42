/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:53:58 by mzutter           #+#    #+#             */
/*   Updated: 2025/04/28 22:36:45 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				nb_of_philos;
	int				meals_needed;
	int				*dead;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*meal_mutex;
}					t_philo;

typedef struct s_program
{
	int				death_flag;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	write_mutex;
	t_philo			*philos;
}					t_program;

// Main functions
int					check_parsed_values(char *argv);
int					parsing(char **argv);
void				destroy_mutex(char *str,
						t_program *program, pthread_mutex_t *forks);

// Initialization
void				init_program(t_program *program, t_philo *philos);
void				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_philos(t_philo *philos, t_program *program,
						pthread_mutex_t *forks, char **argv);
void				init_from_args(t_philo *philo, char **argv);

// Threads
int					thread_create(t_program *program, pthread_mutex_t *forks);
void				*monitor(void *pointer);
void				*philo_routine(void *pointer);

// Actions
void				eat(t_philo *philo);
void				dream(t_philo *philo);
void				think(t_philo *philo);

// Monitor utils
int					dead_loop(t_philo *philo);
int					check_if_all_ate(t_philo *philos);
int					check_if_dead(t_philo *philos);
int					philosopher_dead(t_philo *philo, size_t time_to_die);

// Utils
int					ft_atoi(const char *nptr);
int					ft_usleep(size_t microseconds);
int					ft_strlen(char *str);
void				print_message(char *str, t_philo *philo, int id);
size_t				get_current_time(void);

#endif
