/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_write.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 14:47:56 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/08/01 14:52:34 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

void	philo_write(t_philo *philo, char const *str)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->write_lock);
	if (data->state == ALIVE && philo->amount_eaten != data->amount_to_eat)
	{
		ft_putlong_fd(get_time() - data->start_time, 1);
		write(1, "\t", 1);
		ft_putlong_fd(philo->number, 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	sem_post(data->write_lock);
}

void	unlocked_message(char const *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}
