/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:54:04 by mzutter           #+#    #+#             */
/*   Updated: 2025/04/29 03:28:42 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_parsed_values(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	parsing(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_parsed_values(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_parsed_values(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_parsed_values(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_parsed_values(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_parsed_values(argv[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (parsing(argv) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &program, forks, argv);
	thread_create(&program, forks);
	destroy_mutex(NULL, &program, forks);
	return (0);
}
