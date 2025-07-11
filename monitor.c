/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:54:01 by mzutter           #+#    #+#             */
/*   Updated: 2025/04/28 21:53:21 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_mutex);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_mutex);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_mutex);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_mutex), 1);
	pthread_mutex_unlock(philo->meal_mutex);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			print_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].death_mutex);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].meals_needed == -1)
		return (0);
	while (i < philos[0].nb_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_mutex);
		if (philos[i].meals_eaten >= philos[i].meals_needed)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_mutex);
		i++;
	}
	if (finished_eating == philos[0].nb_of_philos)
	{
		pthread_mutex_lock(philos[0].death_mutex);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (pointer);
}
