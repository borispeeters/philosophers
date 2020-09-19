/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 16:28:39 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/20 00:20:31 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philosophers.h"

int		initiate_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->eat_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_lock);
		return (1);
	}
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&(data->fork_mutex[i]), NULL) != 0)
		{
			destroy_mutexes(data, i);
			return (1);
		}
		++i;
	}
	return (0);
}

void	destroy_mutexes(t_data *data, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		pthread_mutex_destroy(&(data->fork_mutex[i]));
		++i;
	}
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->write_lock);
}
