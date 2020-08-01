/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 14:57:52 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/08/01 12:00:58 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include "philosophers.h"

int		main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	*pt;

	if (argc != 5 && argc != 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (-1);
	}
	if (initialize_data(&data, argv, argc == 6) != 0)
	{
		return (-1);
	}
	if (initialize_philo(&data, &philo, &pt) != 0)
	{
		write(2, "Failed to allocate memory\n", 26);
		return (-1);
	}
	if (initiate_mutexes(&data) == 0)
	{
		philo_threads(&data, philo, pt);
		destroy_mutexes(&data, data.philo_count);
	}
	free_philo(&data, &philo, &pt);
	return (0);
}
