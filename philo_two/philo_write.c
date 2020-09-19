/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_write.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 11:14:46 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/20 00:17:36 by bpeeters      ########   odam.nl         */
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
		ft_putlong_fd(get_time() - data->start_time, STDOUT_FILENO);
		write(STDOUT_FILENO, "\t", 1);
		ft_putlong_fd(philo->number, STDOUT_FILENO);
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, str, ft_strlen(str));
		write(STDOUT_FILENO, "\n", 1);
	}
	sem_post(data->write_lock);
}

void	unlocked_message(char const *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, "\n", 1);
}
