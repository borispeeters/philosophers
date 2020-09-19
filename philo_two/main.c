/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 10:58:21 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/20 00:16:55 by bpeeters      ########   odam.nl         */
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
		write(STDERR_FILENO, "Invalid number of arguments\n", 28);
		return (1);
	}
	if (initialize_data(&data, argv, argc == 6) != 0)
	{
		return (1);
	}
	if (initialize_philo(&data, &philo, &pt) != 0)
	{
		write(STDERR_FILENO, "Failed to allocate memory\n", 26);
		return (1);
	}
	if (open_semaphores(&data) == 0)
	{
		philo_threads(&data, philo, pt);
	}
	close_semaphores(&data);
	free_philo(&philo, &pt);
	return (0);
}
