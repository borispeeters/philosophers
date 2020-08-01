/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 23:57:37 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/08/01 21:00:35 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

int		main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (-1);
	}
	if (initialize_data(&data, argv, argc == 6) != 0)
	{
		return (-1);
	}
	if (initialize_philo(&data, &philo) != 0)
	{
		write(2, "Failed to allocate memory\n", 26);
		return (-1);
	}
	if (open_semaphores(&data) == 0)
	{
		philo_process(&data, philo);
	}
	close_semaphores(&data);
	free_philo(&philo, &data);
}
