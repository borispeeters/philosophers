/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphore.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 01:02:38 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/20 00:20:42 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include "philosophers.h"

int		open_semaphores(t_data *data)
{
	data->write_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	data->eat_lock = sem_open("/eat_lock", O_CREAT, 0644, 1);
	data->dead_lock = sem_open("/dead_lock", O_CREAT, 0644, 0);
	data->fork_sem = sem_open("/fork_sem", O_CREAT, 0644, data->philo_count);
	sem_unlink("/write_lock");
	sem_unlink("/eat_lock");
	sem_unlink("/dead_lock");
	sem_unlink("/fork_sem");
	if (data->write_lock == SEM_FAILED || data->eat_lock == SEM_FAILED
		|| data->fork_sem == SEM_FAILED)
	{
		return (1);
	}
	return (0);
}

int		close_semaphores(t_data *data)
{
	sem_close(data->write_lock);
	sem_close(data->eat_lock);
	sem_close(data->dead_lock);
	sem_close(data->fork_sem);
	return (0);
}
