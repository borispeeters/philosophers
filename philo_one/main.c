/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 14:57:52 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/19 16:44:45 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

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
	initialize_data(&data, argv, argc == 6);
	if (initialize_philo(&data, &philo, &pt) != 0)
	{
		write(2, "Failed to allocate memory\n", 26);
		return (-1);
	}
	initiate_mutexes(&data);
	philo_threads(&data, philo, pt);
	destroy_mutexes(&data);
	return (0);
}
