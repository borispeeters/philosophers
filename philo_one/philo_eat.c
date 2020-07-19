/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_eat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 16:38:34 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/19 23:36:58 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_drop_fork(t_philo *philo, int fork)
{
	t_data	*data;

	data = philo->data;
	while (pthread_mutex_unlock(&(data->fork_mutex[fork])) != 0)
		continue ;
}

static void	philo_take_fork(t_philo *philo, int fork)
{
	t_data	*data;

	data = philo->data;
	while (pthread_mutex_lock(&(data->fork_mutex[fork])) != 0)
		continue ;
	philo_write(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;
	int		first_fork;
	int		second_fork;

	first_fork = min(philo->lfork, philo->rfork);
	second_fork = max(philo->lfork, philo->rfork);
	data = philo->data;
	philo_take_fork(philo, first_fork);
	philo_take_fork(philo, second_fork);
	while (pthread_mutex_lock(&data->eat_lock) != 0)
		continue ;
	philo_write(philo, "is eating");
	++philo->amount_eaten;
	philo->last_eaten = get_time();
	while (pthread_mutex_unlock(&data->eat_lock) != 0)
		continue ;
	ft_usleep(data->eat_time);
	philo_drop_fork(philo, first_fork);
	philo_drop_fork(philo, second_fork);
}
