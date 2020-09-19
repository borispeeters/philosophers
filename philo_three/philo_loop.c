/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 22:18:28 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/20 00:01:49 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosophers.h"

static void	*monitor(void *v_philo)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo*)v_philo;
	data = philo->data;
	while (philo->amount_eaten != data->amount_to_eat)
	{
		sem_wait(data->eat_lock);
		if ((get_time() - philo->last_eaten) > (uint64_t)data->die_time)
		{
			data->state = DEAD;
			philo_write(philo, "died");
			sem_post(data->dead_lock);
			break ;
		}
		sem_post(data->eat_lock);
		usleep(100);
	}
	return (NULL);
}

void		philo_loop(t_philo *philo)
{
	t_data		*data;
	pthread_t	pid;

	data = philo->data;
	philo->last_eaten = get_time();
	if (pthread_create(&pid, NULL, monitor, philo) != 0)
		exit(1);
	while (data->state != DEAD && philo->amount_eaten != data->amount_to_eat)
	{
		philo_write(philo, "is thinking");
		philo_eat(philo);
		philo_write(philo, "is sleeping");
		ft_usleep(data->sleep_time);
	}
	pthread_join(pid, NULL);
	exit(0);
}
