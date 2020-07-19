/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 16:40:27 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/20 00:17:23 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include "philosophers.h"

static void	*monitor(void *v_philo)
{
	t_philo		*philo;
	t_data		*data;
	uint64_t	cur_time;

	philo = (t_philo*)v_philo;
	data = philo->data;
	while (data->state == ALIVE && philo->amount_eaten != data->amount_to_eat)
	{
		while (pthread_mutex_lock(&data->eat_lock) != 0)
			continue ;
		cur_time = get_time();
		if ((get_time() - philo->last_eaten) > data->die_time)
		{
			philo_write(philo, "died");
			data->state = DEAD;
		}
		while (pthread_mutex_unlock(&data->eat_lock) != 0)
			continue ;
		usleep(100);
	}
	return (NULL);
}

static void	*philo_loop(void *v_philo)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	pid;

	philo = (t_philo*)v_philo;
	data = philo->data;
	philo->last_eaten = get_time();
	while (pthread_create(&pid, NULL, monitor, philo) != 0)
		continue ;
	while (data->state == ALIVE && philo->amount_eaten != data->amount_to_eat)
	{
		philo_write(philo, "is thinking");
		philo_eat(philo);
		philo_write(philo, "is sleeping");
		ft_usleep(data->sleep_time);
	}
	while (pthread_join(pid, NULL) != 0)
		continue ;
	return (NULL);
}

void	philo_threads(t_data *data, t_philo *philo, pthread_t *pt)
{
	int		i;

	i = 0;
	while (i < data->philo_count)
	{
		while (pthread_create(&(pt[i]), NULL, philo_loop, &(philo[i])) != 0)
			continue ;
		++i;
	}
	i = 0;
	while (i < data->philo_count)
	{
		while (pthread_join(pt[i], NULL) != 0)
			continue ;
		++i;
	}
	if (data->state != DEAD)
		unlocked_message("All philosophers have eaten enough!");
}
