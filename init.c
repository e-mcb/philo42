/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:54:06 by mzutter           #+#    #+#             */
/*   Updated: 2025/04/28 21:55:45 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_from_args(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->nb_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		philo->meals_needed = ft_atoi(argv[5]);
	else
		philo->meals_needed = -1;
}

void	init_philos(t_philo *philos, t_program *program,
		pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		init_from_args(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_mutex = &program->write_mutex;
		philos[i].death_mutex = &program->death_mutex;
		philos[i].meal_mutex = &program->meal_mutex;
		philos[i].dead = &program->death_flag;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[philos[i].nb_of_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->death_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_mutex, NULL);
	pthread_mutex_init(&program->death_mutex, NULL);
	pthread_mutex_init(&program->meal_mutex, NULL);
}
