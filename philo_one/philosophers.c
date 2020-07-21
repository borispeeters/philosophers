/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 16:40:27 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/21 17:09:53 by bpeeters      ########   odam.nl         */
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
		pthread_mutex_lock(&data->eat_lock);
		cur_time = get_time();
		if ((get_time() - philo->last_eaten) > data->die_time)
		{
			philo_write(philo, "died");
			data->state = DEAD;
		}
		pthread_mutex_unlock(&data->eat_lock);
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
	if (pthread_create(&pid, NULL, monitor, philo) != 0)
		return (NULL);
	while (data->state == ALIVE && philo->amount_eaten != data->amount_to_eat)
	{
		philo_write(philo, "is thinking");
		philo_eat(philo);
		philo_write(philo, "is sleeping");
		ft_usleep(data->sleep_time);
	}
	pthread_join(pid, NULL);
	return (NULL);
}

void		philo_threads(t_data *data, t_philo *philo, pthread_t *pt)
{
	int		i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&(pt[i]), NULL, philo_loop, &(philo[i])) != 0)
		{
			while (i > 0)
			{
				--i;
				pthread_join(pt[i], NULL);
			}
			return ;
		}
		++i;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(pt[i], NULL);
		++i;
	}
	if (data->state != DEAD)
		unlocked_message("All philosophers have eaten enough!");
}
