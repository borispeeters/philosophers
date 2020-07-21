/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_eat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 16:38:34 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/21 23:09:57 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_drop_fork(t_philo *philo, int fork)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&(data->fork_mutex[fork]));
}

static void	philo_take_fork(t_philo *philo, int fork)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->fork_mutex[fork]));
	philo_write(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;
	int		forks[2];

	forks[0] = first_fork(philo);
	forks[1] = second_fork(philo);
	data = philo->data;
	philo_take_fork(philo, forks[0]);
	philo_take_fork(philo, forks[1]);
	pthread_mutex_lock(&data->eat_lock);
	philo_write(philo, "is eating");
	++philo->amount_eaten;
	philo->last_eaten = get_time();
	pthread_mutex_unlock(&data->eat_lock);
	ft_usleep(data->eat_time);
	philo_drop_fork(philo, forks[0]);
	philo_drop_fork(philo, forks[1]);
}
