/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 16:28:39 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/19 16:29:03 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	initiate_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		while (pthread_mutex_init(&(data->fork_mutex[i]), NULL) != 0)
			continue ;
		++i;
	}
	while (pthread_mutex_init(&data->write_lock, NULL) != 0)
		continue ;
	while (pthread_mutex_init(&data->eat_lock, NULL) != 0)
		continue ;
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		while (pthread_mutex_destroy(&(data->fork_mutex[i])) != 0)
			continue ;
		++i;
	}
	while (pthread_mutex_destroy(&data->eat_lock) != 0)
		continue ;
	while (pthread_mutex_destroy(&data->write_lock) != 0)
		continue ;
}
