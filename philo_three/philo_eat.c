/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_eat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 14:42:49 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/08/01 14:47:38 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_drop_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_post(data->fork_sem);
}

static void	philo_take_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->fork_sem);
	philo_write(philo, "has taken a fork");
}

void		philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	philo_take_fork(philo);
	philo_take_fork(philo);
	sem_wait(data->eat_lock);
	philo_write(philo, "is eating");
	++philo->amount_eaten;
	philo->last_eaten = get_time();
	sem_post(data->eat_lock);
	ft_usleep(data->eat_time);
	philo_drop_fork(philo);
	philo_drop_fork(philo);
}
