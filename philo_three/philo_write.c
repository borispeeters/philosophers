/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_write.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 14:47:56 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/20 17:19:57 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

void	philo_write(t_philo *philo, char const *str)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->write_lock);
	if (philo->amount_eaten != data->amount_to_eat)
	{
		ft_putlong_fd(get_time() - data->start_time, STDOUT_FILENO);
		write(STDOUT_FILENO, "\t", 1);
		ft_putlong_fd(philo->number, STDOUT_FILENO);
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, str, ft_strlen(str));
		write(STDOUT_FILENO, "\n", 1);
	}
	if (ft_strcmp(str, "died") != 0)
		sem_post(data->write_lock);
}

void	unlocked_message(char const *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, "\n", 1);
}
