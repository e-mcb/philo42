/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:53:49 by mzutter           #+#    #+#             */
/*   Updated: 2025/04/29 20:29:37 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->death_mutex), 1);
	pthread_mutex_unlock(philo->death_mutex);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destroy_mutex("Thread creation error", program, forks);
	i = 0;
	while (i < program->philos[0].nb_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			destroy_mutex("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_mutex("Thread join error", program, forks);
	while (i < program->philos[0].nb_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_mutex("Thread join error", program, forks);
		i++;
	}
	return (0);
}
